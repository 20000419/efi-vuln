bool sub_8B58()
{
  bool result; // al
  EFI_GUID VendorGuid; // [rsp+30h] [rbp-10h] BYREF
  char Data; // [rsp+50h] [rbp+10h] BYREF
  UINTN DataSize; // [rsp+58h] [rbp+18h] BYREF

  VendorGuid.Data1 = -79978802;
  *(_DWORD *)&VendorGuid.Data2 = 1228098234;
  *(_DWORD *)VendorGuid.Data4 = -692806220;
  *(_DWORD *)&VendorGuid.Data4[4] = 1361283453;
  Data = 0;
  DataSize = 1i64;
  result = (!gRT->GetVariable(VariableName, &VendorGuid, 0i64, &DataSize, &Data)
         || (DataSize = 1i64, !gRT->GetVariable(aBatterysafetym_0, &VendorGuid, 0i64, &DataSize, &Data)))
        && Data == 1;
  return result;
}
