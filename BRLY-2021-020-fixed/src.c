// SMM Initialization Function - Acquire Resources During Driver Load
EFI_STATUS SmmInitialize(void) {
    EFI_STATUS status;
    UINTN handleCount = 0;
    EFI_HANDLE *handleBuffer = NULL;
    
    // Cache ATA Pass-Thru Protocol handles during initialization
    status = gBS->LocateHandleBuffer(
        ByProtocol,
        &EFI_ATA_PASS_THRU_PROTOCOL_GUID,
        NULL,
        &handleCount,
        &handleBuffer
    );
    
    if (status == EFI_SUCCESS) {
        // Allocate SMRAM buffer to store handles
        status = gSmst->SmmAllocatePool(
            EfiRuntimeServicesData,
            handleCount * sizeof(EFI_HANDLE),
            (VOID**)&gAtaHandles
        );
        
        if (status == EFI_SUCCESS) {
            gAtaHandleCount = handleCount;
            CopyMem(gAtaHandles, handleBuffer, handleCount * sizeof(EFI_HANDLE));
        }
        
        gBS->FreePool(handleBuffer);
    }
    
    // Cache ACPI Support Protocol
    status = gBS->LocateProtocol(
        &EFI_ACPI_SUPPORT_PROTOCOL_GUID,
        NULL,
        (VOID**)&gEfiAcpiSupport
    );
    
    if (status == EFI_SUCCESS) {
        // Find FACP table and cache relevant value during initialization
        UINTN tableIndex = 0;
        ACPI_TABLE_HEADER *tableBuffer = NULL;
        UINTN tableSize = 0;
        
        while (1) {
            status = gEfiAcpiSupport->GetAcpiTable(
                tableIndex,
                &tableBuffer,
                &tableSize,
                NULL
            );
            
            if (status != EFI_SUCCESS) break;
            
            if (tableBuffer->Signature == EFI_ACPI_FACP_SIGNATURE) {
                FACP *facp = (FACP*)tableBuffer;
                gFacpValue = facp->PMTimerBlock; // Adjust based on actual field
                status = EFI_SUCCESS;
                break;
            }
            
            gBS->FreePool(tableBuffer);
            tableIndex++;
        }
        
        if (tableBuffer) gBS->FreePool(tableBuffer);
    }
    
    return status;
}

// Fixed SMI Handler - Removed Boot Services Dependency
EFI_STATUS __fastcall SmiHandler_80000A14(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    void *CommBuffer,
    UINTN *CommBufferSize
) {
    EFI_STATUS status = EFI_SUCCESS;
    
    // Validate input parameters
    if (CommBuffer == NULL || CommBufferSize == NULL || *CommBufferSize < 8) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Process command based on buffer content
    if (*(UINT32*)CommBuffer == 0x01) {
        // Use cached ATA handles instead of calling LocateHandleBuffer
        if (gAtaHandles == NULL || gAtaHandleCount == 0) {
            status = EFI_NOT_READY;
        } else {
            // Check if handle count changed (compare with cached value)
            UINTN smmHandleCount = 0;
            status = gSmst->SmmLocateHandle(
                ByProtocol,
                &EFI_ATA_PASS_THRU_PROTOCOL_GUID,
                NULL,
                &smmHandleCount,
                NULL
            );
            
            if (status == EFI_BUFFER_TOO_SMALL && smmHandleCount == gAtaHandleCount) {
                // Handle count matches cached value, proceed
                status = sub_8000082C(1, gAtaHandles[0]); // Use first handle
                
                if (status == EFI_SUCCESS || status == EFI_ALREADY_STARTED) {
                    // Use cached ACPI protocol instead of calling LocateProtocol
                    if (gEfiAcpiSupport != NULL) {
                        // ACPI table access already handled during initialization
                        // Use cached gFacpValue
                    }
                }
            } else {
                status = EFI_NOT_FOUND;
            }
        }
    } else {
        status = EFI_UNSUPPORTED;
    }
    
    // Write status back to communication buffer
    *(UINT32*)((UINT8*)CommBuffer + 4) = status;
    return EFI_SUCCESS;
}

// Fixed Subroutine - Uses Cached Resources
EFI_STATUS __fastcall sub_8000082C(char action, EFI_HANDLE ataHandle) {
    EFI_STATUS status = EFI_SUCCESS;
    
    if (!action) return EFI_SUCCESS;
    
    // Use cached SMM Runtime Protocol instead of calling LocateProtocol
    if (gEfiSmmRuntimeProtocol != NULL) {
        (gEfiSmmRuntimeProtocol->Method_0)(
            &EFI_SMM_RUNTIME_PROTOCOL_GUID,
            0,
            &gEfiSmmRuntimeProtocol
        );
    }
    
    // Use provided ATA handle instead of querying
    if (ataHandle != NULL) {
        // Process ATA handle
        // ... original logic ...
    } else {
        status = EFI_INVALID_PARAMETER;
    }
    
    return status;
}

// Driver Entry Point - Initialize Resources Before SMI Handler Registration
EFI_STATUS DriverEntry(...) {
    EFI_STATUS status;
    EFI_HANDLE dispatchHandle;
    
    // Initialize SMM resources using Boot Services
    status = SmmInitialize();
    if (status != EFI_SUCCESS) {
        return status;
    }
    
    // Register SMI handler
    status = gSmst->SmiHandlerRegister(
        SmiHandler_80000A14,
        &gSmiHandlerGuid,
        &dispatchHandle
    );
    
    return status;
}
