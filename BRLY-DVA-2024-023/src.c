__int64 __fastcall SwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        UINTN *CommBuffer,
        UINTN *CommBufferSize)
{
  UINTN Index; // r9
  __int64 v5; // rbx
  _DWORD *ControllablePtr; // rdi
  _DWORD *Ptr; // r11
  __int16 v8; // ax
  __int64 v9; // rcx
  EFI_GUID VendorGuid; // [rsp+30h] [rbp-228h] BYREF
  UINTN DataSize; // [rsp+40h] [rbp-218h] BYREF
  unsigned int RbxValue; // [rsp+22Ch] [rbp-2Ch] BYREF
  _DWORD *DellGnvsPtr; // [rsp+270h] [rbp+18h] BYREF

  Index = *CommBuffer;
  v5 = 0;
  VendorGuid.Data2 = 0x5A0;
  VendorGuid.Data3 = 0x40C4;
  VendorGuid.Data1 = 0xA602C5B;
  VendorGuid.Data4[0] = 0x91;
  VendorGuid.Data4[1] = 0x81;
  VendorGuid.Data4[2] = 0xED;
  VendorGuid.Data4[3] = 0xCD;
  VendorGuid.Data4[4] = 0x89;
  VendorGuid.Data4[5] = 0x1D;
  VendorGuid.Data4[6] = 0;
  VendorGuid.Data4[7] = 3;
  gEfiSmmCpuProtocol->ReadSaveState(gEfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RBX, Index, &RbxValue);
  ControllablePtr = RbxValue;
  DataSize = 4;
  gRT_0->GetVariable(L"DELL_GNVS_PTR", &VendorGuid, 0, &DataSize, &DellGnvsPtr);
  Ptr = DellGnvsPtr;
  if ( *DellGnvsPtr == 'TESQ' )
  {
    ControllablePtr = DellGnvsPtr + 2;
    *DellGnvsPtr = 0;                           // unchecked write (SMRAM corruption)
    Ptr = DellGnvsPtr;
  }
  if ( *Ptr == 'DESQ' )
  {
    ControllablePtr = Ptr + 2;
    *Ptr = 0;                                   // unchecked write (SMRAM corruption)
  }
  v8 = *gFuncTable;
  if ( *gFuncTable != 255 )
  {
    v9 = 0;
    while ( v8 != *ControllablePtr || *&gFuncTable[v9 + 2] != *(ControllablePtr + 1) )
    {
      ++v5;
      v9 = 12 * v5;
      v8 = *&gFuncTable[12 * v5];
      if ( v8 == 255 )
        return 0;
    }
    // multiple unchecked writes (SMRAM corruption) in functions from gFuncTable
    (*&gFuncTable[12 * v5 + 4])(ControllablePtr);
  }
  return 0;
}
