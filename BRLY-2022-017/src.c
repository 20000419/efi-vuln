gSmst->SmiHandlerRegister)(SmiHandler, &UNKNOWN_PROTOCOL_2970687C_GUID, &Handle);
//The handler is located at offset 0x19D0:
EFI_STATUS __fastcall SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
  if ( CommBuffer && CommBufferSize && !gExitBootServicesFlag2EfiEventLegacyBootFlag )
  {
    if ( !gUnknownProtocol74d936fa )
    {
      if (gEfiBootServices->LocateProtocol)(&UNKNOWN_PROTOCOL_74D936FA_GUID, 0, &gUnknownProtocol74d936fa) < 0 )
        return 0;
