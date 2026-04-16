// Updated protocol installation in AmdCpmInitSmm module (critical SMM-specific changes)
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
    // Use SMM-specific protocol installation (prevents DXE tampering)
    return gSmst->SmmInstallProtocolInterface(Handle, &AMD_CPM_TABLE_SMM_PROTOCOL_GUID, EFI_NATIVE_INTERFACE, Buffer);
  }
}

// Updated protocol location in SMI handler code (SxSmiHandler/PowerButtonSmiHandler)
// Replace dangerous gBS->LocateProtocol with SMM-specific version
result = gSmst->SmmLocateProtocol(&AMD_CPM_TABLE_SMM_PROTOCOL_GUID, 0, &gAmdCpmTableSmmProtocol);
if (result < 0)
  return result;

// Example of safe protocol usage in SxSmiHandler (no functional changes needed)
(*(gAmdCpmTableSmmProtocol + 90))(gAmdCpmTableSmmProtocol, 0x218, 0);
res = (*(gAmdCpmTableSmmProtocol + 11))(0xFED8156C);
(*(gAmdCpmTableSmmProtocol + 15))(0xFED8156C, res & 0xFFBFFFFF);

// Updated SMM variable protocol handling (if applicable)
result = gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, 0, &EfiSmmVariableProtocol);
if (result >= 0)
{
  DataSize = 136;
  result = EfiSmmVariableProtocol->SmmGetVariable(L"AMD_PBS_SETUP", &gGuid, 0, &DataSize, Data);
  // ... existing logic ...
}
