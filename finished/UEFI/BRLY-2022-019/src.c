EFI_STATUS __fastcall sub_3C8(UINTN DataSize, void *Data)
{
  __int64 Status;
  EFI_HANDLE Handle;
  void *Dst;
  char MebxDataValue;
  UINTN DataSizea;

  Dst = Data;
  DataSizea = 0;
  Status = gRT->GetVariable(L"MebxData", &MEBX_DATA_GUID, 0, &DataSizea, &MebxDataValue);
  if ( Status == EFI_BUFFER_TOO_SMALL )
    Status = gRT->GetVariable(L"MebxData", &MEBX_DATA_GUID, 0, &DataSizea, &MebxDataValue);
  if ( Status >= 0 && (DataSizea != DataSize || DataSizea && CompareMem(&Dst, &MebxDataValue, DataSizea))
    || Status == EFI_NOT_FOUND )
  {
    gRT->SetVariable(L"MebxData", &MEBX_DATA_GUID, 3, DataSize, Dst);
    Handle = 0;
    return gBS->InstallProtocolInterface(&Handle, &UPDATE_SMBIOS_HW_ASSET_TABLE_GUID, EFI_NATIVE_INTERFACE, 0);
  }
  return Status;
}
