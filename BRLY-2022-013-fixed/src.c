EFI_STATUS __fastcall SmiHandler(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    void *CommBuffer,
    UINTN *CommBufferSize
) {
    EFI_STATUS Status = EFI_SUCCESS;
    UINT8 *gCommBufferCopy = NULL;
    const UINTN MAX_BUFFER_SIZE = 0x288;
    const UINTN MAX_ITERATIONS = MAX_BUFFER_SIZE / 0x20; // Safely limit iterations by entry size
    UINTN counter, offset, remaining_size;

    if (CommBuffer && CommBufferSize && *CommBufferSize == MAX_BUFFER_SIZE) {
        // Allocate SMRAM buffer with size validation
        Status = SmmAllocateZeroWrapper((VOID **)&gCommBufferCopy, MAX_BUFFER_SIZE);
        if (!gCommBufferCopy || EFI_ERROR(Status)) {
            return EFI_OUT_OF_RESOURCES;
        }

        // Copy and validate original buffer
        memcpy(gCommBufferCopy, CommBuffer, MAX_BUFFER_SIZE);
        UINT8 string_count = gCommBufferCopy[0x282];

        // Prevent excessive iterations (each entry is 0x20 bytes, including offset)
        if (string_count > MAX_ITERATIONS) {
            Status = EFI_INVALID_PARAMETER;
            goto Exit;
        }

        offset = 0;
        for (counter = 0; counter < string_count; counter++) {
            // Get WString pointer from original buffer (validate within 0x288 bytes)
            UINT16 *str_ptr = *(UINT16 **)((UINT8 *)CommBuffer + offset + 0x18);
            if ((UINTN)str_ptr < (UINTN)CommBuffer || 
                (UINTN)str_ptr >= (UINTN)CommBuffer + MAX_BUFFER_SIZE) {
                Status = EFI_SECURITY_VIOLATION;
                goto Exit;
            }

            // Calculate max allowed length for this entry (remaining buffer space)
            remaining_size = MAX_BUFFER_SIZE - (offset + 0x18);
            UINTN max_str_len = remaining_size / 2; // Each WORD is 2 bytes

            // Safely get string length with hard limit and buffer-aware cap
            UINTN strlen_inwords = GetWStringLengthInWords(str_ptr, 
                MIN(max_str_len, 1000000)); // Cap to buffer-safe length

            // Calculate destination in SMRAM buffer and validate space
            UINT8 *dest_ptr = gCommBufferCopy + offset + 0x18;
            if ((UINTN)dest_ptr + 2 * strlen_inwords + 2 > (UINTN)gCommBufferCopy + MAX_BUFFER_SIZE) {
                Status = EFI_BUFFER_TOO_SMALL;
                goto Exit;
            }

            // Copy with buffer-aware size (prevents OOB write)
            Status = WStringCopy((UINT64)dest_ptr, 
                (UINTN)(2 * strlen_inwords + 2), str_ptr);
            if (EFI_ERROR(Status)) {
                goto Exit;
            }

            offset += 0x20; // Move to next entry (maintain fixed entry spacing)
        }
    } else {
        Status = EFI_INVALID_PARAMETER;
    }

Exit:
    if (gCommBufferCopy) {
        SmmFreeWrapper(gCommBufferCopy);
    }
    return Status;
}

// Updated WString length function with strict buffer checks
unsigned __int64 __fastcall GetWStringLengthInWords(UINT16 *a1, unsigned __int64 a2) {
    unsigned __int64 result = 0;
    if (!a1 || !a2) return 0;
    while (result < a2 - 1 && result < 0x1000) { // Added conservative hard limit
        if (!a1[result]) break; // Stop at null terminator
        result++;
    }
    return result;
}

// Updated WString copy function with buffer boundary checks
MACRO_EFI __fastcall WStringCopy(UINT64 dest, UINTN size, UINT16 *src) {
    if (!dest || !src || size == 0 || size > 0x200) { // Enforce buffer-safe size limit
        return EFI_INVALID_PARAMETER;
    }
    UINTN len = GetWStringLengthInWords(src, size);
    if (len >= size / 2) { // Ensure room for null terminator
        return EFI_BUFFER_TOO_SMALL;
    }
    // Safe copy with boundary checks (assuming dest is within SMRAM buffer)
    CopyMem((VOID *)dest, src, 2 * len + 2);
    return EFI_SUCCESS;
}
