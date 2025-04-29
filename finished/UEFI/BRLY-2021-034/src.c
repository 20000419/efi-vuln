EFI_STATUS __fastcall SmiHandler_1690(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        CommBufferStruct *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( CommBuffer && CommBufferSize && (-(*CommBufferSize != 32) & EFI_INVALID_PARAMETER) == 0 )
  {
    Status = EFI_UNSUPPORTED;
    if ( !gComparePointersRes )
    {
      if ( gSmst )
        Status = -(CommBuffer->Case != 0) & EFI_UNSUPPORTED;
      goto _Exit;
    }
    Case = CommBuffer->Case;
    if ( Case )
    {
      Case1 = (Case - 1);
      if ( Case1 )
      {
        Case2 = Case1 - 1;
        if ( !Case2 )
        {
          Status = EFI_NOT_FOUND;
          if ( gFlag )
          {
            CommBuffer->Flag = gFlag;
            Status = 0;
          }
          goto _Exit;
        }
        Case3 = (Case2 - 1);
        if ( Case3 )
        {
          Case4 = (Case3 - 1);
          if ( Case4 )
          {
            if ( Case4 == 1 )
            {
              if ( gSrcBuffer && MEMORY[0xFED40F00] == 0x1050 )
              {
                NewSize = gSrcBuffer;
                DstSize = CommBuffer->DstSize;
                SrcBufferSize = *gSrcBuffer;
                if ( DstSize < SrcBufferSize )
                {
                  Status = EFI_BUFFER_TOO_SMALL;
                }
                else
                {
                  Dst = CommBuffer->Dst;
                  if ( Dst )
                  {
                    CopyMemS(Dst, DstSize, gSrcBuffer + 2, SrcBufferSize);
                    NewSize = gSrcBuffer;
                  }
                  Status = 0;
                }
                CommBuffer->DstSize = *NewSize;
              }
              ...
            }
            ...
          }
          ...
        }
        ...
      }
      ...
    }
    ...
  }
  return 0;
}
