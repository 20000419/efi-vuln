//In the function at offset 0x1068 (image sha256:4143f3774dd14fcfc1afc3d7ee774f97e4ca556032bbc7c3133f5ba9b0045402), the child software System Management Interrupt (SWSMI) handler with GUID 56947330-585c-4470-a95d-c55c529feb47 is registered:

if ( SmstIsNotNull() )
{
  Handle1 = 0;
  gBS->InstallProtocolInterface(&Handle1, &ProprietaryProtocol_D8C0, EFI_NATIVE_INTERFACE, 0);
  gHandle = Handle;
  return gSmst_E718->SmiHandlerRegister(SmiHandler_1C10, &gSmiHandlerGuid, &DispatchHandle);
}
//Below is the decompiled SWSMI handler code:

EFI_STATUS __fastcall SmiHandler_1C10(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( CommBuffer && CommBufferSize )
  {
    if ( *(_QWORD *)CommBuffer == 1 )
    {
      ...
    }
    else
    {
      Status = EFI_UNSUPPORTED;
    }
_WriteStatus:
    *((_QWORD *)CommBuffer + 1) = Status;
  }
  return 0;
}
