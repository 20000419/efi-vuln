// During driver initialization (not in SMI handler)
EFI_STATUS EFIAPI DriverEntry(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
)
{
  // Locate protocol 74d936fa-d8bd-4633-b64d-6424bdd23d24
  EFI_STATUS Status = gBS->LocateProtocol(
    &UNKNOWN_PROTOCOL_74D936FA_GUID,
    NULL,
    (VOID **)&gUnknownProtocol74d936fa
  );
  
  if (EFI_ERROR(Status)) {
    return Status;
  }
  
  // Register SMI handler
  Status = gSmst->SmiHandlerRegister(
    SmiHandler,
    &UNKNOWN_PROTOCOL_2970687C_GUID,
    &Handle
  );
  
  return Status;
}

// Corrected SMI handler
EFI_STATUS __fastcall SmiHandler(
  EFI_HANDLE DispatchHandle,
  const void *Context,
  void *CommBuffer,
  UINTN *CommBufferSize
)
{
  if (CommBuffer && CommBufferSize && !gExitBootServicesFlag2EfiEventLegacyBootFlag) {
    if (!gUnknownProtocol74d936fa) {
      // Protocol already located during driver initialization
      return EFI_PROTOCOL_ERROR;
    }
    
    // ... existing handler code ...
  }
  
  return EFI_SUCCESS;
}
