__int64 __fastcall sub_42C()
{
  __int64 result; // rax
  void (__fastcall *v1)(int); // rax
  __int64 v2; // rbx
  int v3; // [rsp+30h] [rbp-2128h] BYREF
  __int16 v4; // [rsp+34h] [rbp-2124h]
  __int16 v5; // [rsp+36h] [rbp-2122h]
  char v6; // [rsp+38h] [rbp-2120h]
  char v7; // [rsp+39h] [rbp-211Fh]
  char v8; // [rsp+3Ah] [rbp-211Eh]
  char v9; // [rsp+3Bh] [rbp-211Dh]
  char v10; // [rsp+3Ch] [rbp-211Ch]
  char v11; // [rsp+3Dh] [rbp-211Bh]
  char v12; // [rsp+3Eh] [rbp-211Ah]
  char v13; // [rsp+3Fh] [rbp-2119h]
  int v14; // [rsp+40h] [rbp-2118h] BYREF
  __int16 v15; // [rsp+44h] [rbp-2114h]
  __int16 v16; // [rsp+46h] [rbp-2112h]
  char v17; // [rsp+48h] [rbp-2110h]
  char v18; // [rsp+49h] [rbp-210Fh]
  char v19; // [rsp+4Ah] [rbp-210Eh]
  char v20; // [rsp+4Bh] [rbp-210Dh]
  char v21; // [rsp+4Ch] [rbp-210Ch]
  char v22; // [rsp+4Dh] [rbp-210Bh]
  char v23; // [rsp+4Eh] [rbp-210Ah]
  char v24; // [rsp+4Fh] [rbp-2109h]
  __int64 v25; // [rsp+50h] [rbp-2108h] BYREF
  _QWORD v26[3]; // [rsp+58h] [rbp-2100h] BYREF
  _BYTE v27[128]; // [rsp+70h] [rbp-20E8h] BYREF
  __int64 v28; // [rsp+F0h] [rbp-2068h] BYREF
  char v29; // [rsp+13Dh] [rbp-201Bh]
  _BYTE v30[4024]; // [rsp+800h] [rbp-1958h] BYREF
  char v31; // [rsp+17B8h] [rbp-9A0h]
  unsigned int v32; // [rsp+2160h] [rbp+8h] BYREF
  unsigned int v33; // [rsp+2168h] [rbp+10h] BYREF
  __int64 v34; // [rsp+2170h] [rbp+18h] BYREF
  __int64 v35; // [rsp+2178h] [rbp+20h] BYREF

  v14 = -2124212326;
  v15 = -3302;
  v17 = -82;
  v16 = 16690;
  v18 = -34;
  v4 = -5212;
  v19 = -119;
  v20 = -13;
  v21 = 106;
  v22 = -18;
  v5 = 19381;
  v23 = 67;
  v24 = -38;
  v35 = 6475i64;
  v25 = 114i64;
  v26[0] = 1805i64;
  v3 = -326642109;
  v6 = -95;
  v7 = -27;
  v8 = 63;
  v9 = 62;
  v10 = 54;
  v11 = -78;
  v12 = 13;
  v13 = -87;
  sub_2970(qword_3688);
  (gRT_0->GetVariable)(L"Setup", &v3, &v34, v26, &v28);
  result = (gRT_0->GetVariable)(L"SocketIioConfig", &EFI_SOCKET_IIO_VARIABLE_GUID, &v32, &v35, v30);
  if ( v29 != v31 )
  {
    (gRT_0->GetVariable)(                       // <= first call (we can rewrite DataSize here)
      L"SocketCommonRcConfig",
      &EFI_SOCKET_COMMON_RC_VARIABLE_GUID,
      &v33,
      &v25,
      v27);
    v31 = v29;
    v27[6] = 3;
    (gRT_0->SetVariable)(L"SocketIioConfig", &EFI_SOCKET_IIO_VARIABLE_GUID, v32, v35, v30);
    (gRT_0->SetVariable)(                       // <= second call
      L"SocketCommonRcConfig",
      &EFI_SOCKET_COMMON_RC_VARIABLE_GUID,
      v33,
      v25,
      v27);
    (gRT_0->SetVariable)(L"LastBootFailedIoh", &v14, 3i64);
    v1 = funcs_636[0];
    v2 = 0i64;
    while ( v1 )
    {
      v1(0);
      v1 = funcs_636[++v2];
    }
    sub_28D4(0i64, 31i64, 2);
    __outbyte(0xCF9u, 2u);
    __outbyte(0xCF9u, 6u);
    v26[1] = 1i64;
    while ( 1 )
      ;
  }
  return result;
}
