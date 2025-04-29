EFI_STATUS __fastcall sub_2F338(__int64 a1)
{
  // [COLLAPSED LOCAL DECLARATIONS]

  DataSize = 1;
  v0 = sub_2A23C(2);
  v1 = sub_2A23C(1);
  (gRT->GetVariable)(L"SecureBootEnforce", &EFI_GENERIC_VARIABLE_GUID, &Attributes, &DataSize, &SecureBootEnforceData);
  gRT->GetVariable(L"SecureBoot", &EFI_SIMPLE_BOOT_FLAG_VARIABLE_GUID, 0, &DataSize, &SecureBootData);
  Res = SecureBootEnforceData & SecureBootData;
  Status = 0;
  if ( !gRT->GetVariable(L"RestoreBootSettings", &gVendorGuid, 0, &DataSize, &RestoreBootSettingsData)
    && RestoreBootSettingsData == 1
    && !Res
    && (!v1 || v0) )
  {
    Res = 1;
    sub_2FFC4(1);
    gRT->SetVariable(L"RestoreBootSettings", &gVendorGuid, 0, 0, 0);
    gRT->ResetSystem(EfiResetCold, 0, 0, 0);
  }
  if...
  return Status;
}
