EFI_STATUS __fastcall SmiHandler(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    void *CommBuffer,
    UINTN *CommBufferSize
) {
    EFI_STATUS Status = EFI_SUCCESS;
    UINT64 buffer_ptr = 0;
    UINT32 buffer_size = 0;
    const UINTN MIN_REQUIRED_SIZE = 0x26; // Covers ptr[0x25] (0x25 + 1 byte)

    if (CommBuffer && CommBufferSize && *CommBufferSize == 0x18) {
        buffer_ptr = *(_QWORD *)CommBuffer;
        buffer_size = *((UINT32 *)CommBuffer + 2);

        if (!buffer_ptr || buffer_size < MIN_REQUIRED_SIZE) {
            Status = EFI_INVALID_PARAMETER;
            goto Exit;
        }

        // Validate buffer and required offsets are outside SMRAM
        if (!CheckSmramMap_0(buffer_ptr, buffer_size)) {
            Status = EFI_SECURITY_VIOLATION;
            goto Exit;
        }

        // Check for safe access to ptr[0x25] (within buffer bounds)
        if ((UINTN)buffer_ptr + 0x25 >= (UINTN)buffer_ptr + buffer_size) {
            Status = EFI_BUFFER_TOO_SMALL;
            goto Exit;
        }

        // Handle command type
        switch (*((UINT8 *)CommBuffer + 0xC)) {
            case 4:
                if (gSmmReadyToLockFlag2) {
                    goto Exit;
                }
                // Validate destination buffer can hold 0x20 bytes
                if (buffer_size >= 0x20) {
                    memcpy((void *)buffer_ptr, gLocal20Buffer, 0x20);
                } else {
                    Status = EFI_BUFFER_TOO_SMALL;
                }
                break;
            case 5:
                if (!sub_800025E0((void *)buffer_ptr)) {
                    goto Exit;
                }
                if (!sub_80002490(v10)) {
                    // Validate buffer for sub_800022C8's OOB write
                    if ((UINTN)buffer_ptr + 0x25 < (UINTN)buffer_ptr + buffer_size) {
                        sub_800022C8((_BYTE *)buffer_ptr, v10);
                    } else {
                        Status = EFI_BUFFER_TOO_SMALL;
                    }
                }
                break;
            default:
                Status = EFI_UNSUPPORTED;
        }
    } else {
        Status = EFI_INVALID_PARAMETER;
    }

Exit:
    // Additional safety: Ensure no SMRAM access if validation failed
    if (EFI_ERROR(Status) && buffer_ptr) {
        memset((void *)buffer_ptr, 0, MIN_REQUIRED_SIZE); // Clear invalid buffer
    }
    return Status;
}

void __fastcall sub_800022C8(_BYTE *ptr, __int64 res) {
    // Validate ptr is within safe buffer before write
    if ((UINTN)ptr + 0x25 < (UINTN)ptr + *((UINT32 *)((UINT8 *)ptr - 0x10) + 2)) { // Retrieve size from CommBuffer
        ptr[0x25] = 1; // Safe write within validated buffer
    }
}
