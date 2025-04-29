char __fastcall AmiSetupNvramUpdateCallback(EFI_CAPSULE_HEADER **CapsuleHeaderArray)
{
  __int64 Status; // rax
  __int64 Status_1; // rbx
  UINTN v4; // rdx
  void **v5; // r8
  char v6; // dl
  unsigned __int8 v7; // bl
  char v8; // dl
  int v9; // ecx
  int v10; // edx
  EFI_MEMORY_TYPE MemoryType; // ecx
  UINTN v12; // rdx
  EFI_PHYSICAL_ADDRESS v13; // r8
  void *v15; // [rsp+30h] [rbp-50h] BYREF
  void *Interface; // [rsp+38h] [rbp-48h] BYREF
  void *v17; // [rsp+40h] [rbp-40h] BYREF
  char MeSetupStorageData[17]; // [rsp+48h] [rbp-38h] BYREF
  char MeBackupStorageData[17]; // [rsp+60h] [rbp-20h] BYREF
  EFI_MEMORY_TYPE PoolType; // [rsp+B0h] [rbp+30h] BYREF
  UINTN DataSize; // [rsp+B8h] [rbp+38h] BYREF

  memset(MeSetupStorageData, 0, sizeof(MeSetupStorageData));
  memset(MeBackupStorageData, 0, sizeof(MeBackupStorageData));
  Status = gBS->LocateProtocol(&AMI_SETUP_NVRAM_UPDATE_GUID, 0, &Interface);
  if ( Status >= 0 )
  {
    Status_1 = gBS->LocateProtocol(&ProprietaryProtocol_2, 0, &v17);
    LOBYTE(Status) = sub_1D8C4();
    if ( !Status && Status_1 >= 0 )
    {
      DataSize = 17;
      gRT->GetVariable(L"MeSetupStorage", &gVariableGuid, 0, &DataSize, MeSetupStorageData);
      gRT->GetVariable(L"MeBackupStorage", &gVariableGuid, 0, &DataSize, MeBackupStorageData);
      DataSize = 53;
      gRT->GetVariable(L"MeSetup", &gVariableGuid, 0, &DataSize, &unk_27E60);
      if ( MeSetupStorageData[12] != MeBackupStorageData[12] && !byte_27E8A && MeSetupStorageData[12] == 1 )
        sub_1CAB8();
      if ( MeSetupStorageData[2] != MeBackupStorageData[2] )
      {
        gMemoryType = 1;
        if ( MeSetupStorageData[2] )
        {
          sub_1CCB8();
        }
        else if ( (gBS->LocateProtocol(&ProprietaryProtocol_2, 0, &v15) & 0x8000000000000000) == 0 )
        {
          (*(v15 + 8))(&PoolType, v4, v5);
          if ( PoolType != EfiBootServicesCode && !sub_1D8C4() )
            sub_1C704(6, v6, 0);
        }
      }
      v7 = MeSetupStorageData[1];
      if ( MeSetupStorageData[1] != MeBackupStorageData[1] && !sub_1D8C4() )
        sub_1C704(7, v8, v7);
      if ( MeSetupStorageData[0] != MeBackupStorageData[0] )
      {
        gMemoryType = 1;
        if ( MeSetupStorageData[0] == 1 )
        {
          v9 = 4;
          v10 = 0;
        }
        else
        {
          v9 = 0;
          v10 = 4;
        }
        sub_1CDAC(v9, v10);
      }
      MemoryType = gMemoryType;
      if ( MeSetupStorageData[5] != MeBackupStorageData[5] )
        MemoryType = EfiLoaderCode;
      gMemoryType = MemoryType;
      LOBYTE(MemoryType) = MeSetupStorageData[10];
      if ( MeSetupStorageData[10] != MeBackupStorageData[10] )
      {
        gMemoryType = 1;
        sub_1C91C(MeSetupStorageData[10]);
      }
      if ( MeSetupStorageData[11] != MeBackupStorageData[11] )
        sub_1CF58(MeSetupStorageData[11]);
      if ( MeSetupStorageData[15] != MeBackupStorageData[15] )
        sub_1D544(MemoryType, MeSetupStorageData[15]);
      if ( MeSetupStorageData[16] != MeBackupStorageData[16] )
        sub_1D6C8(MemoryType, MeSetupStorageData[16]);
      LOBYTE(Status) = gRT->SetVariable(L"MeBackupStorage", &gVariableGuid, 2, 0x11, MeSetupStorageData);
      if ( CapsuleHeaderArray )
        LOBYTE(Status) = (gBS->CloseEvent)(CapsuleHeaderArray, v12, v13);
    }
  }
  return Status;
}
