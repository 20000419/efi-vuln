/**
 * Check if a buffer or specific offset within it resides in SMRAM
 * @param Buffer: Base address of the communication buffer
 * @param Offset: Offset from the buffer start to check (0 for full buffer check)
 * @param Size: Size of the data to validate at the specified offset
 * @return TRUE if the target address range is in SMRAM, FALSE otherwise
 */
BOOLEAN IsBufferOrOffsetInSmram(VOID *Buffer, UINTN Offset, UINTN Size) {
    EFI_STATUS Status;
    UINTN MapSize, DescriptorCount;
    EFI_SMRAM_DESCRIPTOR *SmramMap;
    UINTN i;
    EFI_PHYSICAL_ADDRESS TargetStart, TargetEnd;
    
    // Retrieve SMRAM memory map
    Status = gSmst->SmmGetSmramMap(&MapSize, &SmramMap);
    if (EFI_ERROR(Status)) return FALSE; // Fallback to safe assumption if map retrieval fails
    
    TargetStart = (EFI_PHYSICAL_ADDRESS)Buffer + Offset;
    TargetEnd = TargetStart + Size;
    
    DescriptorCount = MapSize / sizeof(EFI_SMRAM_DESCRIPTOR);
    for (i = 0; i < DescriptorCount; i++) {
        EFI_PHYSICAL_ADDRESS RegionStart = SmramMap[i].PhysicalStart;
        EFI_PHYSICAL_ADDRESS RegionEnd = RegionStart + SmramMap[i].CpuStart;
        
        // Check for address range overlap with SMRAM regions
        if ((TargetStart < RegionEnd) && (TargetEnd > RegionStart)) {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * Secure SMI Handler with SMRAM pointer validation
 */
EFI_STATUS __fastcall SmiHandler_1C10(
    EFI_HANDLE DispatchHandle,
    CONST VOID *Context,
    VOID *CommBuffer,
    UINTN *CommBufferSize
) {
    EFI_STATUS Status = EFI_SUCCESS;
    
    // Validate input parameters
    if (!CommBuffer || !CommBufferSize) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Validate entire communication buffer is not in SMRAM
    if (IsBufferOrOffsetInSmram(CommBuffer, 0, *CommBufferSize)) {
        ReportSecurityViolation(); // Implement security logging/alerting
        return EFI_ACCESS_DENIED;
    }
    
    // Process command if first QWORD is 1
    if (*(UINT64 *)CommBuffer == 1) {
        // ... Original command processing logic ...
    } else {
        Status = EFI_UNSUPPORTED;
    }
    
    // Validate write location before storing status (CommBuffer + 8, 8-byte QWORD)
    if (IsBufferOrOffsetInSmram(CommBuffer, 8, sizeof(EFI_STATUS))) {
        ReportSecurityViolation();
        return EFI_ACCESS_DENIED;
    }
    
    *((UINT64 *)CommBuffer + 1) = Status; // Safe write to non-SMRAM location
    
    return EFI_SUCCESS;
}
