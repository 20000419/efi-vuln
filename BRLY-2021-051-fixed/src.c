EFI_STATUS __fastcall SmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  EFI_STATUS Res = EFI_UNSUPPORTED;
  void *Interface = NULL;

  if (CommBuffer && CommBufferSize) {
    // Validate buffer size is at least large enough for the status write (e.g., sizeof(EFI_STATUS))
    if (*CommBufferSize < sizeof(EFI_STATUS)) {
      Res = EFI_INVALID_PARAMETER;
      goto Exit;
    }

    // Check if the entire buffer (including write location) is outside SMRAM
    if (!SmmIsBufferOutsideSmmValid(CommBuffer, sizeof(EFI_STATUS))) {
      Res = EFI_SECURITY_VIOLATION;
      goto Exit;
    }

    // Safely locate the proprietary protocol (SMM-safe call)
    Res = gSmst->SmmLocateProtocol(&ProprietaryProtocol_8, NULL, &Interface);
    if (!EFI_ERROR(Res) && Interface) {
      Res = ((EFI_STATUS (*)())Interface)(); // Assuming the protocol function returns EFI_STATUS
    }
  }

Exit:
  // Only write to buffer if all validations pass
  if (CommBuffer && !EFI_ERROR(Res)) {
    *(EFI_STATUS *)CommBuffer = Res; // Safe write to validated buffer
  }
  return EFI_SUCCESS;
}
