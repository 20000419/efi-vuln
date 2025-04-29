FI_STATUS __fastcall SmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  Interface = 0;
  if ( CommBuffer && CommBufferSize )
  {
    Res = gSmst->SmmLocateProtocol(&ProprietaryProtocol_8, 0, &Interface);
    if ( !Res )
      Res = (*Interface)();
    *CommBuffer = Res;
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
