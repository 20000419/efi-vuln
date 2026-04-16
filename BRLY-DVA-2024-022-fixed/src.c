EFI_STATUS __fastcall SwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        UINTN *CommBuffer,
        UINTN *CommBufferSize)
{
  UINTN Index;
  __int64 v5;
  unsigned __int64 ControllablePtr;
  _DWORD *Ptr;
  __int16 v8;
  __int64 v9;
  EFI_GUID VendorGuid = {0xA602C5B, 0x5A0, 0x40C4, {0x91, 0x81, 0xED, 0xCD, 0x89, 0x1D, 0, 3}};
  UINTN DataSize;
  int RbxValue[11];
  _DWORD *DellGnvsPtr = 0;

  Index = *CommBuffer;
  v5 = 0;

  gEfiSmmCpuProtocol->ReadSaveState(gEfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RBX, Index, RbxValue);
  ControllablePtr = RbxValue[0];

  DataSize = 4;
  gRT_0->GetVariable(L"DELL_GNVS_PTR", &VendorGuid, 0, &DataSize, &DellGnvsPtr);
  
  // Validate pointer from NVRAM
  if (!SmmIsBufferOutsideSmmValid((UINTN)DellGnvsPtr, 4)) {
    return EFI_ACCESS_DENIED;
  }

  Ptr = DellGnvsPtr;
  
  // Validate and sanitize TESQ signature write
  if (*DellGnvsPtr == 'TESQ' && SmmIsBufferOutsideSmmValid((UINTN)DellGnvsPtr, 4)) {
    ControllablePtr = (DellGnvsPtr + 2);
    *DellGnvsPtr = 0;
    Ptr = DellGnvsPtr;
  }
  
  // Validate and sanitize DESQ signature write
  if (*Ptr == 'DESQ' && SmmIsBufferOutsideSmmValid((UINTN)Ptr, 4)) {
    ControllablePtr = (Ptr + 2);
    *Ptr = 0;
  }

  v8 = gFuncTable[0];
  if (gFuncTable[0] != 255) {
    v9 = 0;
    while (v8 != *ControllablePtr || gFuncTable[v9 + 1] != *(ControllablePtr + 2)) {
      ++v5;
      v9 = 6 * v5;
      v8 = gFuncTable[6 * v5];
      if (v8 == 255)
        return 0;
    }
    
    // Validate ControllablePtr before function call
    if (SmmIsBufferOutsideSmmValid((UINTN)ControllablePtr, 28)) { // Check 7 DWORDs (0-6)
      (*&gFuncTable[6 * v5 + 2])(ControllablePtr);
    }
  }
  return 0;
}

// Example validation function (should be platform-specific)
BOOLEAN SmmIsBufferOutsideSmmValid(UINTN Address, UINTN Size) {
  UINTN SmramBase = 0xE0000000; // Example SMRAM base
  UINTN SmramSize = 0x2000000;  // Example SMRAM size
  
  return (Address >= SmramBase && Address + Size <= SmramBase + SmramSize);
}
