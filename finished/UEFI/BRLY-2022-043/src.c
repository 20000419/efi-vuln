...
gSmst->SmmLocateProtocol(&EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID, 0, &EfiSmmSwDispatch2Protocol);
RegisterContext.SwSmiInputValue = 0xBC;
result = EfiSmmSwDispatch2Protocol->Register(
            EfiSmmSwDispatch2Protocol,
            SwSmiHandler, // vulnerable handler, offset: 0x319C
            &RegisterContext,
            &DispatchHandle);
if ( result >= 0 )
{
  RegisterContext.SwSmiInputValue = 0xBA;
  result = EfiSmmSwDispatch2Protocol->Register(
              EfiSmmSwDispatch2Protocol,
              SwSmiHandler_0, // vulnerable handler, offset: 0x32B0
              &RegisterContext,
              &DispatchHandle);
  if ( result >= 0 )
  {
    if ( value > 0xC )
      return 0;
    check_val = 0x1B20;
    if ( !_bittest(&check_val, value) )
      return 0;
    RegisterContext.SwSmiInputValue = 0xB9;
    result = EfiSmmSwDispatch2Protocol->Register(
                EfiSmmSwDispatch2Protocol,
                SwSmiHandler_1,
                &RegisterContext,
                &DispatchHandle);
    if ( result >= 0 )
      return 0;
  }
}
...
//Each of the handlers mentioned contains many function calls from the interfaces, which has been located as follows:

EfiSmmBase2Protocol->InSmm(EfiSmmBase2Protocol, &InSmram);
if ( InSmram )
{
  // AMD_CPM_TABLE_SMM_PROTOCOL_GUID = af6efacf-7a13-45a3-b1a5-aafc061c4b79
  result = gBS->LocateProtocol(&AMD_CPM_TABLE_SMM_PROTOCOL_GUID, 0, &gAmdCpmTableSmmProtocol);
  if ( result < 0 )
    return result;
  // AMD_CPM_DISPLAY_FEATURE_PROTOCOL_GUID = db4a79ac-5bbb-4625-6a9e-febf9d6d95eb
  if ( gBS->LocateProtocol(&AMD_CPM_DISPLAY_FEATURE_PROTOCOL_GUID, 0, &gAmdCpmDisplayFeatureProtocol) != EFI_SUCCESS )
    return EFI_ABORTED;
...
//Below are some examples of functions calls from the mentioned protocols interfaces that are used within SMI handlers:

// from SwSmiHandler located at offset 0x319C
v6 = (*(gAmdCpmTableSmmProtocol + 113))(gAmdCpmTableSmmProtocol, '31A$');
// from sub_1818
...
(*(gAmdCpmTableSmmProtocol + 0x24))(gAmdCpmTableSmmProtocol, a2, a3, a4);
LOBYTE(v7) = *(a1 + 2 * v4 + 37);
LOBYTE(v8) = *(a1 + 2 * v4 + 36) & 7;
LOBYTE(v9) = *(a1 + 2 * v4 + 36) >> 3;
(*(gAmdCpmTableSmmProtocol + 0x24))(gAmdCpmTableSmmProtocol, v7, v9, v8);
LOBYTE(v10) = *(a1 + 2 * v4 + 37);
LOBYTE(v11) = *(a1 + 2 * v4 + 36) & 7;
LOBYTE(v12) = *(a1 + 2 * v4 + 36) >> 3;
(*(gAmdCpmTableSmmProtocol + 0x24))(gAmdCpmTableSmmProtocol, v10, v12, v11);
LOBYTE(v13) = *(a1 + 2 * v4 + 37);
LOBYTE(v14) = *(a1 + 2 * v4 + 36) & 7;
LOBYTE(v15) = *(a1 + 2 * v4 + 36) >> 3;
(*(gAmdCpmTableSmmProtocol + 0x24))(gAmdCpmTableSmmProtocol, v13, v15, v14);
LOBYTE(v16) = *(a1 + 2 * v4 + 37);
LOBYTE(v17) = *(a1 + 2 * v4 + 36) & 7;
LOBYTE(v18) = *(a1 + 2 * v4 + 36) >> 3;
(*(gAmdCpmTableSmmProtocol + 0x24))(gAmdCpmTableSmmProtocol, v16, v18, v17);
...
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
