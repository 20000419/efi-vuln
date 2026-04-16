char sub_B220()
{
  __int64 v0; // rbx
  char result; // al
  char v2; // dl
  unsigned __int8 v3; // bl
  char v4; // dl
  int v5; // ecx
  int v6; // edx
  int v7; // ecx
  unsigned __int8 v8; // bl
  char v9; // dl
  void *Interface; // [rsp+30h] [rbp-40h] BYREF
  __int64 Data; // [rsp+38h] [rbp-38h] BYREF
  __int64 v12; // [rsp+40h] [rbp-30h]
  char v13[8]; // [rsp+48h] [rbp-28h]
  __int64 v14; // [rsp+50h] [rbp-20h] BYREF
  __int64 v15; // [rsp+58h] [rbp-18h]
  char v16; // [rsp+60h] [rbp-10h]
  int v17; // [rsp+90h] [rbp+20h] BYREF
  UINTN DataSize; // [rsp+98h] [rbp+28h] BYREF
  int v19; // [rsp+A0h] [rbp+30h] BYREF
  __int16 v20; // [rsp+A4h] [rbp+34h]
  char v21; // [rsp+A6h] [rbp+36h]
  void *HeciProtocol; // [rsp+A8h] [rbp+38h] BYREF

  Data = 0i64;
  v12 = 0i64;
  v13[0] = 0;
  v14 = 0i64;
  v15 = 0i64;
  v16 = 0;
  v19 = 0;
  v20 = 0;
  v21 = 0;
  v0 = gBS->LocateProtocol(&HECI_PROTOCOL_GUID, 0i64, &Interface);
  result = sub_FF2C();
  if ( !result && v0 >= 0 )
  {
    DataSize = 17i64;
    gRT->GetVariable(
      L"MeSetupStorage",
      &ME_SETUP_VARIABLE_GUID,
      0i64,
      &DataSize,
      &Data);
    // Re-initialize DataSize to correct buffer size before second GetVariable
    DataSize = 17i64; // Match expected buffer size for MeBackupStorage
    gRT->GetVariable(
      L"MeBackupStorage",
      &ME_SETUP_VARIABLE_GUID,
      0i64,
      &DataSize,
      &v14);
    DataSize = 143i64;
    gRT->GetVariable(L"MeSetup", &ME_SETUP_VARIABLE_GUID, 0i64, &DataSize, &unk_A0F80);
    DataSize = 7i64;
    gRT->GetVariable(L"TcgSetup", &EFI_SETUP_VARIABLE_GUID, 0i64, &DataSize, &v19);
    if ( BYTE4(v12) != BYTE4(v15) && !byte_A0FAA && BYTE4(v12) == 1 )
      sub_F120();
    if ( BYTE2(Data) != BYTE2(v14) )
    {
      byte_A0891 = 1;
      if ( BYTE2(Data) )
      {
        sub_F320();
      }
      else if ( (gBS->LocateProtocol(&HECI_PROTOCOL_GUID, 0i64, &HeciProtocol) & 0x8000000000000000ui64) == 0i64 )
      {
        (*(HeciProtocol + 8))(&v17);
        if ( v17 != 3 && !sub_FF2C() )
          sub_ED6C(6, v2, 0);
      }
    }
    v3 = BYTE1(Data);
    if ( BYTE1(Data) != BYTE1(v14) && !sub_FF2C() )
      sub_ED6C(7, v4, v3);
    if ( Data != v14 )
    {
      byte_A0891 = 1;
      if ( Data == 1 )
      {
        v5 = 4;
        v6 = 0;
      }
      else
      {
        v5 = 0;
        v6 = 4;
      }
      sub_F414(v5, v6);
    }
    v7 = byte_A0891;
    v8 = BYTE6(Data);
    if ( BYTE5(Data) != BYTE5(v14) )
      v7 = 1;
    byte_A0891 = v7;
    if ( BYTE6(Data) != BYTE6(v14) && v19 == 1 && !sub_FF2C() )
      sub_ED6C(47, v9, v8);
    LOBYTE(v7) = BYTE2(v12);
    if ( BYTE2(v12) != BYTE2(v15) )
    {
      byte_A0891 = 1;
      sub_EF84(SBYTE2(v12));
    }
    if ( BYTE3(v12) != BYTE3(v15) )
      sub_F5C0(BYTE3(v12));
    if ( HIBYTE(v12) != HIBYTE(v15) )
      sub_FBAC(v7, SHIBYTE(v12));
    if ( v13[0] != v16 )
      sub_FD30(v7, v13[0]);
    return gRT->SetVariable(L"MeBackupStorage", &ME_SETUP_VARIABLE_GUID, 2u, 0x11ui64, &Data);
  }
  return result;
}
