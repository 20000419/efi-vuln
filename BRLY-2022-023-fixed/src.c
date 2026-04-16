EFI_STATUS __fastcall SwSmiHandler(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    void *CommBuffer,
    UINTN *CommBufferSize
) {
    __int64 Ptr;
    __int16 Index;
    __int16 ResValue;
    UINTN Val;
    __int64 IhisiParamBufferValue;
    EFI_STATUS Status;

    if (ToGetIhisiParamBufferVar(&IhisiParamBufferValue, &Val, CommBuffer) >= EFI_SUCCESS) {
        Ptr = IhisiParamBufferValue;
        
        // Validate signature
        if (*(IhisiParamBufferValue + 16) == 'BSI$') {
            Index = *(*(IhisiParamBufferValue + 0x28) + 6);
            
            // Validate index range
            if ((Index & 0xFFF8) == 80) {
                // Validate function pointer in table
                if (Index >= 80 && Index <= 87 && gFuncsTable[Index & 7] != NULL) {
                    ResValue = (gFuncsTable[Index & 7])(*(IhisiParamBufferValue + 0x28));
                } else {
                    ResValue = 0x82; // Invalid function pointer
                }
            } else {
                ResValue = 0x82; // Invalid index
            }
            
            // Calculate target address (Ptr + 8)
            UINT64 targetAddress = Ptr + 8;
            
            // Validate target address is within SMRAM
            Status = IsAddressInSmram(targetAddress, sizeof(ResValue));
            if (EFI_ERROR(Status)) {
                return EFI_ACCESS_DENIED; // Prevent write to non-SMRAM memory
            }
            
            // Safely write to SMRAM
            *(UINT16*)targetAddress = ResValue;
        }
    }
    return EFI_SUCCESS;
}

// Helper function to check if address is within SMRAM
EFI_STATUS IsAddressInSmram(UINT64 address, UINTN size) {
    EFI_STATUS Status;
    UINTN mapSize = 0;
    EFI_SMRAM_DESCRIPTOR *smramMap = NULL;
    UINTN descriptorCount;
    UINTN i;
    
    // Get SMRAM map size
    Status = gSmst->SmmGetSmramMap(&mapSize, NULL);
    if (Status != EFI_BUFFER_TOO_SMALL) {
        return EFI_DEVICE_ERROR;
    }
    
    // Allocate buffer for SMRAM map
    smramMap = AllocatePool(mapSize);
    if (smramMap == NULL) {
        return EFI_OUT_OF_RESOURCES;
    }
    
    // Get SMRAM map
    Status = gSmst->SmmGetSmramMap(&mapSize, smramMap);
    if (EFI_ERROR(Status)) {
        FreePool(smramMap);
        return Status;
    }
    
    // Calculate descriptor count
    descriptorCount = mapSize / sizeof(EFI_SMRAM_DESCRIPTOR);
    
    // Check if address is within any SMRAM region
    for (i = 0; i < descriptorCount; i++) {
        EFI_PHYSICAL_ADDRESS regionStart = smramMap[i].PhysicalStart;
        EFI_PHYSICAL_ADDRESS regionEnd = regionStart + smramMap[i].CpuVisibleLength;
        
        if (address >= regionStart && (address + size) <= regionEnd) {
            FreePool(smramMap);
            return EFI_SUCCESS;
        }
    }
    
    FreePool(smramMap);
    return EFI_ACCESS_DENIED;
}
