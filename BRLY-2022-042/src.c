__int64 __fastcall sub_121C(EFI_SMM_BASE2_PROTOCOL *a1, __int64 a2)
{
  __int64 result
  EFI_STATUS v3;
  EFI_HANDLE DispatchHandle[3];
  EFI_SMM_BASE2_PROTOCOL *EfiSmmBase2Protocol;
  __int64 InSmram;
  EFI_SMM_SW_REGISTER_CONTEXT RegisterContext;
  EFI_SMM_SW_DISPATCH2_PROTOCOL *EfiSmmSwDispatch2Protocol;

  InSmram = a2;
  EfiSmmBase2Protocol = a1;
  result = gBS->LocateProtocol(&EFI_SMM_BASE2_PROTOCOL_GUID, 0, &EfiSmmBase2Protocol);
  v3 = result;
  if ( result >= 0 )
  {
    EfiSmmBase2Protocol->InSmm(EfiSmmBase2Protocol, &InSmram);
    if ( InSmram )
    {
      result = gBS->LocateProtocol(&AMD_CPM_TABLE_SMM_PROTOCOL_GUID, 0, &gAmdCpmTableSmmProtocol);
      if ( result < 0 )
        return result;
      (*(gAmdCpmTableSmmProtocol + 72))(60);
      gSmst->SmmLocateProtocol(&EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID, 0, &EfiSmmSwDispatch2Protocol);
      RegisterContext.SwSmiInputValue = 0xBC;
      v3 = EfiSmmSwDispatch2Protocol->Register(
             EfiSmmSwDispatch2Protocol,
             SwSmiHandler,
             &RegisterContext,
             DispatchHandle);
      (*(gAmdCpmTableSmmProtocol + 72))(61);
    }
    return v3;
  }
  return result;
}
//Consider the pseudocode of the SwSmiHandler:

EFI_STATUS __fastcall SwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // local variables initialization

  sub_1300();
  v4 = gAmdCpmTableSmmProtocol;
  if ( gAmdCpmTableSmmProtocol )
  {
    v5 = (*(gAmdCpmTableSmmProtocol + 113))(gAmdCpmTableSmmProtocol, '11A$');
    if ( v5 )
    {
      for ( i = (v5 + 16); *i != 255; i += 2 )
        (*(v4 + 92))(v4, *i, i[1]);
    }
  }
  return 0;
}
Where sub_1300 contains the following code snippets:

AmdCpmTableSmmProtocol = gAmdCpmTableSmmProtocol;
v1 = 0;
v2 = (*(gAmdCpmTableSmmProtocol + 113))(gAmdCpmTableSmmProtocol, '71A$');
v3 = (*(AmdCpmTableSmmProtocol + 113))(AmdCpmTableSmmProtocol, '30A$');
v4 = (*(AmdCpmTableSmmProtocol + 96))(AmdCpmTableSmmProtocol) & 2;
if ( v3 )
{
  if ( v4 )
  {
      if ( v2 )
      {
          LOBYTE(v5) = -117;
          v6 = (*(AmdCpmTableSmmProtocol + 126))(AmdCpmTableSmmProtocol, v5);
          LOBYTE(v7) = -118;
          v8 = v6;
          v9 = (*(AmdCpmTableSmmProtocol + 126))(AmdCpmTableSmmProtocol, v7);
          LOBYTE(v10) = -119;
          v11 = (v8 << 8) + v9;
          v12 = (*(AmdCpmTableSmmProtocol + 126))(AmdCpmTableSmmProtocol, v10);
          LOBYTE(v13) = -120;
          v14 = (v11 << 8) + v12;
          v15 = (*(AmdCpmTableSmmProtocol + 126))(AmdCpmTableSmmProtocol, v13);
          LOBYTE(v16) = -121;
          v17 = (v14 << 8) + v15;
          v18 = (*(AmdCpmTableSmmProtocol + 126))(AmdCpmTableSmmProtocol, v16);
          ...
      }
      ...
  }
  ...
}  
//As we can see from the pseudocode, there are many function calls from the interface, which has been located as follows:

// AMD_CPM_TABLE_SMM_PROTOCOL_GUID = af6efacf-7a13-45a3-b1a5-aafc061c4b79
gBS->LocateProtocol(&AMD_CPM_TABLE_SMM_PROTOCOL_GUID, 0, &gAmdCpmTableSmmProtocol);
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
