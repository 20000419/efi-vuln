//The handler is registered as follows:

result = (gSmst->SmmLocateProtocol)(&EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID, 0, &EfiSmmSwDispatch2Protocol);
if ( result >= 0 )
{
  RegisterContext.SwSmiInputValue = 0x31;
  EfiSmmSwDispatch2Protocol->Register(EfiSmmSwDispatch2Protocol, SmiHandler, &RegisterContext, &DispatchHandle);
  ...
}
//The pseudocode of the vulnerable handler is shown below:

EFI_STATUS __fastcall SmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  UsbData = gUsbData;
  Struct = *(gUsbData + 25824);
  if ( Struct )
  {
    *(gUsbData + 25824) = 0;
  }
  else
  {
    if ( (*(gUsbData + 8) & 0x10) != 0 )
      return 0;
    Struct = *(16 * MEMORY[0x40E] + 260);
    // check that the buffer does not overlap with SMRAM
    if ( BufferValidation(Struct, 47) < EFI_SUCCESS )
      return 0;
    *(UsbData + 26904) = 1;
  }
  if ( !Struct )
    return 0;
  FuncIndex = *Struct;
  if ( !*Struct )
    goto _Exec;
  if ( FuncIndex >= 32 && FuncIndex <= 56 )
  {
    FuncIndex -= 31;
_Exec:
    (gUsbApiTable[FuncIndex])(Struct);
    UsbData = gUsbData;
  }
  if ( !*(UsbData + 25824) )
    *(UsbData + 26904) = 0;
  return 0;
}
//Struct value can be controlled by attacker with Ring 0 privileges.If FuncIndex == 14, than the function located at offset 0x3080 will be called:

__int64 __fastcall UsbApiHcProc(STRUCT *Struc)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  result = Invoke(
             *(192 * ((Struc->HcType - 16) >> 4) + gUsbData + 112 + 8 * Struc->SubfuncIndex + 8),
             Struc->ParamBuffer,
             (Struc->ParamSize + 3) & ~3u);
  Struc->RetVal = 0;
  Struc->ApiRetVal = result;
  return result;
}
The first argument to the Invoke function is a pointer to be retrieved from the structure pointed to by gUsbData.The pseudocode of the Invoke function is shown below:

__int64 __fastcall Invoke(__int64 (*Ptr)(void), _QWORD *ParamBuffer, unsigned int ParamSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  v3 = ParamSize >> 3;
  if ( !v3 )
    return Ptr();
  v4 = v3 - 1;
  if ( !v4 )
    return (Ptr)(*ParamBuffer);
  v5 = v4 - 1;
  if ( !v5 )
    return (Ptr)(*ParamBuffer, ParamBuffer[1]);
  v6 = v5 - 1;
  if ( !v6 )
    return (Ptr)(*ParamBuffer, ParamBuffer[1], ParamBuffer[2]);
  v7 = v6 - 1;
  if ( !v7 )
    return (Ptr)(*ParamBuffer, ParamBuffer[1], ParamBuffer[2], ParamBuffer[3]);
  v8 = v7 - 1;
  if ( !v8 )
    return (Ptr)(*ParamBuffer, ParamBuffer[1], ParamBuffer[2], ParamBuffer[3], ParamBuffer[4]);
  v9 = v8 - 1;
  if ( !v9 )
    return (Ptr)(*ParamBuffer, ParamBuffer[1], ParamBuffer[2], ParamBuffer[3], ParamBuffer[4], ParamBuffer[5]);
  if ( v9 == 1 )
    return (Ptr)(
             *ParamBuffer,
             ParamBuffer[1],
             ParamBuffer[2],
             ParamBuffer[3],
             ParamBuffer[4],
             ParamBuffer[5],
             ParamBuffer[6]);
  return 0;
}
