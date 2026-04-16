__int64 __fastcall sub_E74()
{
  char v0; // bl
  __int64 result; // rax
  unsigned __int8 v2; // al
  __int64 (__fastcall **v3)(__int64); // rax
  bool v4; // zf
  int v5; // eax
  UINTN v6; // [rsp+30h] [rbp-D0h] BYREF
  UINTN DataSize; // [rsp+38h] [rbp-C8h] BYREF
  char Data[91]; // [rsp+40h] [rbp-C0h] BYREF
  int v9; // [rsp+9Bh] [rbp-65h]
  int v10; // [rsp+9Fh] [rbp-61h]
  int v11; // [rsp+A9h] [rbp-57h]
  char v12[2048]; // [rsp+2D0h] [rbp+1D0h] BYREF
  UINT32 Attributes; // [rsp+AE0h] [rbp+9E0h] BYREF
  UINT32 v14; // [rsp+AE8h] [rbp+9E8h] BYREF
  void *Interface; // [rsp+AF0h] [rbp+9F0h] BYREF
  void *v16; // [rsp+AF8h] [rbp+9F8h] BYREF

  Interface = 0i64;
  v16 = 0i64;
  v0 = 0;
  result = gBS->LocateProtocol(&PLATFORM_NVS_AREA_PROTOCOL_GUID, 0i64, &Interface);
  if ( result >= 0 )
  {
    if ( (gBS->LocateProtocol(&UNKNOWN_PROTOCOL_GUID_0, 0i64, &v16) & 0x8000000000000000ui64) == 0i64 )
    {
      while ( 1 )
      {
        (*((void (__fastcall **)(void *, __int64, __int64))v16 + 3))(v16, 166i64, 1i64);
        __outbyte(0x910u, 0x11u);
        v2 = __inbyte(0x911u);
        if ( ((v2 + 1) & 0xFE) != 0 )
          break;
        if ( (unsigned __int8)++v0 >= 3u )
          goto LABEL_7;
      }
      switch ( v2 )
      {
        case 1u:
LABEL_7:
          *(_BYTE *)(*(_QWORD *)Interface + 2079i64) = 0;
          break;
        case 2u:
          *(_BYTE *)(*(_QWORD *)Interface + 2079i64) = 1;
          break;
        case 4u:
          *(_BYTE *)(*(_QWORD *)Interface + 2079i64) = 2;
          break;
        case 8u:
          *(_BYTE *)(*(_QWORD *)Interface + 2079i64) = 3;
          break;
      }
    }
    DataSize = 654i64;
    result = gRT->GetVariable((CHAR16 *)L"CpuSetup", &CPU_SETUP_VARIABLE_GUID, &Attributes, &DataSize, Data);
    if ( result >= 0 )
    {
      v3 = (__int64 (__fastcall **)(__int64))sub_1824();
      v4 = (v3[1](306i64) & 1) == 0;
      v5 = 100000;
      if ( v4 )
        v5 = 109000;
      v11 = v5;
      v10 = v5;
      v9 = v5;
      gRT->SetVariable((CHAR16 *)L"CpuSetup", &CPU_SETUP_VARIABLE_GUID, Attributes, 0x28Eui64, Data);
      v6 = 2028i64;
      gRT->GetVariable(                         // <= first call (we can rewrite DataSize here)
        (CHAR16 *)L"PchSetup",
        &PCH_SETUP_VARIABLE_GUID,
        &v14,
        &v6,
        v12);
      v12[1712] = 0;
      return gRT->SetVariable(                  // <= second call
               (CHAR16 *)L"PchSetup",
               &PCH_SETUP_VARIABLE_GUID,
               v14,
               v6,
               v12);
    }
  }
  return result;
}
