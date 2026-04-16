__int64 __fastcall SwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        UINTN *CommBuffer,
        UINTN *CommBufferSize)
{
  UINTN Index;
  __int64 v5;
  _DWORD *ControllablePtr;
  _DWORD *Ptr;
  __int16 v8;
  __int64 v9;
  EFI_GUID VendorGuid = {0xA602C5B, 0x5A0, 0x40C4, {0x91, 0x81, 0xED, 0xCD, 0x89, 0x1D, 0, 3}};
  UINTN DataSize;
  unsigned int RbxValue;
  _DWORD *DellGnvsPtr = 0;

  Index = *CommBuffer;
  v5 = 0;

  gEfiSmmCpuProtocol->ReadSaveState(gEfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RBX, Index, &RbxValue);
  ControllablePtr = (DWORD*)RbxValue;

  DataSize = sizeof(DellGnvsPtr);
  if (gRT_0->GetVariable(L"DELL_GNVS_PTR", &VendorGuid, 0, &DataSize, &DellGnvsPtr) != EFI_SUCCESS)
    return EFI_NOT_FOUND;

  // Validate NVRAM-derived pointer before use
  if (!SmmIsBufferOutsideSmmValid((UINTN)DellGnvsPtr, 4)) {
    return EFI_ACCESS_DENIED;
  }

  Ptr = DellGnvsPtr;

  // Validate and sanitize TESQ signature write
  if (*DellGnvsPtr == 'TESQ' && SmmIsBufferOutsideSmmValid((UINTN)DellGnvsPtr, sizeof(DWORD))) {
    ControllablePtr = DellGnvsPtr + 2;
    *DellGnvsPtr = 0;
    Ptr = DellGnvsPtr;
  }

  // Validate and sanitize DESQ signature write
  if (Ptr && *Ptr == 'DESQ' && SmmIsBufferOutsideSmmValid((UINTN)Ptr, sizeof(DWORD))) {
    ControllablePtr = Ptr + 2;
    *Ptr = 0;
  }

  v8 = *gFuncTable;
  if (*gFuncTable != 255) {
    v9 = 0;
    while (v8 != *ControllablePtr || *(&gFuncTable[v9 + 2]) != *(ControllablePtr + 1)) {
      ++v5;
      v9 = 12 * v5;
      v8 = *(&gFuncTable[12 * v5]);
      if (v8 == 255)
        return 0;
    }

    // Validate ControllablePtr with sufficient buffer size for deepest offset (e.g., +32 in sub_6A9C)
    if (ControllablePtr && SmmIsBufferOutsideSmmValid((UINTN)ControllablePtr, 36)) { // 36 bytes covers up to +32 offset
      (*(&gFuncTable[12 * v5 + 4]))(ControllablePtr);
    }
  }

  return 0;
}

// Platform-specific SMRAM validation function
BOOLEAN SmmIsBufferOutsideSmmValid(UINTN Address, UINTN Size) {
  const UINTN SMRAM_BASE = 0xE0000000;
  const UINTN SMRAM_SIZE = 0x2000000;

  if (!Address || Size == 0)
    return FALSE;

  return (Address >= SMRAM_BASE && Address + Size <= SMRAM_BASE + SMRAM_SIZE);
}
