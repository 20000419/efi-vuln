//In the function at offset 0xEBC (image sha256: 4b91d7456d48b897106f97d419426840ef3c62844797b21b4c46fb4628fbae58), the child software System Management Interrupt (SWSMI) handler with GUID 54c03d2d-5903-4dfb-88b7-fa7636be03d1 is registered:

if ( SmstIsNotNull() )
{
  Handle1 = 0;
  gBS_8000C6E0->InstallProtocolInterface(&Handle1, &ProprietaryProtocol_8000BFF0, EFI_NATIVE_INTERFACE, 0);
  gHandle = Handle;
  if ( sub_80008990(&unk_8000BD20, 27) )
    gSmst_8000C718->SmmRegisterProtocolNotify(&ProprietaryProtocol_8000BE70, Function, &Registration);
  return gSmst_8000C718->SmiHandlerRegister(SmiHandler_80000A14, &gSmiHandlerGuid, &DispatchHandle);
}
//Find below the decompiled SWSMI handler code:

EFI_STATUS __fastcall SmiHandler_80000A14(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( !CommBuffer || !CommBufferSize )
    return 0;
  if ( *(_DWORD *)CommBuffer == 1 )
  {
    ...
  }
  else
  {
    Status = EFI_UNSUPPORTED;
  }
_WriteStatus:
  *(_QWORD *)((char *)CommBuffer + 4) = Status;
  return 0;
}
