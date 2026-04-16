EFI_STATUS __fastcall ChildSwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        char *CommBuffer,
        UINTN *CommBufferSize)
{
  __int64 Ptr; // [rsp+20h] [rbp-18h]

  Ptr = *(CommBuffer + 4);
  if ( Ptr )
  {
    (*(Ptr + 8))(*Ptr, gSmst, CommBuffer + 24);
    *((_QWORD *)CommBuffer + 4) = 0; // Arbitrary write (*CommBufferSize is not checked)
  }
  return EFI_SUCCESS;
}
