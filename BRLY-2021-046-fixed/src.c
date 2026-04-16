EFI_PCD_PROTOCOL *gCachedEfiPcdProtocol = NULL; // Stored in SMRAM

EFI_PCD_PROTOCOL *LocateEfiPcdProtocol() {
  if (!gCachedEfiPcdProtocol) {
    // Acquire protocol during SMM initialization (once, safely)
    EFI_STATUS status = gSmst->SmmLocateProtocol(
      &EFI_PCD_PROTOCOL_GUID,
      NULL,
      (VOID**)&gCachedEfiPcdProtocol
    );
    if (EFI_ERROR(status)) {
      return NULL; // Or handle error appropriately
    }
  }
  return gCachedEfiPcdProtocol;
}

__int64 __fastcall sub_181C(unsigned int CbValue) {
  Value1 = 0;
  Value2 = 0;
  Flag = 0;

  // Validate proprietary protocol interface is not NULL or corrupted
  if (!ProprietaryProtocol3Interface || !ProprietaryProtocol3Interface->Func1) {
    return EFI_INVALID_PARAMETER;
  }

  // Use SMM-safe calls for proprietary protocol functions (assuming they're SMM-compatible)
  if (!ProprietaryProtocol3Interface->Func1(&gGuid_0, &Value1) &&
      !ProprietaryProtocol3Interface->Func3(&gGuid_0, &Value2)) {
    Flag = Value1 != Value2;
  }

  // Validate Func4 and Func6 pointers before use
  if (!ProprietaryProtocol3Interface->Func4 || !ProprietaryProtocol3Interface->Func6) {
    return EFI_UNSUPPORTED;
  }

  Res = ProprietaryProtocol3Interface->Func4(&gGuid_0, CbValue);
  if (!Res) {
    Res = ProprietaryProtocol3Interface->Func6(&gGuid_0, CbValue);
    if (!Res && Flag) {
      EFI_PCD_PROTOCOL *PcdProtocol = LocateEfiPcdProtocol();
      if (!PcdProtocol || !PcdProtocol->SetBool) {
        return EFI_NOT_FOUND;
      }
      // Validate SetBool pointer is within expected SMRAM-resident protocol
      if (!IsPointerInSmram(PcdProtocol->SetBool, sizeof(PcdProtocol->SetBool))) {
        return EFI_SECURITY_VIOLATION;
      }
      UINT8 Value = 1;
      PcdProtocol->SetBool(&gGuid, 0x40000002, &Value);
    }
  }
  return Res;
}
