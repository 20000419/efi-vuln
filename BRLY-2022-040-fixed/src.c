__int64 sub_F02C()
{
  __int64 result;
  UINTN DataSize;
  __int64 Data;
  EFI_GUID VendorGuid;
  EFI_GUID BootFlowVariableGuid;
  UINT32 Attributes;
  UINT32 OsIndicationsAttributes;
  int BootFlowValue;
  __int64 OsIndicationsValue;

  sub_503C(0, 0, 0x18, 0x50);

  // EFI_SIMPLE_BOOT_FLAG_VARIABLE_GUID
  VendorGuid.Data1 = 0x8BE4DF61;
  *&VendorGuid.Data2 = 0x11D293CA;
  *VendorGuid.Data4 = 0xE0000DAA;
  *&VendorGuid.Data4[4] = 0x8C2B0398;

  Data = 1;
  DataSize = 8;
  Attributes = 6;
  BootFlowValue = 4;

  // BOOT_FLOW_VARIABLE_GUID
  BootFlowVariableGuid.Data1 = 0xEF152FB4;
  *&BootFlowVariableGuid.Data2 = 0x427D7B2F;
  *BootFlowVariableGuid.Data4 = 0xA7EB4BD;
  *&BootFlowVariableGuid.Data4[4] = 0x646E8205;
  if ( (gRT->GetVariable(L"OsIndicationsSupported", &VendorGuid, &Attributes, &DataSize, &Data) & 0x8000000000000000) == 0
    && DataSize )
  {
    Data |= 1;
  }
  // Re-initialize DataSize to correct buffer size before SetVariable
  DataSize = sizeof(Data); // Ensure it's 8 bytes for __int64
  result = gRT->SetVariable(L"OsIndicationsSupported", &VendorGuid, Attributes, DataSize, &Data);
  if ( result >= 0 )
  {
    DataSize = 8;
    result = gRT->GetVariable(L"OsIndications", &VendorGuid, &OsIndicationsAttributes, &DataSize, &OsIndicationsValue);
    if ( result >= 0 && (OsIndicationsValue & 1) != 0 )
    {
      gRT->SetVariable(L"BootFlow", &BootFlowVariableGuid, 2, 4, &BootFlowValue);
      OsIndicationsValue &= ~1;
      return gRT->SetVariable(L"OsIndications", &VendorGuid, OsIndicationsAttributes, DataSize, &OsIndicationsValue);
    }
  }
  return result;
}
