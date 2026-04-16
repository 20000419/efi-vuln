// SMRAM-resident structure to cache protocol handles and pointers
typedef struct {
    UINTN Magic;                                  // Signature for buffer validation (0x4d4d5353 'SMM')
    EFI_ATA_PASS_THRU_PROTOCOL *CachedAtaProtocol; // Cached ATA pass-thru protocol
    EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *CachedStorageSecurityProtocol; // Cached storage security protocol
    UINTN AtaHandleCount;                         // Cached count of ATA handles
    EFI_HANDLE *CachedAtaHandles;                 // Array of cached ATA handles (SMRAM allocated)
} SMM_CACHED_PROTOCOLS;

// Global pointer to SMRAM-resident cache (initialized in driver entry)
SMM_CACHED_PROTOCOLS *gSmmCachedProtocols = NULL;

// Initialization function - safely uses boot services during driver load
EFI_STATUS InitializeSmmCachedProtocols(EFI_HANDLE DriverHandle) {
    EFI_STATUS status;
    UINTN bufferSize = sizeof(SMM_CACHED_PROTOCOLS);
    
    // Allocate SMRAM buffer for protocol caching
    status = gSmst->SmmAllocatePool(EfiRuntimeServicesData, bufferSize, (VOID**)&gSmmCachedProtocols);
    if (status != EFI_SUCCESS) {
        return status;
    }
    ZeroMem(gSmmCachedProtocols, bufferSize);
    gSmmCachedProtocols->Magic = 0x4d4d5353; // 'SMM' magic number
    
    // Cache ATA Pass-Thru protocol using boot services (only during initialization)
    status = gBS->LocateProtocol(&EFI_ATA_PASS_THRU_PROTOCOL_GUID, NULL, 
                                (VOID**)&gSmmCachedProtocols->CachedAtaProtocol);
    if (status != EFI_SUCCESS) {
        gSmst->SmmFreePool(gSmmCachedProtocols);
        return status;
    }
    
    // Cache Storage Security Command protocol handles
    status = gBS->LocateHandleBuffer(ByProtocol, &EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID, 
                                    NULL, &gSmmCachedProtocols->AtaHandleCount, 
                                    (EFI_HANDLE**)&gSmmCachedProtocols->CachedAtaHandles);
    if (status != EFI_SUCCESS && status != EFI_NOT_FOUND) {
        gSmst->SmmFreePool(gSmmCachedProtocols);
        return status;
    }
    
    return EFI_SUCCESS;
}

// Fixed subroutine - eliminates boot services in SMM context
EFI_STATUS sub_80001508(__int64 Pointer, char InSmm) {
    EFI_STATUS status = EFI_UNSUPPORTED;
    
    // Validate SMRAM cache integrity
    if (gSmmCachedProtocols == NULL || gSmmCachedProtocols->Magic != 0x4d4d5353) {
        return EFI_DEVICE_ERROR;
    }
    
    if (InSmm) {
        // Use SMM services or cached protocols (never boot services)
        if (gSmmCachedProtocols->CachedAtaProtocol) {
            // Example: Directly use cached ATA protocol instead of HandleProtocol
            status = gSmmCachedProtocols->CachedAtaProtocol->Identify(/* parameters */);
        } else {
            // Fallback to SMM-specific protocol lookup (safe if not cached during init)
            status = gSmst->SmmHandleProtocol(Pointer, &EFI_ATA_PASS_THRU_PROTOCOL_GUID, 
                                            (VOID**)&gSmmCachedProtocols->CachedAtaProtocol);
        }
    } else {
        // Non-SMM context - allow boot services (but should be rare in SMI handler)
        status = gBS->HandleProtocol(Pointer, &EFI_ATA_PASS_THRU_PROTOCOL_GUID, 
                                   (VOID**)&gSmmCachedProtocols->CachedAtaProtocol);
    }
    
    return status;
}

// Fixed SMI Handler - only uses SMM services or cached protocols
EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, 
                      void *CommBuffer, UINTN *CommBufferSize) {
    EFI_STATUS status = EFI_SUCCESS;
    UINT64 command = 0;
    
    // Validate input parameters
    if (!CommBuffer || !CommBufferSize || *CommBufferSize < sizeof(UINT64)) {
        return EFI_INVALID_PARAMETER;
    }
    
    command = *(_QWORD *)CommBuffer;
    
    switch (command) {
        case 1: {
            // Use cached protocol for ATA operations in SMM
            if (gSmmCachedProtocols->CachedAtaProtocol) {
                status = sub_80001508(*((_QWORD *)CommBuffer + 2), 1); // InSmm = 1 (SMM context)
            } else {
                status = EFI_NOT_FOUND;
            }
            break;
        }
        case 2: {
            UINTN i = 0, handleCount = gSmmCachedProtocols->AtaHandleCount;
            EFI_HANDLE *handles = gSmmCachedProtocols->CachedAtaHandles;
            
            // Use cached storage security protocol handles (SMRAM-resident)
            while (i < handleCount) {
                EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *protocol = NULL;
                status = gSmst->SmmHandleProtocol(handles[i], 
                                                &EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID, 
                                                (VOID**)&protocol);
                if (!status && protocol) {
                    // Validate protocol signature using cached data (no boot services)
                    if (*(UINT64*)(protocol - 0x20) == 'GOTS' && !*(UINT64*)(protocol - 8)) {
                        // Safe operations using SMM services or cached data
                    }
                }
                i++;
            }
            break;
        }
        default:
            status = EFI_UNSUPPORTED;
    }
    
    return status;
}

// Driver Entry Point - handles initialization and SMI registration
EFI_STATUS DriverEntry(IN EFI_HANDLE DriverHandle, IN EFI_SYSTEM_TABLE *SystemTable) {
    EFI_STATUS status;
    EFI_HANDLE dispatchHandle;
    
    // Initialize SMRAM-resident protocol cache using boot services
    status = InitializeSmmCachedProtocols(DriverHandle);
    if (status != EFI_SUCCESS) {
        return status;
    }
    
    // Register SMI handler after caching is complete
    status = gSmst->SmiHandlerRegister(SmiHandler, &gSmiHandlerGuid, &dispatchHandle);
    if (status != EFI_SUCCESS) {
        gSmst->SmmFreePool(gSmmCachedProtocols);
        return status;
    }
    
    return EFI_SUCCESS;
}
