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
    // Use SMM-specific protocol installation
    return gSmst->SmmInstallProtocolInterface(Handle, &AMD_CPM_TABLE_SMM_PROTOCOL_GUID, EFI_NATIVE_INTERFACE, Buffer);
  }
}

// Updated protocol location in sub_121C (SMI handler registration function)
result = gSmst->SmmLocateProtocol(&AMD_CPM_TABLE_SMM_PROTOCOL_GUID, 0, &gAmdCpmTableSmmProtocol);
if (result < 0)
  return result;

// Updated SwSmiHandler and sub_1300 to use properly located SMM protocol
EFI_STATUS __fastcall SwSmiHandler(...) {
  // ...
  if (gAmdCpmTableSmmProtocol) {
    // Safe usage of protocol functions from SMRAM-resident interface
    v5 = (*(gAmdCpmTableSmmProtocol + 113))(gAmdCpmTableSmmProtocol, '11A$');
    // ...
  }
  // ...
}
