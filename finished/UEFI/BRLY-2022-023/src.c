EFI_STATUS __fastcall SwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  __int64 Ptr;
  __int16 Index;
  __int16 ResValue;
  UINTN Val;
  __int64 IhisiParamBufferValue;

  if ( ToGetIhisiParamBufferVar(&IhisiParamBufferValue, &Val, CommBuffer) >= EFI_SUCCESS )
  {
    Ptr = IhisiParamBufferValue;
    if ( *(IhisiParamBufferValue + 16) == 'BSI$' )
    {
      Index = *(*(IhisiParamBufferValue + 0x28) + 6);
      if ( (Index & 0xFFF8) == 80 )             // Index: 80, 81, 82, 83, 84, 85, 86, 87
        ResValue = (gFuncsTable[Index & 7])(*(IhisiParamBufferValue + 0x28));
      else
        ResValue = 0x82;
      *(Ptr + 8) = ResValue;
    }
  }
  return 0;
}
