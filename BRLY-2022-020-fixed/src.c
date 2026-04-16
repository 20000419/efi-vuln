EFI_STATUS sub_21468()
{
  // [Collapsed local declarations, including MeSetupStorageData and MeBackupStorageData (both 0x11 bytes)]

  memset(MeSetupStorageData, 0, 0x11);
  memset(MeBackupStorageData, 0, 0x11);
  DataSize = 1250;
  gRT->GetVariable(aSetup, &DRIVER_SAMPLE_FORM_SET_GUID, 0, &DataSize, Data);
  v4 = gBS->LocateProtocol(&ProprietaryProtocol_10, 0, &Interface);
  result = sub_2D178(v0);
  
  if (!result && v4 >= 0) {
    UINTN setupDataSize = sizeof(MeSetupStorageData);  // Explicitly set buffer size
    EFI_STATUS status = gRT->GetVariable(
      L"MeSetupStorage", 
      &gVariableGuid, 
      0, 
      &setupDataSize, 
      MeSetupStorageData
    );
    
    if (EFI_ERROR(status) && status != EFI_NOT_FOUND) {
      return status;  // Handle error without using oversized setupDataSize
    }
    
    UINTN backupDataSize = sizeof(MeBackupStorageData);  // Fresh buffer size for second call
    status = gRT->GetVariable(
      L"MeBackupStorage", 
      &gVariableGuid, 
      0, 
      &backupDataSize, 
      MeBackupStorageData
    );
    
    if (EFI_ERROR(status) && status != EFI_NOT_FOUND) {
      return status;
    }
    
    DataSize = 54;
    gRT->GetVariable(aMesetup, &gVariableGuid, 0, &DataSize, &unk_119A20);
    sub_29338(v11);
    // ... (remaining logic unchanged, using validated buffer sizes) ...
    
    gRT->SetVariable(L"MeBackupStorage", &gVariableGuid, 2, 0x11, MeSetupStorageData);
    return gRT->SetVariable(aSetup, &DRIVER_SAMPLE_FORM_SET_GUID, 2, 0x4E2, Data);
  }
  return result;
}
