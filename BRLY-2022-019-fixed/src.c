EFI_STATUS __fastcall sub_3C8(UINTN DataSize, void *Data)
{
  EFI_STATUS Status;
  EFI_HANDLE Handle;
  UINTN DataSizea = 0;
  VOID *MebxDataBuffer = NULL;

  // Get required buffer size
  Status = gRT->GetVariable(L"MebxData", &MEBX_DATA_GUID, NULL, &DataSizea, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL && Status != EFI_NOT_FOUND) {
    return Status;
  }

  // Allocate heap buffer
  if (DataSizea > 0) {
    MebxDataBuffer = AllocatePool(DataSizea);
    if (!MebxDataBuffer) {
      return EFI_OUT_OF_RESOURCES;
    }

    // Read variable contents
    Status = gRT->GetVariable(L"MebxData", &MEBX_DATA_GUID, NULL, &DataSizea, MebxDataBuffer);
    if (EFI_ERROR(Status)) {
      FreePool(MebxDataBuffer);
      return Status;
    }
  }

  // Compare data if variable exists
  if (Status == EFI_SUCCESS && 
      (DataSizea != DataSize || 
       (DataSizea > 0 && CompareMem(Data, MebxDataBuffer, MIN(DataSize, DataSizea))))) {
    // Data differs, update variable
    Status = gRT->SetVariable(L"MebxData", &MEBX_DATA_GUID, 3, DataSize, Data);
    if (EFI_ERROR(Status)) {
      FreePool(MebxDataBuffer);
      return Status;
    }

    // Install protocol interface
    Handle = NULL;
    Status = gBS->InstallProtocolInterface(&Handle, &UPDATE_SMBIOS_HW_ASSET_TABLE_GUID, EFI_NATIVE_INTERFACE, NULL);
  } else if (Status == EFI_NOT_FOUND) {
    // Variable doesn't exist, create it
    Status = gRT->SetVariable(L"MebxData", &MEBX_DATA_GUID, 3, DataSize, Data);
    if (EFI_ERROR(Status)) {
      FreePool(MebxDataBuffer);
      return Status;
    }

    // Install protocol interface
    Handle = NULL;
    Status = gBS->InstallProtocolInterface(&Handle, &UPDATE_SMBIOS_HW_ASSET_TABLE_GUID, EFI_NATIVE_INTERFACE, NULL);
  }

  // Cleanup
  if (MebxDataBuffer) {
    FreePool(MebxDataBuffer);
  }

  return Status;
}
