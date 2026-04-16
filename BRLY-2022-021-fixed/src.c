EFI_STATUS __fastcall sub_2F338(__int64 a1)
{
  // [Collapsed local declarations, including SecureBootEnforceData (1 byte), SecureBootData (1 byte), RestoreBootSettingsData (1 byte)]

  // Dedicated buffer sizes for each variable (match stack variable sizes)
  UINTN secureBootEnforceSize = sizeof(SecureBootEnforceData);  // 1 byte
  UINTN secureBootSize = sizeof(SecureBootData);                // 1 byte
  UINTN restoreBootSettingsSize = sizeof(RestoreBootSettingsData);  // 1 byte

  v0 = sub_2A23C(2);
  v1 = sub_2A23C(1);

  // First GetVariable: SecureBootEnforce (uses dedicated size)
  EFI_STATUS status = gRT->GetVariable(
    L"SecureBootEnforce",
    &EFI_GENERIC_VARIABLE_GUID,
    &Attributes,
    &secureBootEnforceSize,
    &SecureBootEnforceData
  );
  if (EFI_ERROR(status) && status != EFI_NOT_FOUND) {
    return status;  // Handle error without trusting modified size
  }

  // Second GetVariable: SecureBoot (uses dedicated size)
  status = gRT->GetVariable(
    L"SecureBoot",
    &EFI_SIMPLE_BOOT_FLAG_VARIABLE_GUID,
    NULL,
    &secureBootSize,
    &SecureBootData
  );
  if (EFI_ERROR(status) && status != EFI_NOT_FOUND) {
    return status;
  }

  UINTN res = SecureBootEnforceData & SecureBootData;
  status = EFI_SUCCESS;

  // Third GetVariable: RestoreBootSettings (uses dedicated size)
  status = gRT->GetVariable(
    L"RestoreBootSettings",
    &gVendorGuid,
    NULL,
    &restoreBootSettingsSize,
    &RestoreBootSettingsData
  );

  if (!EFI_ERROR(status) && RestoreBootSettingsData == 1 && !res && (!v1 || v0)) {
    res = 1;
    sub_2FFC4(1);
    gRT->SetVariable(L"RestoreBootSettings", &gVendorGuid, 0, 0, NULL);  // Use NULL for zero-length data
    gRT->ResetSystem(EfiResetCold, 0, 0, 0);
  }

  return status;
}
