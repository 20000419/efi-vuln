__int64 __fastcall SwSmiHandler(__int64 a1, __int64 a2, _QWORD *Index, __int64 a4)
{
  __int64 v4; // rsi
  __int64 Status_1; // rdi
  EFI_STATUS Status; // rax
  _DWORD *Ptr; // rcx
  __int16 v8; // ax
  _WORD *ControllablePtr; // rbx
  __int64 v10; // rcx
  void (__fastcall **AmiNvramControlProtocol)(__int64); // rax
  __int64 v12; // rcx
  _DWORD *DellGnvsPtr; // [rsp+30h] [rbp-28h] BYREF
  UINTN DataSize; // [rsp+38h] [rbp-20h] BYREF
  EFI_GUID VendorGuid; // [rsp+40h] [rbp-18h] BYREF
  _WORD *Value; // [rsp+70h] [rbp+18h] BYREF

  v4 = 0;
  VendorGuid.Data1 = 0xA602C5B;
  DellGnvsPtr = 0;
  VendorGuid.Data2 = 0x5A0;
  VendorGuid.Data3 = 0x40C4;
  VendorGuid.Data4[0] = 0x91;
  VendorGuid.Data4[1] = 0x81;
  VendorGuid.Data4[2] = 0xED;
  VendorGuid.Data4[3] = 0xCD;
  VendorGuid.Data4[4] = 0x89;
  VendorGuid.Data4[5] = 0x1D;
  VendorGuid.Data4[6] = 0;
  VendorGuid.Data4[7] = 3;
  if ( !Index || !a4 || *Index == -1 )
    return 0;
  Status_1 = (gSmmCpu->ReadSaveState)(gSmmCpu, 4, EFI_SMM_SAVE_STATE_REGISTER_RBX, *Index, &Value);
  if ( gFromVariable == 1 )
  {
    DataSize = 4;
    Status = gRT_0->GetVariable(L"DELL_GNVS_PTR", &VendorGuid, 0, &DataSize, &DellGnvsPtr);
    Ptr = DellGnvsPtr;
    Status_1 = Status;
    if ( *DellGnvsPtr == 'TESQ' )
    {
      Value = DellGnvsPtr + 2;
      *DellGnvsPtr = 0;                         // unchecked write (SMRAM corruption)
      Ptr = DellGnvsPtr;
    }
    if ( *Ptr == 'DESQ' )
    {
      Value = Ptr + 2;
      *Ptr = 0;                                 // unchecked write (SMRAM corruption)
    }
  }
  v8 = gFuncTable[0];
  if ( gFuncTable[0] != 255 )
  {
    ControllablePtr = Value;
    v10 = 0;
    while ( v8 != *Value || *(&gFuncTable[1] + v10) != Value[1] )
    {
      ++v4;
      v10 = 12 * v4;
      v8 = gFuncTable[6 * v4];
      if ( v8 == 255 )
        return Status_1;
    }
    AmiNvramControlProtocol = gAmiNvramControlProtocol;
    if ( gAmiNvramControlProtocol
      || (AmiNvramControlProtocol = GetVendorTable(&AMI_NVRAM_CONTROL_PROTOCOL_GUID),
          (gAmiNvramControlProtocol = AmiNvramControlProtocol) != 0) )
    {
      LOBYTE(v10) = 1;
      (*AmiNvramControlProtocol)(v10);
      if ( gAmiNvramControlProtocol )
        (*(gAmiNvramControlProtocol + 8))(0);
      ControllablePtr = Value;
    }
    // multiple unchecked writes (SMRAM corruption) in functions from gFuncTable
    (*&gFuncTable[6 * v4 + 2])(ControllablePtr);
    if ( gAmiNvramControlProtocol )
    {
      (*gAmiNvramControlProtocol)(0);
      if ( gAmiNvramControlProtocol )
      {
        LOBYTE(v12) = 1;
        (*(gAmiNvramControlProtocol + 8))(v12);
      }
    }
  }
  return Status_1;
}
