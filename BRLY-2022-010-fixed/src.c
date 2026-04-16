EFI_STATUS __fastcall SmiHandler(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    void *CommBuffer,
    UINTN *CommBufferSize
) {
    EFI_STATUS Status = EFI_SUCCESS;
    EFI_SMRAM_DESCRIPTOR *SmramMap = NULL;
    UINTN SmramMapSize = 0, SmramDescriptorCount = 0;
    void *ptr = NULL;

    // Step 1: Validate CommBuffer and size before any operations
    if (!CommBuffer || !CommBufferSize || *CommBufferSize == 0) {
        return EFI_INVALID_PARAMETER;
    }

    // Step 2: Retrieve SMRAM descriptor map for validation
    Status = GetSmramMap(&SmramMapSize, &SmramMap, &SmramDescriptorCount);
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // Step 3: Check CommBuffer is outside SMRAM
    if (IsPointerInSmram(CommBuffer, *CommBufferSize, SmramMap, SmramDescriptorCount)) {
        return EFI_SECURITY_VIOLATION;
    }

    // Step 4: Allocate SMRAM buffer with size validation (example: max allowed size)
    const UINTN MAX_ALLOWED_SIZE = 0x1000; // Adjust based on actual needs
    if (*CommBufferSize > MAX_ALLOWED_SIZE) {
        return EFI_INVALID_PARAMETER;
    }

    ptr = SmmAllocateWrite(*CommBufferSize, CommBuffer);
    if (!ptr) {
        return EFI_OUT_OF_RESOURCES;
    }

    // Step 5: Validate all derived pointers against SMRAM
    // Validate nested_ptr (ptr + 5*QWORD)
    void *nested_ptr = (void *)*((UINT64 *)ptr + 5);
    if (nested_ptr && IsPointerInSmram(nested_ptr, sizeof(UINT64), SmramMap, SmramDescriptorCount)) {
        SmmFreeWrite(ptr);
        return EFI_SECURITY_VIOLATION;
    }

    // Validate ptr_plus40_ptr (ptr + 0x40)
    void *ptr_plus40_ptr = (char *)ptr + 0x40;
    if (IsPointerInSmram(ptr_plus40_ptr, 1, SmramMap, SmramDescriptorCount)) { // At least 1 byte check
        SmmFreeWrite(ptr);
        return EFI_SECURITY_VIOLATION;
    }

    // Validate ptr_plus18_ptr (ptr + 0x18)
    void *ptr_plus18_ptr = (char *)ptr + 0x18;
    if (IsPointerInSmram(ptr_plus18_ptr, 1, SmramMap, SmramDescriptorCount)) {
        SmmFreeWrite(ptr);
        return EFI_SECURITY_VIOLATION;
    }

    // Validate dest pointer calculation (critical vulnerability point)
    UINT64 offset = *((UINT64 *)ptr + 6); // Controllable offset
    void *dest = (char *)ptr + offset + 0x40;
    if (dest && IsPointerInSmram(dest, 1, SmramMap, SmramDescriptorCount)) { // Check if dest is in SMRAM
        SmmFreeWrite(ptr);
        return EFI_SECURITY_VIOLATION;
    }

    // Proceed with existing logic only if all validations pass
    if (*(_BYTE *)ptr) {
        // Read variable path (sub_800016FC)
        Status = sub_800016FC(
            (__int64)&v22,
            ptr_plus40_ptr,
            ptr_plus18_ptr,
            (char *)ptr + 0x38,
            (size_t *)ptr + 5,
            dest
        );
    } else {
        // Write variable path (sub_800018A8)
        Status = sub_800018A8(
            (__int64)&v22,
            ptr_plus40_ptr,
            ptr_plus18_ptr,
            *((UINT32 *)ptr + 0xE),
            nested_ptr,
            dest
        );
    }

    SmmFreeWrite(ptr);
    return Status;
}

// Helper function to check pointer overlap with SMRAM (same as prior fixes)
BOOLEAN IsPointerInSmram(
    VOID *Buffer,
    UINTN Size,
    EFI_SMRAM_DESCRIPTOR *SmramMap,
    UINTN DescriptorCount
) {
    VOID *End = (VOID *)((UINTN)Buffer + Size);
    for (UINTN i = 0; i < DescriptorCount; i++) {
        if ((UINTN)Buffer < (SmramMap[i].PhysicalStart + SmramMap[i].PhysicalSize) &&
            (UINTN)End > SmramMap[i].PhysicalStart) {
            return TRUE; // Overlaps with SMRAM
        }
    }
    return FALSE;
}
