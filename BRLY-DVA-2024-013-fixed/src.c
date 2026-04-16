__int64 __fastcall SwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        UINTN *CommBuffer,
        UINTN *CommBufferSize)
{
  __int64 DellWmiSharedMem;
  // ... [existing variable declarations] ...

  VendorGuid.Data1 = 0x8CC2B3F1;
  *&VendorGuid.Data2 = 0x4784EC41;
  *VendorGuid.Data4 = 0x5D4C4884;
  *&VendorGuid.Data4[4] = 0x91471358;

  if (gDellWmiSharedMem == 0) {
    DataSize = 4;
    if (gRT->GetVariable(L"DELL_WMI_SHARED_MEM", &VendorGuid, 0, &DataSize, &Data) != EFI_SUCCESS) {
      return EFI_NOT_FOUND;
    }
    DellWmiSharedMem = Data;
    
    // Validate pointer after retrieval from NVRAM
    if (!SmmIsBufferOutsideSmmValid(DellWmiSharedMem, 40)) { // Check 40 bytes for safety
      return EFI_ACCESS_DENIED;
    }
    gDellWmiSharedMem = DellWmiSharedMem;
  } else {
    DellWmiSharedMem = gDellWmiSharedMem;
  }

  // ... [existing logic up to write operations] ...

  if (gFuncTable[0] != -1) {
    // ... [existing loop to find function] ...

    Ptr = gDellWmiSharedMem;
    
    // Validate base pointer before any writes
    if (!SmmIsBufferOutsideSmmValid(Ptr, 40)) { // 40 bytes covers indices 6-9 (4*4=16 bytes)
      return EFI_ACCESS_DENIED;
    }

    if (*gDellWmiSharedMem == 'DWMI') {
      // Validate each write location individually
      if (SmmIsBufferOutsideSmmValid(Ptr + 6 * sizeof(DWORD), sizeof(DWORD))) {
        Ptr[6] = v34[0];
      }
      if (SmmIsBufferOutsideSmmValid(Ptr + 7 * sizeof(DWORD), sizeof(DWORD))) {
        Ptr[7] = v35;
      }
      if (SmmIsBufferOutsideSmmValid(Ptr + 8 * sizeof(DWORD), sizeof(DWORD))) {
        Ptr[8] = v34[1];
      }
      if (SmmIsBufferOutsideSmmValid(Ptr + 9 * sizeof(DWORD), sizeof(DWORD))) {
        Ptr[9] = v34[2];
      }
    } else {
      // ... [existing non-SMRAM write logic] ...
    }
  }

  return 0;
}
