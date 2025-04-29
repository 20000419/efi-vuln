//In the function at offset 0x172C (image sha256: 9f110c958f2dae1c40369babcf3511324e7bc7f24e6b87c58ea74de7d4bcdb86), the child software System Management Interrupt (SWSMI) handler with GUID 2970687c-618c-4de5-b8f9-6c7576dca83d is registered:

Handle = 0;
gSmst_80005570->SmiHandlerRegister(SmiHandler_800016B0, &gSmiHandlerGuid, &Handle);
Handle = 0;
return gBS_80005240->InstallProtocolInterface(
            &Handle,
            &ProprietaryProtocol_80005190,
            EFI_NATIVE_INTERFACE,
            0);
//Below is the decompiled SWSMI handler code:

EFI_STATUS __fastcall SmiHandler_800016B0(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  EFI_STATUS Status; // rax

  if ( CommBuffer && CommBufferSize && !gExitBootServices && *CommBufferSize == 0x1020 )
  {
    switch ( *CommBuffer )
    {
      case 2:
        Status = sub_80002B00(CommBuffer + 32, *(CommBuffer + 2), *(CommBuffer + 3));
        goto _WriteStatus;
      case 3:
        Status = sub_80002A38(*(CommBuffer + 2), CommBuffer + 32, CommBuffer + 3, *(CommBuffer + 2));
        goto _WriteStatus;
      case 4:
        Status = sub_800029A4(*(CommBuffer + 2), *(CommBuffer + 3));
_WriteStatus:
        *(CommBuffer + 1) = Status;
        break;
    }
  }
  return 0;
}
