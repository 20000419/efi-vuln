/**
 * Check if a buffer resides within SMRAM regions
 * @param Buffer - Pointer to buffer
 * @param Size - Size of buffer in bytes
 * @return TRUE if buffer is in SMRAM, FALSE otherwise
 */
BOOLEAN IsBufferInSmram(VOID *Buffer, UINTN Size) {
    EFI_STATUS Status;
    UINTN MapSize, DescriptorCount;
    EFI_SMRAM_DESCRIPTOR *SmramMap;
    UINTN i;
    
    // Retrieve SMRAM map from SMM Access Protocol
    Status = gSmst->SmmGetSmramMap(&MapSize, &SmramMap);
    if (EFI_ERROR(Status)) return FALSE; // Fail safe if map retrieval fails
    
    DescriptorCount = MapSize / sizeof(EFI_SMRAM_DESCRIPTOR);
    EFI_PHYSICAL_ADDRESS BufferStart = (EFI_PHYSICAL_ADDRESS)Buffer;
    EFI_PHYSICAL_ADDRESS BufferEnd = BufferStart + Size;
    
    for (i = 0; i < DescriptorCount; i++) {
        EFI_PHYSICAL_ADDRESS RegionStart = SmramMap[i].PhysicalStart;
        EFI_PHYSICAL_ADDRESS RegionEnd = RegionStart + SmramMap[i].CpuStart;
        
        // Check for address range overlap with SMRAM
        if ((BufferStart < RegionEnd) && (BufferEnd > RegionStart)) {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * Secure SMI Handler with SMRAM pointer validation
 */
EFI_STATUS __fastcall SmiHandler_1278(
    EFI_HANDLE DispatchHandle,
    CONST VOID *Context,
    VOID *CommBuffer,
    UINTN *CommBufferSize
) {
    if (!CommBuffer || !CommBufferSize) {
        return EFI_INVALID_PARAMETER;
    }
    
    // Validate communication buffer is not in SMRAM
    if (IsBufferInSmram(CommBuffer, *CommBufferSize)) {
        ReportSecurityViolation(); // Custom function to log security events
        return EFI_ACCESS_DENIED;
    }
    
    if (*(UINT64 *)CommBuffer == 1) {
        // Validate before calling subroutine that modifies CommBuffer
        if (IsBufferInSmram((UINT8 *)CommBuffer + 8, 24)) { // Check 3 QWORDS (24 bytes) of writes
            ReportSecurityViolation();
            return EFI_ACCESS_DENIED;
        }
        sub_80001454(CommBuffer);
    }
    return EFI_SUCCESS;
}

/**
 * Secure subroutine with SMRAM write protection
 */
__int64 __fastcall sub_80001454(VOID *CommBuffer) {
    UINTN RangeCount = gSmramRangeCount;
    UINTN TotalSize = 0;
    UINTN *p_PhysicalSize;
    
    if (RangeCount == 0) {
        *((UINT64 *)CommBuffer + 2) = 0;
        return EFI_SUCCESS;
    }
    
    p_PhysicalSize = &SmramMap->PhysicalSize; // Assume SmramMap is SMM-owned and safe
    
    // Calculate total SMRAM size (original logic)
    do {
        TotalSize += *p_PhysicalSize;
        p_PhysicalSize += 4;
    } while (--RangeCount);
    
    // Validate each write location in CommBuffer before modification
    // Write 2nd QWORD (offset 8): TotalSize
    if (!IsBufferInSmram((UINT8 *)CommBuffer + 8, sizeof(UINT64))) {
        *((UINT64 *)CommBuffer + 2) = TotalSize;
    } else {
        ReportSecurityViolation();
        return EFI_ACCESS_DENIED;
    }
    
    // Write 3rd QWORD (offset 16): 0
    if (!IsBufferInSmram((UINT8 *)CommBuffer + 16, sizeof(UINT64))) {
        *((UINT64 *)CommBuffer + 1) = 0;
    } else {
        ReportSecurityViolation();
        return EFI_ACCESS_DENIED;
    }
    
    // Write 4th QWORD (offset 24): Value (assuming Value is safe)
    if (!IsBufferInSmram((UINT8 *)CommBuffer + 24, sizeof(UINT64))) {
        *((UINT64 *)CommBuffer + 3) = Value;
    } else {
        ReportSecurityViolation();
        return EFI_ACCESS_DENIED;
    }
    
    return EFI_SUCCESS;
}
