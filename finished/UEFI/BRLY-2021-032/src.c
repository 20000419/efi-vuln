EFI_STATUS __fastcall SmiHandler_2158(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        _QWORD *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  Num = 4;
  if ( CommBuffer && CommBufferSize && (-(__int64)(*CommBufferSize != 24) & EFI_INVALID_PARAMETER) == 0 )
  {
    Size = GetStrSize((_WORD *)CommBuffer[1]);
    CommBuffer1 = CommBuffer[1];
    Size1 = Size;
    Res = 0;
    if ( CommBuffer1 && Size1 )
      Res = SmmIsBufferOutsideSmmValid(CommBuffer1, Size1);
    if ( (-(__int64)(Res == 0) & EFI_INVALID_PARAMETER) == 0 )
    {
      if ( *(_BYTE *)CommBuffer )
      {
        if ( *(_BYTE *)CommBuffer == 1 )
        {
          if ( GetWideStrSize((_WORD *)CommBuffer[1]) )
          {
            Res1 = FactoryConfigHandler((_WORD *)CommBuffer[1], (__int64)&Num, 1);// possible heap overflow
            goto _Exit;
          }
        }
        else if ( *(_BYTE *)CommBuffer == 2 )
        {
          Res1 = BuildIdHandler((_WORD *)CommBuffer[1], (__int64)&Num, 1);// possible heap overflow
_Exit:
          CommBuffer[2] = Res1;
          return 0;
        }
      }
      else if ( GetWideStrSize((_WORD *)CommBuffer[1]) )
      {
        CommBuffer[2] = Validate((_WORD *)CommBuffer[1]) ? 0 : EFI_CRC_ERROR;
        return 0;
      }
      CommBuffer[2] = EFI_INVALID_PARAMETER;
    }
  }
  return 0;
}

//Consider the FactoryConfigHandler function.

Status = SmmGetVariable(L"FactoryConfig", &VariableValue);
if ( Stautus )
    goto _Exit;
if ( GetWideStrSize(StringFromCommBufferPtr) )
{
    StrSize = GetStrSize(StringFromCommBufferPtr);
    Value = VariableValue;
    if ( VariableValue && StrSize )
    {
        if ( StrSize > 500 )
        StrSize = 500;
        if ( VariableValue != StringFromCommBufferPtr )
        CopyMem(VariableValue, StringFromCommBufferPtr, StrSize);
    }
...
}
