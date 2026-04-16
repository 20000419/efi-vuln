EFI_STATUS __fastcall SmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( CommBuffer && CommBufferSize )
  {
    Res = *(_DWORD *)CommBuffer < 8;
    Value = *((_BYTE *)CommBuffer + 4);
    if ( !Res )
      goto _InvalidParameter;
    if ( *(_DWORD *)CommBuffer )
    {
      switch ( *(_DWORD *)CommBuffer )
      {
        case 1:
          goto _Case1;
        case 2:
          goto _Case2;
        case 3:
          goto _Case1;
        case 4:
          goto _Case2;
        case 5:
_Case1:
          Flag = 0;
_HpPolicy:
          status = HpPolicy(&Value, *(_DWORD *)CommBuffer, *((_QWORD *)CommBuffer + 2));
          if ( Flag && !status )
            *((_BYTE *)CommBuffer + 4) = Value;
          goto _Exit;
      }
      if ( *(_DWORD *)CommBuffer != 6 )
      {
        if ( *(_DWORD *)CommBuffer == 7 )
          goto _Case1;
_InvalidParameter:
        status = EFI_INVALID_PARAMETER;
_Exit:
        *((_QWORD *)CommBuffer + 1) = status;
        return 0;
      }
    }
_Case2:
    Flag = 1;
    goto _HpPolicy;
  }
  return 0;
}
//Before SMI handler will be triggered, CommBuffer will be checked for overlap with SMRAM (inside PiSmmCommunicationSmm module):

EFI_STATUS __fastcall SwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  Status = 0;
  CommunicationHeader = *gCommunicationHeader;
  if ( *gCommunicationHeader )
  {
    if ( SmmIsBufferOutsideSmmValid(*gCommunicationHeader, 24) )
    {
      CommBufferSizea[0] = CommunicationHeader->MessageLength;
      if ( SmmIsBufferOutsideSmmValid(CommunicationHeader->Data, CommBufferSizea[0]) )
        Status = gSmst->SmiManage(
                   &CommunicationHeader->HeaderGuid,
                   0,
                   CommunicationHeader->Data,
                   CommBufferSizea);
    }
  }
  return -(Status != 0) & 0xA000000000000000;
}

