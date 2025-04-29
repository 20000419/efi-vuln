__int64 __fastcall SwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        UINTN *CommBuffer,
        UINTN *CommBufferSize)
{
  __int64 DellWmiSharedMem; // rax
  __int64 v5; // rdi
  int v7; // ecx
  int v8; // r9d
  unsigned int v9; // r8d
  unsigned int v10; // edx
  UINTN CpuIndex; // rbx
  char *v12; // rax
  __int64 v13; // r9
  char *v14; // rcx
  __int128 v15; // xmm1
  __int128 v16; // xmm0
  __int128 v17; // xmm1
  __int128 v18; // xmm0
  __int128 v19; // xmm1
  __int128 v20; // xmm0
  __int128 v21; // xmm1
  __int64 Status; // rax
  __int64 v23; // rax
  _DWORD *Ptr; // rcx
  unsigned int Data; // [rsp+30h] [rbp-D0h] BYREF
  EFI_GUID VendorGuid; // [rsp+38h] [rbp-C8h] BYREF
  UINTN DataSize; // [rsp+48h] [rbp-B8h] BYREF
  char v28; // [rsp+50h] [rbp-B0h] BYREF
  int Buffer; // [rsp+220h] [rbp+120h] BYREF
  unsigned int v30; // [rsp+224h] [rbp+124h] BYREF
  unsigned int v31; // [rsp+228h] [rbp+128h] BYREF
  int v32[9]; // [rsp+22Ch] [rbp+12Ch] BYREF
  char v33[464]; // [rsp+250h] [rbp+150h] BYREF
  _DWORD v34[3]; // [rsp+420h] [rbp+320h] BYREF
  unsigned int v35; // [rsp+42Ch] [rbp+32Ch] BYREF

  DellWmiSharedMem = gDellWmiSharedMem;
  v5 = 0;
  DataSize = 0;
  Data = 0;
  VendorGuid.Data1 = 0x8CC2B3F1;
  *&VendorGuid.Data2 = 0x4784EC41;
  *VendorGuid.Data4 = 0x5D4C4884;
  *&VendorGuid.Data4[4] = 0x91471358;
  if ( (gDellWmiSharedMem
     || ((DataSize = 4,
          (gRT->GetVariable(L"DELL_WMI_SHARED_MEM", &VendorGuid, 0, &DataSize, &Data) & 0x8000000000000000) != 0)
       ? (DellWmiSharedMem = gDellWmiSharedMem)
       : (DellWmiSharedMem = Data, gDellWmiSharedMem = Data),
         DellWmiSharedMem))
    && *DellWmiSharedMem == 'DWMI' )
  {
    if ( *(DellWmiSharedMem + 20) )
    {
      v7 = Buffer;
    }
    else
    {
      v7 = *(DellWmiSharedMem + 24);
      Buffer = v7;
    }
    if ( (*(DellWmiSharedMem + 20) & 0xFF00) != 0 )
    {
      v8 = v32[0];
    }
    else
    {
      v8 = *(DellWmiSharedMem + 28);
      v32[0] = v8;
    }
    if ( (*(DellWmiSharedMem + 20) & 0xFF0000) != 0 )
    {
      v9 = v30;
    }
    else
    {
      v9 = *(DellWmiSharedMem + 32);
      v30 = v9;
    }
    if ( (*(DellWmiSharedMem + 20) & 0xFF000000) != 0 )
    {
      v10 = v31;
    }
    else
    {
      v10 = *(DellWmiSharedMem + 36);
      v31 = v10;
    }
    if ( *(DellWmiSharedMem + 20) )
      v7 = DellWmiSharedMem + 48;
    Buffer = v7;
    if ( (*(DellWmiSharedMem + 20) & 0xFF00) != 0 )
      v8 = DellWmiSharedMem + 48;
    v32[0] = v8;
    CpuIndex = DataSize;
    if ( (*(DellWmiSharedMem + 20) & 0xFF0000) != 0 )
      v9 = DellWmiSharedMem + 48;
    v30 = v9;
    if ( (*(DellWmiSharedMem + 20) & 0xFF000000) != 0 )
    {
      v10 = DellWmiSharedMem + 48;
      v31 = DellWmiSharedMem + 48;
    }
  }
  else
  {
    CpuIndex = *CommBuffer;
    gEfiSmmCpuProtocol->ReadSaveState(gEfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RAX, CpuIndex, &Buffer);
    gEfiSmmCpuProtocol->ReadSaveState(gEfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RBX, CpuIndex, v32);
    gEfiSmmCpuProtocol->ReadSaveState(gEfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RCX, CpuIndex, &v30);
    gEfiSmmCpuProtocol->ReadSaveState(gEfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RDX, CpuIndex, &v31);
    v10 = v31;
    v9 = v30;
  }
  v12 = v33;
  v13 = 4;
  v14 = &v28;
  do
  {
    v15 = *(v14 + 1);
    *v12 = *v14;
    v16 = *(v14 + 2);
    *(v12 + 1) = v15;
    v17 = *(v14 + 3);
    *(v12 + 2) = v16;
    v18 = *(v14 + 4);
    *(v12 + 3) = v17;
    v19 = *(v14 + 5);
    *(v12 + 4) = v18;
    v20 = *(v14 + 6);
    *(v12 + 5) = v19;
    v21 = *(v14 + 7);
    v14 += 128;
    *(v12 + 6) = v20;
    v12 += 128;
    *(v12 - 1) = v21;
    --v13;
  }
  while ( v13 );
  if ( !v10 )
    goto LABEL_34;
  if ( !gAmiSmmBufferValidationProtocol )
    return EFI_ACCESS_DENIED;
  Status = (gAmiSmmBufferValidationProtocol->ValidateMemoryBuffer)(v10, v9);
  if ( Status >= 0 )
  {
LABEL_34:
    if ( gFuncTable[0] != -1 )
    {
      v23 = 0LL;
      while ( gFuncTable[v23 + 1] != LOBYTE(v34[0])
           || gFuncTable[v23] != 1
           && (gFuncTable[v23 + 2] != BYTE1(v34[0])
            || gFuncTable[v23] != 2
            && (gFuncTable[v23 + 3] != v35 || gFuncTable[v23] != 3 && gFuncTable[v23 + 4] != BYTE1(v35))) )
      {
        ++v5;
        v23 = 13 * v5;
        if ( gFuncTable[13 * v5] == -1 )
          return 0;
      }
      (*&gFuncTable[13 * v5 + 5])(v33, v34[0], v35, *(v34 + 1));
      Ptr = gDellWmiSharedMem;
      if ( *gDellWmiSharedMem == 'DWMI' )
      {
        *gDellWmiSharedMem = 0;
        Ptr[6] = v34[0];                        // unchecked write (SMRAM corruption)
        Ptr[7] = v35;                           // unchecked write (SMRAM corruption)
        Ptr[8] = v34[1];                        // unchecked write (SMRAM corruption)
        Ptr[9] = v34[2];                        // unchecked write (SMRAM corruption)
      }
      else
      {
        if ( v34[0] != Buffer )
          gEfiSmmCpuProtocol->WriteSaveState(gEfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RAX, CpuIndex, v34);
        if ( v35 != v32[0] )
          gEfiSmmCpuProtocol->WriteSaveState(gEfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RBX, CpuIndex, &v35);
        if ( v34[1] != v30 )
          gEfiSmmCpuProtocol->WriteSaveState(
            gEfiSmmCpuProtocol,
            4,
            EFI_SMM_SAVE_STATE_REGISTER_RCX,
            CpuIndex,
            &v34[1]);
        if ( v34[2] != v31 )
          gEfiSmmCpuProtocol->WriteSaveState(
            gEfiSmmCpuProtocol,
            4,
            EFI_SMM_SAVE_STATE_REGISTER_RDX,
            CpuIndex,
            &v34[2]);
      }
    }
    return 0;
  }
  return Status;
}
