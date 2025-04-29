bool CheckBatterySafety()
{
  EFI_GUID VendorGuid;
  char Buffer;
  UINTN DataSize;

  VendorGuid.Data1 = 0xFB3B9ECE;
  *&VendorGuid.Data2 = 0x49334ABA;
  *VendorGuid.Data4 = 0xD6B49DB4;
  *&VendorGuid.Data4[4] = 0x5123897D;
  Buffer = 0;
  DataSize = 1i64;
  return (!gRT_157B30->GetVariable(L"BatterySafetyModeStatus", &VendorGuid, 0i64, &DataSize, &Buffer)
       || !gRT_157B30->GetVariable(L"BatterySafetyMode", &VendorGuid, 0i64, &DataSize, &Buffer))
      && Buffer == 1;
}
