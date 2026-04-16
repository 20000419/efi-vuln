__int64 sub_2890()
{
  __int64 result; // rax
  char v1; // al
  __int64 v2; // rax
  char v3; // bl
  char v4; // di
  char v5; // si
  signed __int64 v6; // rbx
  int v7; // eax
  __int64 v8; // rdx
  __int16 v9; // [rsp+30h] [rbp-98h] BYREF
  int v10; // [rsp+32h] [rbp-96h]
  int v11; // [rsp+36h] [rbp-92h]
  int v12; // [rsp+3Ah] [rbp-8Eh]
  int v13; // [rsp+3Eh] [rbp-8Ah]
  int v14; // [rsp+42h] [rbp-86h]
  char Destination; // [rsp+48h] [rbp-80h] BYREF
  char v16; // [rsp+49h] [rbp-7Fh]
  unsigned __int8 v17; // [rsp+4Bh] [rbp-7Dh]
  char v18; // [rsp+50h] [rbp-78h]
  char v19; // [rsp+51h] [rbp-77h]
  char v20; // [rsp+52h] [rbp-76h]
  char v21; // [rsp+55h] [rbp-73h]
  char v22; // [rsp+56h] [rbp-72h]
  char v23; // [rsp+58h] [rbp-70h]
  char v24; // [rsp+5Ah] [rbp-6Eh]
  void *v25; // [rsp+70h] [rbp-58h] BYREF
  __int64 v26; // [rsp+78h] [rbp-50h] BYREF
  __int64 (**v27)(void); // [rsp+80h] [rbp-48h] BYREF
  void *Interface; // [rsp+88h] [rbp-40h] BYREF
  EFI_EVENT Event; // [rsp+90h] [rbp-38h] BYREF
  char Data; // [rsp+D0h] [rbp+8h] BYREF
  UINT32 Attributes; // [rsp+D8h] [rbp+10h] BYREF
  void *v32; // [rsp+E0h] [rbp+18h] BYREF
  UINTN DataSize; // [rsp+E8h] [rbp+20h] BYREF

  Attributes = 3;
  DataSize = 1i64;
  v26 = 0i64;
  Data = 0;
  if ( (gBS->LocateProtocol(&SETUP_GUID, 0i64, &v27) & 0x8000000000000000ui64) == 0i64 )
    return (*v27)();
  result = gBS->LocateProtocol(&EFI_TPM_MP_DRIVER_PROTOCOL_GUID, 0i64, &Interface);
  if ( result >= 0 )
  {
    result = gBS->LocateProtocol(&EFI_TCG_PROTOCOL_GUID, 0i64, &v25);
    if ( result >= 0 )
    {
      result = gBS->LocateProtocol(&TCG_PLATFORM_SETUP_POLICY_GUID, 0i64, &v32);
      if ( result >= 0 )
      {
        v10 = 369098752;
        v9 = -16128;
        v12 = 0x4000000;
        v11 = 1702887424;
        if ( !sub_52F4() )
          v11 = 1694498816;
        v13 = 0x4000000;
        v14 = 134283264;
        (*(v25 + 3))(v25, 22i64, &v9, 256i64, &unk_6BD0);
        v9 = -16128;
        v10 = 369098752;
        v1 = sub_52F4();
        v12 = 83886080;
        v13 = 0x4000000;
        v11 = v1 != 0 ? 1702887424 : 1694498816;
        v14 = 285278208;
        v2 = (*(v25 + 3))(v25, 22i64, &v9, 512i64, &unk_70F0);
        v3 = byte_70FE;
        if ( v2 < 0 )
          v3 = 0;
        gBS->CopyMem(&Destination, v32 + 1, 0x1Bui64);
        v4 = v23;
        v5 = v24;
        v20 = v3;
        v18 = v23;
        v19 = v24;
        v21 = 0;
        if ( (gRT->GetVariable(L"TpmOldvar", &TC_EFI_GLOBAL_VARIABLE_GUID, &Attributes, &DataSize, &Data) & 0x8000000000000000ui64) == 0i64 )
        {
          if ( Data == v16 )
          {
            if ( v16 != (((v4 | v5) & 1) == 0) )
              v22 = 1;
          }
          else
          {
            Data = v16;
            DataSize = 1i64; // Re-initialize DataSize
            sub_55F0(L"TpmOldvar", &TC_EFI_GLOBAL_VARIABLE_GUID, Attributes, DataSize, &Data);
          }
        }
        else
        {
          Data = v16;
          DataSize = 1i64; // Re-initialize DataSize
          gRT->SetVariable(
            L"TpmOldvar",
            &TC_EFI_GLOBAL_VARIABLE_GUID,
            Attributes,
            DataSize,
            &Data);
        }
        if ( v22 )
        {
          v17 = 0;
          v22 = 0;
          v16 = ((v4 | v5) & 1) == 0;
          Data = v16;
          DataSize = 1i64; // Re-initialize DataSize
          sub_55F0(L"TpmOldvar", &TC_EFI_GLOBAL_VARIABLE_GUID, Attributes, DataSize, &Data);
        }
        byte_7342 = Destination;
        v6 = sub_593C(&v26);
        if ( v6 < 0 )
          v6 = gBS->CreateEventEx(0x200u, 8ui64, sub_260C, 0i64, &EFI_ACPI_20_TABLE_GUID, &Event);
        else
          sub_260C(0i64, 0i64);
        (*(v32 + 4))(&Destination, 0i64);
        if ( v16 == (((v4 | v5) & 1) == 0) )
        {
          if ( !v17 )
            return v6;
          v7 = sub_1D24(v17);
          v17 = 0;
        }
        else
        {
          v7 = sub_1D24(7 - (v16 != 0));
        }
        if ( v7 )
        {
          v21 = 1;
          (*(v32 + 4))(&Destination, 0i64);
          return 0i64;
        }
        LOBYTE(v8) = 1;
        (*(v32 + 4))(&Destination, v8);
        sub_E64(0);
        return v6;
      }
    }
  }
  return result;
}
