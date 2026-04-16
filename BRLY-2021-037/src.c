EFI_STATUS __fastcall SmiHandler_1810(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        CommBufferStruct *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( CommBuffer && CommBufferSize && *CommBufferSize == 24 && CommBuffer->BufferPtr && CommBuffer->BufferSize )
  {
    Res = 0;
    if ( CommBuffer->BufferSize )
      Res = SmmIsBufferOutsideSmmValid(CommBuffer->BufferPtr, CommBuffer->BufferSize);
    if ( (-(Res == 0) & EFI_SECURITY_VIOLATION) == 0 )
    {
      if ( LOBYTE(CommBuffer->Case) )
      {
        if ( LOBYTE(CommBuffer->Case) != 1 )
        {
          Status = EFI_INVALID_PARAMETER;
_Exit:
          CommBuffer->Status = Status;
          return 0;
        }
      }
      else
      {
        gPointer = &gData;
      }
      // SMM memory corruption here
      Status = sub_189C(CommBuffer->BufferPtr);
      goto _Exit;
    }
  }
  return 0;
}

EFI_STATUS __fastcall sub_189C(char *Buffer)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  DstBuffer = Buffer;
  Status0 = EFI_INVALID_PARAMETER;
  Index = 0;
  if ( Buffer )
  {
    // Change the data pointed to by CommBuffer->BufferPtr
    ZeroMem(Buffer, 0x260);
    Status = EFI_SUCCESS;
    do
    {
      if ( Status )
        break;
      Status = EFI_INVALID_PARAMETER;
      if ( DstBuffer )
      {
        Value = Dref(&gData, gPointer);
        if ( Value == &gData )
        {
          Status = EFI_NOT_FOUND;
        }
        else
        {
          SrcBuffer = Value + 16;
          gPointer = Value;
          if ( Value != -16 && DstBuffer != SrcBuffer )
            // Change the data pointed to by CommBuffer->BufferPtr
            CopyMem(DstBuffer, SrcBuffer, 38);
          Status = EFI_SUCCESS;
        }
      }
      DstBuffer += 38;
      ++Index;
    }
    while ( Index < 0x10u );
    Status0 = Status;
    if ( Status == EFI_NOT_FOUND )
      return 0;
  }
  return Status0;
}
