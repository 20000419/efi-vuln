//In the function at offset 0x1AC0 (image sha256: f6d7d5cce1a3b2ebe9825c195f61f36aca674e3710abf0e24f1383e6d3c0e126), the child software System Management Interrupt (SWSMI) handler with the GUID EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID is registered:

if ( SmstIsNotNull() )
{
  DispatchHandle = 0;
  gSmst_62B0->SmiHandlerRegister(SmiHandler_17D4, &EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID_5AF0, &DispatchHandle);
  Registration = 0;
  result = gSmst_62B0->SmmRegisterProtocolNotify(&ProprietaryProtocol_5B80, Function, &Registration);
  if ( result < 0 )
    return result;
}
//Find below the decompiled SWSMI handler code:

__int64 __fastcall SmiHandler_17D4(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( !CommBuffer || !CommBufferSize )
    return 0;
  if ( *CommBuffer != 1 )
    return EFI_UNSUPPORTED;
  SourceSize = 0;
  if ( (gBS_6278->LocateHandleBuffer(
          ByProtocol,
          &EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID_5AF0,
          0,
          &NoHandles,
          &SourceSize) & 0x8000000000000000) != 0 )
    return EFI_NOT_FOUND;
  Buffer = SourceSize;
  if ( SourceSize )
  {
    gBS_6278->FreePool(SourceSize);
    Buffer = 0;
    SourceSize = 0;
  }
  BufferSize = 0;
  Status = gSmst_62B0->SmmLocateHandle(
             ByProtocol,
             &EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID_5AF0,
             0,
             &BufferSize,
             Buffer);
  if ( Status )
  {
    if ( Status == EFI_BUFFER_TOO_SMALL )
    {
      gSmst_62B0->SmmAllocatePool(EfiRuntimeServicesData, BufferSize, &SourceSize);
      if ( !SourceSize )
        return EFI_OUT_OF_RESOURCES;
      Status = gSmst_62B0->SmmLocateHandle(
                 ByProtocol,
                 &EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID_5AF0,
                 0,
                 &BufferSize,
                 SourceSize);
    }
    else if ( Status != EFI_NOT_FOUND )
    {
      return EFI_NOT_FOUND;
    }
  }
  Res = Status == EFI_NOT_FOUND ? 0 : BufferSize >> 3;
  gSmst_62B0->SmmFreePool(SourceSize);
  if ( Res == NoHandles )
    return 0;
  result = sub_428();
  if ( result >= 0 )
    return 0;
  if ( result == EFI_NOT_STARTED )
    return 0;
  return result;
}
