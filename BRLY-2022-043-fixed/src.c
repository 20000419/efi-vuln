// Updated protocol installation in AmdCpmInitSmm module (using SMM-specific services)
EfiSmmBase2Protocol->InSmm(EfiSmmBase2Protocol, &InSmram);
if (!InSmram)
  return res;
Status = gSmst->SmmAllocatePool(EfiRuntimeServicesData, 0x410, &Buffer);
if (Status >= 0)
{
  Status = gBS->LocateProtocol(&AMD_CPM_TABLE_PROTOCOL_GUID, 0, &Interface);
  if (Status >= 0)
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
    // Use SMM-specific protocol installation (critical fix)
    return gSmst->SmmInstallProtocolInterface(Handle, &AMD_CPM_TABLE_SMM_PROTOCOL_GUID, EFI_NATIVE_INTERFACE, Buffer);
  }
}

// Updated protocol location in SMI handler registration code
gSmst->SmmLocateProtocol(&EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID, 0, &EfiSmmSwDispatch2Protocol);
RegisterContext.SwSmiInputValue = 0xBC;
result = EfiSmmSwDispatch2Protocol->Register(..., ..., ...);

// In SMI handler initialization code (inside SwSmiHandler and SwSmiHandler_0)
EfiSmmBase2Protocol->InSmm(EfiSmmBase2Protocol, &InSmram);
if (InSmram)
{
  // Use SMM-specific locate for SMM protocols (critical fix)
  result = gSmst->SmmLocateProtocol(&AMD_CPM_TABLE_SMM_PROTOCOL_GUID, 0, &gAmdCpmTableSmmProtocol);
  if (result < 0)
    return result;
  result = gSmst->SmmLocateProtocol(&AMD_CPM_DISPLAY_FEATURE_PROTOCOL_GUID, 0, &gAmdCpmDisplayFeatureProtocol);
  if (result != EFI_SUCCESS)
    return EFI_ABORTED;
}

// Safe protocol function calls in SMI handlers (no changes needed to functional logic)
v6 = (*(gAmdCpmTableSmmProtocol + 113))(gAmdCpmTableSmmProtocol, '31A$');
(*(gAmdCpmTableSmmProtocol + 0x24))(gAmdCpmTableSmmProtocol, v7, v9, v8);
