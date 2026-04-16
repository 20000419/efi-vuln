__int64 __fastcall SwSmiHandler(__int64 a1, __int64 a2, _QWORD *Index, __int64 a4)
{
  __int64 v4;
  EFI_STATUS Status;
  _DWORD *Ptr;
  _WORD *ControllablePtr;
  _DWORD *DellGnvsPtr = 0;
  UINTN DataSize;
  EFI_GUID VendorGuid = {
    0xA602C5B, 0x5A0, 0x40C4,
    {0x91, 0x81, 0xED, 0xCD, 0x89, 0x1D, 0, 3}
  };

  if (!Index || !a4 || *Index == -1)
    return 0;

  if (gFromVariable == 1) {
    DataSize = sizeof(DellGnvsPtr);
    Status = gRT_0->GetVariable(L"DELL_GNVS_PTR", &VendorGuid, 0, &DataSize, &DellGnvsPtr);
    
    // Validate pointer from NVRAM before use
    if (Status == EFI_SUCCESS && !SmmIsBufferOutsideSmmValid(DellGnvsPtr, 4)) {
      return EFI_ACCESS_DENIED;
    }

    Ptr = DellGnvsPtr;
    
    // Validate and sanitize TESQ signature write
    if (DellGnvsPtr && *DellGnvsPtr == 'TESQ' && SmmIsBufferOutsideSmmValid(DellGnvsPtr, sizeof(DWORD))) {
      *DellGnvsPtr = 0;
      Ptr = DellGnvsPtr;
    }
    
    // Validate and sanitize DESQ signature write
    if (Ptr && *Ptr == 'DESQ' && SmmIsBufferOutsideSmmValid(Ptr, sizeof(DWORD))) {
      *Ptr = 0;
    }
  }

  if (gFuncTable[0] != 255) {
    ControllablePtr = Value; // Assume Value comes from validated save state
    
    // Add validation before function table calls that perform writes
    if (ControllablePtr && SmmIsBufferOutsideSmmValid(ControllablePtr, 19*sizeof(WORD))) { // Cover max offset 18
      (*&gFuncTable[6 * v4 + 2])(ControllablePtr);
    }
  }

  return Status_1;
}

// Example validation function (should be implemented in SMM context)
BOOLEAN SmmIsBufferOutsideSmmValid(UINTN Address, UINTN Size) {
  UINTN SmramBase = 0xE0000000;
  UINTN SmramSize = 0x2000000;
  
  if (!Address || Size == 0)
    return FALSE;
    
  return (Address >= SmramBase && Address + Size <= SmramBase + SmramSize);
}
