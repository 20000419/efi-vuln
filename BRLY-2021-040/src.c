EFI_STATUS __fastcall SmiHandler_17C8
(
        EFI_HANDLE DispatchHandle,
        const void
 *Context,
        CommBufferStruct *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if
 ( CommBuffer )
  {
    if
 ( CommBufferSize )
    {
      Size = *CommBufferSize;
      if ( (-(*CommBufferSize != 160) & EFI_INVALID_PARAMETER) == 0
 )
      {
        Res = 0
;
        if
 ( Size )
          Res = SmmIsBufferOutsideSmmValid
(CommBuffer, Size);
        if ( (-(Res == 0) & EFI_INVALID_PARAMETER) == 0
 )
        {
          Status = -(CommBuffer->Sig != 'GFCU'
) & EFI_INVALID_PARAMETER;
          if ( CommBuffer->Sig == 'GFCU'
 )
          {
            if ( CommBuffer->Case == 16
 )
            {
              if
 ( !gBufferPtr1 )
              {
                BufferPtr1 = GetCopy(120
, &CommBuffer->BufferPtr1);
                BufferSize = CommBuffer->BufferSize;
                BufferPtr = CommBuffer->BufferPtr;
                gBufferPtr1 = BufferPtr1;
                sub_2288
(BufferPtr, BufferSize);
                // Vulnerability here
                PcdProtocol = BsLocatePcdProtocol
();
                if ( (PcdProtocol->Get8)(0x2C4) == 1
 )
                  HandlerUnregister
();
              }
            }
            ...
          }
          ...
        }
      }
    }
  }
  return 0
;
}
