EFI_STATUS __fastcall SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT64 buffer_ptr = 0;
  UINT32 buffer_size = 0;
  UINTN required_size = 0x22; // Minimum size to avoid OOB (0x20 + 2 bytes)

  if (CommBuffer && CommBufferSize && *CommBufferSize == 0x18) {
    buffer_ptr = *(_QWORD *)CommBuffer;
    buffer_size = *((_DWORD *)CommBuffer + 2); // Pointer to size (4 bytes)

    if (!buffer_ptr || !buffer_size) {
      Status = EFI_INVALID_PARAMETER;
      goto Exit;
    }

    // Validate buffer_ptr is outside SMRAM with sufficient size
    if (!CheckSmramMap_0(buffer_ptr, required_size)) {
      Status = EFI_SECURITY_VIOLATION;
      goto Exit;
    }

    // Validate size pointer itself is outside SMRAM
    if (!CheckSmramMap_0((UINT64)((char *)CommBuffer + 8), 4)) {
      Status = EFI_SECURITY_VIOLATION;
      goto Exit;
    }

    // Ensure buffer size is large enough to avoid OOB write (ptr + 2 + 0x20)
    if (buffer_size < required_size) {
      Status = EFI_BUFFER_TOO_SMALL;
      goto Exit;
    }

    // Proceed with original logic
    if (CommBuffer_1[3]) {
      Status = EFI_UNSUPPORTED;
    } else {
      Status = sub_800024D0((_BYTE *)buffer_ptr);
    }
  } else {
    Status = EFI_INVALID_PARAMETER;
  }

Exit:
  *((_QWORD *)CommBuffer + 2) = Status;
  return EFI_SUCCESS;
}

__int64 __fastcall sub_800024D0(_BYTE *ptr)
{
  EFI_STATUS Status = EFI_SUCCESS;
  UINT8 buffer[0x20] = {0};
  UINTN copy_size = 0x20;

  // Retrieve data into buffer (assuming this is SMM-safe)
  Status = UnknownProtocol53986f2e(buffer, v10);
  if (!EFI_ERROR(Status)) {
    // Validate ptr can safely receive the copy (ptr + 2 + 0x20)
    if (CheckSmramMap_0((UINT64)ptr, copy_size + 2)) {
      memcpy(ptr + 2, buffer, copy_size); // Safe copy
    } else {
      Status = EFI_SECURITY_VIOLATION;
    }
  }

  return Status;
}
