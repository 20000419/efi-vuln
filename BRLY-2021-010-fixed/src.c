/**
 * Validate that a pointer does not lie within SMRAM.
 * 
 * @param ptr The pointer to validate.
 * @return EFI_SUCCESS if the pointer is valid, EFI_SECURITY_VIOLATION otherwise.
 */
EFI_STATUS ValidateNonSmramPointer(void *ptr) {
    EFI_STATUS status;
    UINTN regionCount = 0;
    EFI_SMRAM_DESCRIPTOR *smramMap = NULL;
    
    // Get SMRAM map
    status = gSmst->SmmGetSmramMap(&regionCount, &smramMap);
    if (EFI_ERROR(status)) {
        return status;
    }
    
    // Check if pointer lies within any SMRAM region
    for (UINTN i = 0; i < regionCount; i++) {
        EFI_PHYSICAL_ADDRESS smramStart = smramMap[i].PhysicalStart;
        EFI_PHYSICAL_ADDRESS smramEnd = smramStart + smramMap[i].RegionLength;
        
        if ((UINTN)ptr >= smramStart && (UINTN)ptr < smramEnd) {
            return EFI_SECURITY_VIOLATION;
        }
    }
    
    return EFI_SUCCESS;
}

/**
 * Validate all nested pointers in the communication buffer.
 * 
 * @param commBuffer The communication buffer.
 * @return EFI_SUCCESS if all pointers are valid, EFI_SECURITY_VIOLATION otherwise.
 */
EFI_STATUS ValidateNestedPointers(void *commBuffer) {
    EFI_STATUS status;
    UINT64 nestedPtr;
    
    // Validate gCommBuffer_plus10_val
    nestedPtr = *((UINT64 *)commBuffer + 2);
    status = ValidateNonSmramPointer((void *)nestedPtr);
    if (EFI_ERROR(status)) {
        return status;
    }
    
    // Validate other nested pointers if necessary
    // ...
    
    return EFI_SUCCESS;
}

EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    EFI_STATUS status;
    
    if (gUnknownProtocol == CommBuffer && *CommBufferSize == 0x20 && CommBuffer)
    {
        // Validate the communication buffer itself
        status = ValidateNonSmramPointer(CommBuffer);
        if (EFI_ERROR(status)) {
            return status;
        }
        
        gCommBuffer_plus10_val = *((UINT64 *)CommBuffer + 2);
        
        // Validate nested pointers
        status = ValidateNestedPointers(CommBuffer);
        if (EFI_ERROR(status)) {
            return status;
        }
        
        if (*(UINT64 *)CommBuffer == 1)
        {
            status = sub_8000358C();
            if (status < 0)
                return status;
        }
        else
        {
            if (*(UINT64 *)CommBuffer != 3)
                return EFI_INVALID_PARAMETER;
            sub_80003484();
        }
    }

    return EFI_SUCCESS;
}
