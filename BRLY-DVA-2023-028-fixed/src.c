EFI_STATUS __fastcall ChildSwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        char *CommBuffer,
        UINTN *CommBufferSize)
{
  __int64 Ptr; // [rsp+20h] [rbp-18h]

  // Validate communication buffer size to prevent out-of-bounds access
  const UINTN MIN_BUFFER_SIZE = 24; // Minimum size to safely access CommBuffer + 24
  if (CommBuffer == NULL || *CommBufferSize < MIN_BUFFER_SIZE) {
    return EFI_INVALID_PARAMETER;
  }

  Ptr = *(CommBuffer + 4);
  if (Ptr) {
    // Additional check to ensure Ptr points to valid memory (optional but recommended)
    // (Example: Check if Ptr is within non-SMRAM regions using SmmGetSmramMap)
    
    (*(Ptr + 8))(Ptr, gSmst, CommBuffer + 24);
    
    // Ensure write operation is within valid buffer bounds
    if ((UINTN)((_QWORD *)CommBuffer + 4) <= (UINTN)CommBuffer + *CommBufferSize) {
      *((_QWORD *)CommBuffer + 4) = 0;
    } else {
      return EFI_BUFFER_TOO_SMALL;
    }
  }
  return EFI_SUCCESS;
}
