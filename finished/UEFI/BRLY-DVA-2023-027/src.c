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
    (*(Ptr + 8))(*Ptr, gSmst, CommBuffer + 24); // Arbitrary function call
    *(CommBuffer + 4) = 0;
  }
  return EFI_SUCCESS;
}
