EFI_STATUS __fastcall SmiHandler(
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
      Length = *CommBufferSize;
      if ( (-(*CommBufferSize != 160) & EFI_INVALID_PARAMETER) == 0 )
      {
        Res = 0;
        if ( Length )
          Res = SmmIsBufferOutsideSmmValid(CommBuffer, Length);
        if ( (-(Res == 0) & EFI_INVALID_PARAMETER) == 0 )
        {
          Status = -(*CommBuffer != 'GFCU') & EFI_INVALID_PARAMETER;
          if ( *CommBuffer == 'GFCU' )
          {
            switch ( *(CommBuffer + 1) )
            {
              case 0x10:
                if ( !gBuffer )
                {
                  Buffer = GetCopy(0x78, CommBuffer + 24);
                  BufferSize = *(CommBuffer + 2);
                  BufferPtr = *(CommBuffer + 1);
                  gBuffer = Buffer;
                  sub_261C(BufferPtr, BufferSize);
                  PcdProtocol = LocatePcdProtocol();
                  if ( (PcdProtocol->Get8)(0x23B) == 1 )
                    FreeAndUnregister();
                }
                break;
              ...
              default:
_InvalidParameter:
                Status = EFI_INVALID_PARAMETER;
                break;
            }
          }
          *(CommBuffer + 19) = Status;
        }
      }
    }
  }
  return 0;
}
