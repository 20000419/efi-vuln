// SMRAM-resident buffer structure to hold cached protocol data
typedef struct {
    UINT32 Magic;                  // Signature for buffer validation
    UINT16 ProtocolHandle;         // Handle of the unknown protocol
    UINT16 ProtocolHandleIndex;    // Index within the protocol structure
    EFI_SMM_RUNTIME_PROTOCOL *SmmRuntimeProtocol; // Cached SMM runtime protocol
    void *UnknownProtocol;         // Cached unknown protocol pointer
    EFI_STATUS (*Sub_80000B2C)();  // Cached function pointer
    EFI_STATUS (*Sub_80001040)();  // Cached function pointer
} SMM_BUFFER_DATA;

// Global pointer to SMRAM buffer (allocated in initialization)
SMM_BUFFER_DATA *gSmmBuffer = NULL;

// Initialization function - uses boot services safely
EFI_STATUS InitializeSmmResources(EFI_HANDLE DriverHandle) {
    EFI_STATUS status;
    UINTN bufferSize = sizeof(SMM_BUFFER_DATA);
    
    // Allocate SMRAM buffer for critical data
    status = gSmst->SmmAllocatePool(EfiRuntimeServicesData, bufferSize, (VOID**)&gSmmBuffer);
    if (status != EFI_SUCCESS) {
        return status;
    }
    
    // Clear buffer and set magic signature
    ZeroMem(gSmmBuffer, bufferSize);
    gSmmBuffer->Magic = 'S51I'; // Preserve original magic value
    
    // Safely locate protocols during initialization (boot services)
    status = gBS->LocateProtocol(&EFI_SMM_RUNTIME_PROTOCOL_GUID, NULL, 
                                (VOID**)&gSmmBuffer->SmmRuntimeProtocol);
    if (status != EFI_SUCCESS) {
        gSmst->SmmFreePool(gSmmBuffer);
        return status;
    }
    
    // Locate unknown protocol and cache its handle/index
    status = gBS->LocateProtocol(&UNKNOWN_PROTOCOL_3D819F77_GUID, NULL, 
                                &gSmmBuffer->UnknownProtocol);
    if (status == EFI_SUCCESS) {
        // Extract handle and index (assuming protocol structure layout)
        gSmmBuffer->ProtocolHandle = *((UINT16*)gSmmBuffer->UnknownProtocol);
        gSmmBuffer->ProtocolHandleIndex = *((UINT16*)gSmmBuffer->UnknownProtocol + 1);
        
        // Cache function pointers used in subroutines
        gSmmBuffer->Sub_80000B2C = sub_80000B2C;
        gSmmBuffer->Sub_80001040 = sub_80001040;
    }
    
    return EFI_SUCCESS;
}

// Fixed SMI Handler - Only uses SMRAM-resident cached data
EFI_STATUS SwSmiHandler(EFI_HANDLE DispatchHandle, const void *Context, 
                        void *CommBuffer, UINTN *CommBufferSize) {
    // Validate SMRAM buffer magic signature
    if (gSmmBuffer == NULL || gSmmBuffer->Magic != 'S51I') {
        return EFI_UNSUPPORTED;
    }
    
    // Check the critical value (now initialized during boot, not dependent on runtime lookup)
    if (!gSmmBuffer->ProtocolHandleIndex) {
        // Use cached SMM runtime protocol instead of boot services
        if (gSmmBuffer->SmmRuntimeProtocol != NULL) {
            // Example: Use cached protocol functions safely
            gSmmBuffer->SmmRuntimeProtocol->QueryCapsuleCapabilities(...);
        }
        return EFI_SUCCESS;
    }
    
    // Rest of the handler logic using cached data...
    return EFI_SUCCESS;
}

// Modified subroutine - Eliminates boot service calls
__int64 sub_80000D18() {
    // This function is now only called during initialization, 
    // and uses already cached protocol pointers from gSmmBuffer
    
    // Example: Access cached unknown protocol
    if (gSmmBuffer->UnknownProtocol != NULL) {
        // Directly use pre-stored handle/index values
        UINT64 targetAddress = (UINT64)gSmmBuffer->UnknownProtocol + 
                             0x10 * gSmmBuffer->ProtocolHandleIndex + 0x32;
        *(UINT64*)targetAddress = (UINT64)gSmmBuffer->Sub_80000B2C;
    }
    
    return 0;
}

// Driver Entry Point - Coordinates initialization and SMI registration
EFI_STATUS DriverEntry(IN EFI_HANDLE DriverHandle, IN EFI_SYSTEM_TABLE *SystemTable) {
    EFI_STATUS status;
    EFI_HANDLE dispatchHandle;
    
    // Initialize SMRAM resources using boot services
    status = InitializeSmmResources(DriverHandle);
    if (status != EFI_SUCCESS) {
        return status;
    }
    
    // Register SMI handler after resources are initialized
    status = gSmst->SmiHandlerRegister(SwSmiHandler, &gSmiHandlerGuid, &dispatchHandle);
    if (status != EFI_SUCCESS) {
        gSmst->SmmFreePool(gSmmBuffer);
        return status;
    }
    
    // Call subroutine once during initialization (safe here)
    sub_80000D18();
    
    return EFI_SUCCESS;
}
