// SMM Initialization Function - Safe Boot Services Usage during Driver Initialization
EFI_STATUS SmmInitialize(void) {
    EFI_ACPI_SUPPORT_PROTOCOL *EfiAcpiSupportProtocol;
    ACPI_TABLE_HEADER *FacpBuffer;
    UINTN Index = 0, TableKey = 0, TableSize = 0;
    
    // Locate ACPI Support Protocol (Only called once during SMM initialization)
    if (gBS->LocateProtocol(&EFI_ACPI_SUPPORT_PROTOCOL_GUID, NULL, (VOID**)&EfiAcpiSupportProtocol) != EFI_SUCCESS) {
        return EFI_UNSUPPORTED;
    }
    
    // Find FACP Table and Cache PMTimerBlock (Executed only once during initialization)
    while (1) {
        EFI_STATUS status = EfiAcpiSupportProtocol->GetAcpiTable(Index, &FacpBuffer, &TableSize, &TableKey);
        if (status != EFI_SUCCESS) break;
        if (FacpBuffer->Signature == EFI_ACPI_FACP_SIGNATURE) {
            gPMTimerBlock = ((FACP *)FacpBuffer)->PMTimerBlock;
            gBS->FreePool(FacpBuffer);
            break;
        }
        gBS->FreePool(FacpBuffer);
        Index++;
    }
    
    return EFI_SUCCESS;
}

// Fixed SMI Handler - Removed Dependency on Boot Services
EFI_STATUS __fastcall SmiHandler_80000984(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    void *CommBuffer,
    UINTN *CommBufferSize
) {
    UINT8 *CommBuffer1 = (UINT8 *)CommBuffer;
    
    // Validate input parameters
    if (CommBuffer == NULL || CommBufferSize == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    if (*CommBufferSize < COMMAND_BUFFER_MIN_SIZE) {
        return EFI_BUFFER_TOO_SMALL;
    }
    
    // Process command based on buffer content
    if (*CommBuffer != 0) {
        CommBuffer1[1] = EFI_UNSUPPORTED;
        return EFI_SUCCESS;
    }
    
    if (COMM_BUFFER_COMMAND(CommBuffer) == 0x130) {
        // Ensure PMTimerBlock was cached during SMM initialization
        if (gPMTimerBlock == NULL) {
            CommBuffer1[1] = EFI_NOT_READY;
            return EFI_SUCCESS;
        }
        
        // Process command data using cached PMTimerBlock
        CommBuffer1 = CommBuffer + COMMAND_DATA_OFFSET;
        EFI_STATUS status = sub_800007F8(gPMTimerBlock, CommBuffer1);
        CommBuffer1[1] = status;
    } else {
        CommBuffer1[1] = EFI_INVALID_PARAMETER;
    }
    
    return EFI_SUCCESS;
}

// Fixed Subroutine - Uses Cached Resources Instead of Boot Services
EFI_STATUS sub_800007F8(PM_TIMER_BLOCK *CachedPMTimerBlock, UINT8 *DataBuffer) {
    // Use cached PMTimerBlock instead of querying during SMI handling
    if (CachedPMTimerBlock == NULL) {
        return EFI_NOT_READY;
    }
    
    // Original business logic...
    return EFI_SUCCESS;
}

// Driver Entry Point - Initialize SMM Resources Before Registering Handler
EFI_STATUS DriverEntry(...) {
    // Initialize SMM resources safely using Boot Services
    if (SmmInitialize() != EFI_SUCCESS) {
        return EFI_ABORTED;
    }
    
    // Register SMI handler after initialization
    EFI_HANDLE DispatchHandle;
    EFI_STATUS status = gSmst->SmiHandlerRegister(SmiHandler_80000984, &gSmiHandlerGuid, &DispatchHandle);
    if (status != EFI_SUCCESS) {
        return status;
    }
    
    // Register protocol notification if needed
    return EFI_SUCCESS;
}
