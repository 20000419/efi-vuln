EFI_STATUS __fastcall SmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  if (CommBuffer && CommBufferSize) {
    // Validate buffer size is at least large enough for status write (8 bytes beyond CommBuffer)
    if (*CommBufferSize < sizeof(UINT64) + 4) { // Adjust based on actual required buffer space
      status = EFI_INVALID_PARAMETER;
      goto _Exit;
    }

    // Check if buffer and write location (CommBuffer + 8) are outside SMRAM
    if (!SmmIsBufferOutsideSmmValid(CommBuffer, *CommBufferSize) ||
        !SmmIsBufferOutsideSmmValid((UINT8*)CommBuffer + 8, sizeof(UINT64))) {
      status = EFI_SECURITY_VIOLATION;
      goto _Exit;
    }

    Res = *(_DWORD *)CommBuffer < 8;
    Value = *((_BYTE *)CommBuffer + 4);
    if (!Res)
      goto _InvalidParameter;
    if (*(_DWORD *)CommBuffer) {
      switch (*(_DWORD *)CommBuffer) {
        case 1:
        case 3:
        case 7:
_Case1:
          Flag = 0;
          goto _HpPolicy;
        case 2:
        case 4:
_Case2:
          Flag = 1;
          goto _HpPolicy;
        default:
          if (*(_DWORD *)CommBuffer == 6)
            goto _Case1; // Fall through to _HpPolicy via case 1 logic
_InvalidParameter:
          status = EFI_INVALID_PARAMETER;
          goto _Exit;
      }
_HpPolicy:
      status = HpPolicy(&Value, *(_DWORD *)CommBuffer, *((_QWORD *)CommBuffer + 2));
      if (Flag && !status)
        *((_BYTE *)CommBuffer + 4) = Value;
    }
  }

_Exit:
  // Only write status if buffer is valid (ensured by prior checks)
  if (CommBuffer && CommBufferSize && *CommBufferSize >= sizeof(UINT64)) {
    *((_QWORD *)CommBuffer + 1) = status;
  }
  return 0;
}
