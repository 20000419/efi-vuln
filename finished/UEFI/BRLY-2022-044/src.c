gSmst->SmmLocateProtocol(&EFI_SMM_SX_DISPATCH2_PROTOCOL_GUID, 0i64, &EfiSmmSxDispatch2Protocol);
gSmst->SmmLocateProtocol(&EFI_SMM_POWER_BUTTON_DISPATCH2_PROTOCOL_GUID, 0i64, &EfiSmmPowerButtonDispatch2Protocol);
RegisterContext.Phase = SxEntry;
RegisterContext.Type = SxS3;
EfiSmmSxDispatch2Protocol->Register(EfiSmmSxDispatch2Protocol, SxSmiHandler, &RegisterContext, &DispatchHandle);
RegisterContext.Phase = SxEntry;
RegisterContext.Type = SxS4;
EfiSmmSxDispatch2Protocol->Register(
  EfiSmmSxDispatch2Protocol,
  PowerButtonSmiHandler,
  &RegisterContext,
  &DispatchHandle);
RegisterContext.Phase = SxEntry;
RegisterContext.Type = SxS5;
EfiSmmSxDispatch2Protocol->Register(
  EfiSmmSxDispatch2Protocol,
  PowerButtonSmiHandler,
  &RegisterContext,
  &DispatchHandle);
PbRegisterContext.Phase = PowerButtonExit;
EfiSmmPowerButtonDispatch2Protocol->Register(
  EfiSmmPowerButtonDispatch2Protocol,
  PowerButtonSmiHandler,
  &PbRegisterContext,
  &PbDispatchHandle);
  
//SxSmiHandler and SxAndPowerButtonSmiHandler callbacks contains many function calls from the interface, which has been located as follows:

// AMD_CPM_TABLE_SMM_PROTOCOL_GUID = af6efacf-7a13-45a3-b1a5-aafc061c4b79
result = gBS->LocateProtocol(&AMD_CPM_TABLE_SMM_PROTOCOL_GUID, 0, &gAmdCpmTableSmmProtocol);
//Let's look at all the problem areas (marked with "callout" comment) using the SxSmiHandler function as an example:

(*(gAmdCpmTableSmmProtocol + 90))(gAmdCpmTableSmmProtocol, 0x218, 0); // callout
(*(gAmdCpmTableSmmProtocol + 90))(gAmdCpmTableSmmProtocol, 0x21F, 0); // callout
res = (*(gAmdCpmTableSmmProtocol + 11))(0xFED8156C); // callout
(*(gAmdCpmTableSmmProtocol + 15))(0xFED8156C, res & 0xFFBFFFFF); // callout
result = gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, 0, &EfiSmmVariableProtocol);
if ( result >= 0 )
{
  DataSize = 136;
  result = EfiSmmVariableProtocol->SmmGetVariable(L"AMD_PBS_SETUP", &gGuid, 0, &DataSize, Data);
  Status = result;
  if ( result >= 0 )
  {
    if ( Data[54] == 1 )
    {
      res = (*(gAmdCpmTableSmmProtocol + 11))(0xFED803E4); // callout
      // in case of SxAndPowerButtonSmiHandler last argument is different: res & 0xFFFFFFFC
      (*(gAmdCpmTableSmmProtocol + 15))(0xFED803E4, res & 0xFFFFFFFC | 1); // callout
    }
    return Status;
  }
}
//The AMD_CPM_TABLE_SMM_PROTOCOL_GUID (af6efacf-7a13-45a3-b1a5-aafc061c4b79) protocol installation routine shown below (code from AmdCpmInitSmm module):

EfiSmmBase2Protocol->InSmm(EfiSmmBase2Protocol, &InSmram);
if ( !InSmram )
  return res;
Status = gSmst->SmmAllocatePool(EfiRuntimeServicesData, 0x410, &Buffer);
if ( Status >= 0 )
{
  Status = gBS->LocateProtocol(&AMD_CPM_TABLE_PROTOCOL_GUID, 0, &Interface);
  if ( Status >= 0 )
  {
    *Buffer = *Interface;
    *(Buffer + 1) = *(Interface + 1);
    InterfaceBuffer = Buffer;
    *(Buffer + 0x71) = sub_13A0;
    InterfaceBuffer[0x72] = &loc_13A8;
    InterfaceBuffer[0x78] = sub_14E4;
    InterfaceBuffer[0x79] = sub_14B4;
    sub_2DE4(Buffer);
    sub_3A00(Buffer);
    sub_5FC0(Buffer);
    Handle[0] = 0;
    return gBS->InstallProtocolInterface(Handle, &AMD_CPM_TABLE_SMM_PROTOCOL_GUID, EFI_NATIVE_INTERFACE, Buffer);
...  
