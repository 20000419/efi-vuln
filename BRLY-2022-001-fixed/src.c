char __fastcall AmiSetupNvramUpdateCallback(EFI_CAPSULE_HEADER **CapsuleHeaderArray) {
  EFI_STATUS Status;
  UINTN DataSize;
  void *MeSetupStorageBuffer = NULL;
  void *MeBackupStorageBuffer = NULL;
  // ... (other variables and initializations)

  // Safely retrieve MeSetupStorage variable
  DataSize = 0;
  Status = gRT->GetVariable(L"MeSetupStorage", &gVariableGuid, 0, &DataSize, NULL);
  if (!EFI_ERROR(Status)) {
    MeSetupStorageBuffer = gBS->AllocatePool(DataSize);
    if (MeSetupStorageBuffer) {
      Status = gRT->GetVariable(L"MeSetupStorage", &gVariableGuid, 0, &DataSize, MeSetupStorageBuffer);
      if (EFI_ERROR(Status)) {
        gBS->FreePool(MeSetupStorageBuffer);
        MeSetupStorageBuffer = NULL;
      }
    }
  }

  // Safely retrieve MeBackupStorage variable
  DataSize = 0;
  Status = gRT->GetVariable(L"MeBackupStorage", &gVariableGuid, 0, &DataSize, NULL);
  if (!EFI_ERROR(Status)) {
    MeBackupStorageBuffer = gBS->AllocatePool(DataSize);
    if (MeBackupStorageBuffer) {
      Status = gRT->GetVariable(L"MeBackupStorage", &gVariableGuid, 0, &DataSize, MeBackupStorageBuffer);
      if (EFI_ERROR(Status)) {
        gBS->FreePool(MeBackupStorageBuffer);
        MeBackupStorageBuffer = NULL;
      }
    }
  }

  if (MeSetupStorageBuffer && MeBackupStorageBuffer) {
    // Perform comparisons using dynamic buffers instead of stack buffers
    if (((char*)MeSetupStorageBuffer)[12] != ((char*)MeBackupStorageBuffer)[12] && !byte_27E8A && ((char*)MeSetupStorageBuffer)[12] == 1)
      sub_1CAB8();
    if (((char*)MeSetupStorageBuffer)[2] != ((char*)MeBackupStorageBuffer)[2]) {
      // ... (existing logic using dynamic buffers)
    }
    // ... (other comparisons and logic using MeSetupStorageBuffer and MeBackupStorageBuffer)

    // Free allocated buffers after use
    gBS->FreePool(MeSetupStorageBuffer);
    gBS->FreePool(MeBackupStorageBuffer);
  }

  // ... (remaining code, ensuring no use of unsafe stack buffers)

  return Status;
}
