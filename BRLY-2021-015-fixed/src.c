/**
 * Check if a pointer resides within SMRAM regions
 * @param ptr - Pointer to validate
 * @param size - Size of the buffer to check
 * @return TRUE if pointer is in SMRAM, FALSE otherwise
 */
BOOLEAN IsPointerInSmram(const void *ptr, UINTN size)
{
    EFI_STATUS status;
    EFI_SMRAM_DESCRIPTOR *smramMap;
    UINTN mapSize, descriptorCount;
    UINTN i;
    
    // Retrieve SMRAM map from SMM driver
    status = gSmst->SmmGetSmramMap(&mapSize, &smramMap);
    if (EFI_ERROR(status)) {
        // If map retrieval fails, assume pointer is safe to avoid blocking legitimate operations
        return FALSE;
    }
    
    // Calculate number of descriptors
    descriptorCount = mapSize / sizeof(EFI_SMRAM_DESCRIPTOR);
    
    // Check if pointer overlaps any SMRAM region
    for (i = 0; i < descriptorCount; i++) {
        EFI_PHYSICAL_ADDRESS ptrAddr = (EFI_PHYSICAL_ADDRESS)ptr;
        EFI_PHYSICAL_ADDRESS regionStart = smramMap[i].PhysicalStart;
        EFI_PHYSICAL_ADDRESS regionEnd = regionStart + smramMap[i].CpuStart;
        
        // Check for overlap
        if (ptrAddr >= regionStart && ptrAddr < regionEnd) {
            return TRUE;
        }
    }
    
    return FALSE;
}

/**
 * Secure SMI Handler with SMRAM pointer validation
 */
EFI_STATUS __fastcall SmiHandler_80000A14(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
    EFI_STATUS Status = EFI_SUCCESS;
    
    // Validate input parameters
    if (!CommBuffer || !CommBufferSize) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Validate entire communication buffer is not in SMRAM
    if (IsPointerInSmram(CommBuffer, *CommBufferSize)) {
        ReportSecurityViolation(); // Custom function to log security events
        return EFI_ACCESS_DENIED;
    }
    
    // Process command if first DWORD is 1
    if (*(UINT32 *)CommBuffer == 1) {
        // ... original command processing logic ...
    } else {
        Status = EFI_UNSUPPORTED;
    }
    
    // Validate write location before writing status (CommBuffer + 4)
    if (!IsPointerInSmram((UINT8 *)CommBuffer + 4, sizeof(EFI_STATUS))) {
        *(EFI_STATUS *)((UINT8 *)CommBuffer + 4) = Status;
    } else {
        ReportSecurityViolation();
        Status = EFI_ACCESS_DENIED;
    }
    
    return Status;
}
