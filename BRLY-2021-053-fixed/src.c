__int64 SaPolisyProtocolNotifier() {
  EFI_STATUS Status;
  void *Interface;
  EFI_GUID VendorGuid;
  char IntelTechnologiesOptionsBuffer[40];
  UINTN DataSize;
  void *DynamicBuffer = NULL; // Dynamically allocated buffer

  VendorGuid.Data1 = 0xFB3B9ECE;
  *&VendorGuid.Data2 = 0x49334ABA;
  *&VendorGuid.Data4 = 0xD6B49DB4;
  *&VendorGuid.Data4[4] = 0x5123897D;

  // Locate protocol (existing logic)
  gBS->LocateProtocol(&SA_POLICY_PROTOCOL_GUID, 0, &Interface);

  // Safely retrieve PciePwrMgmt variable
  DataSize = 0;
  Status = gRT->GetVariable(L"PciePwrMgmt", &VendorGuid, 0, &DataSize, NULL); // First call for size
  if (!EFI_ERROR(Status) && DataSize > 0) {
    DynamicBuffer = gBS->AllocatePool(DataSize); // Allocate correct-sized buffer
    if (DynamicBuffer) {
      Status = gRT->GetVariable(L"PciePwrMgmt", &VendorGuid, 0, &DataSize, DynamicBuffer); // Second call with correct buffer
      if (!EFI_ERROR(Status)) {
        // Use DynamicBuffer as needed (replace unsafe Buffer usage)
        // ...
      }
      gBS->FreePool(DynamicBuffer); // Free allocated memory
    }
  }

  // Existing logic for IntelTechnologiesOptions (ensure buffer size matches if used)
  DataSize = sizeof(IntelTechnologiesOptionsBuffer);
  Status = gRT->GetVariable(L"IntelTechnologiesOptions", &VendorGuid, 0, &DataSize, IntelTechnologiesOptionsBuffer);
  if (EFI_ERROR(Status) && Status != EFI_BUFFER_TOO_SMALL) {
    // Handle error
  }

  return 0;
}
