//In the function at offset 0x1E78 (image sha256: fa9d63c831354c494ce14c87757c43936d1c634779997a8cc77ec71cb9a307ca), the child software System Management Interrupt (SWSMI) handler with GUID 3779ad93-b988-43bc-91f0-3b6c6e38fadb is registered:

if ( v5 )
{
  result = gBS_B588->LocateProtocol(&gSmiHandlerGuid, 0, &Buffer);
  if ( result >= 0 )
  {
    result = gSmst_B5C8->SmiHandlerRegister(SmiHandler_296C, &gSmiHandlerGuid, &DispatchHandle);
    if ( result >= 0 )
    {
      v7 = (gSmst_B5C8->SmmRegisterProtocolNotify)(&Protocol, Function, v11);
      if ( v7 < 0 )
        return v7;
      return v4;
    }
  }
}
//Find below the decompiled SWSMI handler code:

EFI_STATUS __fastcall SmiHandler_296C(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  EFI_STATUS Status; // rax

  if ( CommBuffer && CommBufferSize )
  {
    if ( *CommBuffer )
    {
      Status = EFI_UNSUPPORTED;
    }
    else if ( *(CommBuffer + 2) == 0x148 )
    {
      Status = sub_27CC(0, CommBuffer + 0x18);
    }
    else
    {
      Status = EFI_INVALID_PARAMETER;
    }
    *(CommBuffer + 1) = Status;
  }
  return 0;
}
//If CommBuffer and CommBufferSize pointers are not NULL, the status code is written to the second QWORD in the CommBuffer (*(CommBuffer + 1)).

//In addition, if the third QWORD from the CommBuffer is 0x148, the sub_27CC function is called. Consider the following decompiled code of this function:

EFI_STATUS __fastcall sub_27CC(__int64 a1, void *CommBufferData)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( *((_BYTE *)CommBufferData + 0xE0) )
    return 0;
  Interface = 0;
  Buffer = 0;
  Status = gSmst_B5C8->SmmAllocatePool(EfiRuntimeServicesData, 0x148, &Buffer);
  if ( (Status & 0x8000000000000000) != 0 )
    goto _FreeBufferAndExit1;
  ZeroMem(Buffer, 0x148);
  CopyMem(Buffer, CommBufferData, 0x148);
  *((_QWORD *)Buffer + 3) = 0;
  Status = InstallProprietaryProtocolInterface((__int64)Buffer);
  if ( (Status & 0x8000000000000000) == 0 )
  {
    ...
    Status = gSmst_B5C8->SmmInstallProtocolInterface(
               (EFI_HANDLE *)Buffer + 3,
               &EFI_DEVICE_PATH_PROTOCOL_GUID_B000,
               EFI_NATIVE_INTERFACE,
               Interface);
    if ( (Status & 0x8000000000000000) == 0 )
    {
      v7 = Buffer;
      *((_QWORD *)CommBufferData + 3) = *((_QWORD *)Buffer + 3);
      *((_BYTE *)CommBufferData + 0xE0) = 1;
      v7[224] = 1;
      return Status;
    }
_FreeBufferAndExit1:
    Interface1 = Interface;
    goto _FreeBufferAndExit;
  }
  ((void (__fastcall *)(void *))gSmst_B5C8->SmmFreePool)(Buffer);
  return Status;
}
