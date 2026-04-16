PCD_PROTOCOL *gCachedPcdProtocol = NULL; // SMRAM-resident cached pointer

PCD_PROTOCOL *LocatePcdProtocol() {
  if (!gCachedPcdProtocol) {
    // Use SMM-specific protocol lookup (safe in SMRAM)
    EFI_STATUS status = gSmst->SmmLocateProtocol(
      &PCD_PROTOCOL_GUID,
      NULL,
      (VOID**)&gCachedPcdProtocol
    );
    if (EFI_ERROR(status)) {
      return NULL; // Handle error or log
    }
  }
  return gCachedPcdProtocol;
}
case 0x10:
  if (!gBuffer) {
    Buffer = GetCopy(0x78, CommBuffer + 24);
    BufferSize = *(CommBuffer + 2);
    BufferPtr = *(CommBuffer + 1);
    gBuffer = Buffer;
    sub_261C(BufferPtr, BufferSize);
    
    // Get cached PCD protocol (SMM-safe, no boot services)
    PCD_PROTOCOL *PcdProtocol = LocatePcdProtocol();
    if (!PcdProtocol || !PcdProtocol->Get8) {
      Status = EFI_NOT_FOUND;
      break; // or handle error
    }
    
    // Validate Get8 pointer is within SMRAM (example check)
    if (!IsPointerInSmram(PcdProtocol->Get8, sizeof(PcdProtocol->Get8))) {
      Status = EFI_SECURITY_VIOLATION;
      break;
    }
    
    if (PcdProtocol->Get8(0x23B) == 1) {
      FreeAndUnregister();
    }
  }
  break;
