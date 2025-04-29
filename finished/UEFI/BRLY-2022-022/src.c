//The handler is registered as shown below:
RegisterContext.Type = UsbLegacy;
RegisterContext.Device = &gDevicePath;
if ( (EfiSmmUsbDispatch2Protocol->Register(EfiSmmUsbDispatch2Protocol, UsbSmiHandler, &RegisterContext, &Handle) & 0x8000000000000000) != 0 ) return EFI_UNSUPPORTED;
//The pseudocode of USB SMI handler is shown below:

__int64 __fastcall UsbSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS]

  result = 0;
  if ( (MEMORY[0xC00F8094] & 0xF00) != 0 )
    result = (MEMORY[0xC00F8094] >> 8) & 0xF;
  v5 = UsbLegacyProtocolFunc1;
  if ( UsbLegacyProtocolFunc1 )
    result = UsbLegacyProtocolFunc1(result, UsbLegacyProtocolFunc2);
  if ( !gNotTheFirstTime )
  {
    OldTpl = (gBS->RaiseTPL)(31);
    (gBS->RestoreTPL)(OldTpl);
    if ( OldTpl == 31 )
      (gBS->RestoreTPL)(8);
    gNotTheFirstTime = 1;
    if ( (gBS->LocateHandleBuffer(ByProtocol, &ProprietaryProtocol, 0, &NoHandles, &Buffer) & 0x8000000000000000u) == 0 )
    {
      v7 = 0;
      if ( NoHandles )
      {
        while ( (gBS->HandleProtocol(Buffer[v7], &ProprietaryProtocol, &Interface) & 0x8000000000000000u) != 0
             || *(Interface + 24) )
        {
          if ( ++v7 >= NoHandles )
            goto _Exit;
        }
        UsbLegacyProtocolFunc1 = *(Interface + 1);
        UsbLegacyProtocolFunc2 = *(Interface + 2);
      }
    }
_Exit:
    result = gBS->FreePool(Buffer);
    if ( OldTpl == 31 )
      return (gBS->RaiseTPL)(31);
  }
  return result;
}
