EFI_STATUS __fastcall SmiHandler_1988(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( CommBuffer )
  {
    if ( CommBufferSize )
    {
      if ( *(_DWORD *)CommBuffer == 'DFCH'
        && !gBS->AllocatePool(EfiBootServicesData, 175 * BlocksNum, (void **)CommBuffer + 2) )
      {
        DstBuffer = *((_QWORD *)CommBuffer + 2);
        Size = 175 * BlocksNum;
        *((_QWORD *)CommBuffer + 1) = BlocksNum;
        if ( DstBuffer )
        {
          if ( Size && gSrcBuffer && DstBuffer != gSrcBuffer )
            CopyMem(DstBuffer, gSrcBuffer, Size);
        }
      }
    }
  }
  return 0;
}
