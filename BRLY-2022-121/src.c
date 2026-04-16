__int64 sub_2608()
{
  char v0; // bl
  char v1; // di
  unsigned __int8 v2; // bl
  __int64 v3; // rax
  int v4; // edx
  __int64 result; // rax
  char v6; // al
  int v7; // [rsp+30h] [rbp-9E8h] BYREF
  __int16 v8; // [rsp+34h] [rbp-9E4h]
  __int16 v9; // [rsp+36h] [rbp-9E2h]
  char v10; // [rsp+38h] [rbp-9E0h]
  char v11; // [rsp+39h] [rbp-9DFh]
  char v12; // [rsp+3Ah] [rbp-9DEh]
  char v13; // [rsp+3Bh] [rbp-9DDh]
  char v14; // [rsp+3Ch] [rbp-9DCh]
  char v15; // [rsp+3Dh] [rbp-9DBh]
  char v16; // [rsp+3Eh] [rbp-9DAh]
  char v17; // [rsp+3Fh] [rbp-9D9h]
  int v18; // [rsp+40h] [rbp-9D8h] BYREF
  __int16 v19; // [rsp+44h] [rbp-9D4h]
  __int16 v20; // [rsp+46h] [rbp-9D2h]
  char v21; // [rsp+48h] [rbp-9D0h]
  char v22; // [rsp+49h] [rbp-9CFh]
  char v23; // [rsp+4Ah] [rbp-9CEh]
  char v24; // [rsp+4Bh] [rbp-9CDh]
  char v25; // [rsp+4Ch] [rbp-9CCh]
  char v26; // [rsp+4Dh] [rbp-9CBh]
  char v27; // [rsp+4Eh] [rbp-9CAh]
  char v28; // [rsp+4Fh] [rbp-9C9h]
  int v29; // [rsp+50h] [rbp-9C8h] BYREF
  unsigned int v30; // [rsp+54h] [rbp-9C4h] BYREF
  unsigned int v31; // [rsp+58h] [rbp-9C0h] BYREF
  unsigned int v32; // [rsp+5Ch] [rbp-9BCh] BYREF
  __int64 v33; // [rsp+60h] [rbp-9B8h] BYREF
  __int64 v34; // [rsp+68h] [rbp-9B0h] BYREF
  _QWORD v35[2]; // [rsp+70h] [rbp-9A8h] BYREF
  __int64 v36; // [rsp+80h] [rbp-998h] BYREF
  _BYTE v37[763]; // [rsp+90h] [rbp-988h] BYREF
  char v38; // [rsp+38Bh] [rbp-68Dh]
  char v39; // [rsp+3A0h] [rbp-678h]
  char v40; // [rsp+3A1h] [rbp-677h]
  char v41; // [rsp+3EEh] [rbp-62Ah]
  char v42; // [rsp+444h] [rbp-5D4h]
  char v43; // [rsp+470h] [rbp-5A8h]
  _BYTE v44[632]; // [rsp+7A0h] [rbp-278h] BYREF
  char v45; // [rsp+A20h] [rbp+8h] BYREF
  int v46; // [rsp+A28h] [rbp+10h] BYREF
  unsigned int v47; // [rsp+A30h] [rbp+18h] BYREF
  unsigned int v48; // [rsp+A38h] [rbp+20h] BYREF

  v8 = 5729;
  v9 = 18403;
  v19 = 26188;
  v20 = 19799;
  v35[0] = 0i64;
  v29 = 0;
  v36 = 1805i64;
  v7 = 758045968;
  v10 = -67;
  v11 = -1;
  v12 = 88;
  v13 = 31;
  v14 = 42;
  v15 = 99;
  v16 = -20;
  v17 = 13;
  v18 = 1029781824;
  v21 = -114;
  v22 = -2;
  v23 = 54;
  v24 = 61;
  v25 = -77;
  v26 = -56;
  v27 = -18;
  v28 = -14;
  v45 = 0;
  sub_19544(17170444, 0i64, 2i64, 0i64, (int *)&v47);
  v47 >>= 1;
  v0 = v47;
  sub_19544(17170445, 0i64, 2i64, 0i64, (int *)&v48);
  v48 >>= 1;
  v1 = v0 | (2 * v48);
  if ( ((__int64 (__fastcall *)(EFI_GUID *, _QWORD, _QWORD *))gBS->LocateProtocol)(&UNKNOWN_PROTOCOL_GUID_3, 0i64, v35) >= 0 )
    (*(void (__fastcall **)(int *, __int64, _QWORD))(v35[0] + 8i64))(&v29, 5i64, 0i64);
  v2 = 0;
  if ( v29 == 1 )
    v2 = 32;
  v34 = 4i64;
  v3 = ((__int64 (__fastcall *)(const __int16 *, int *, _QWORD, __int64 *, int *))gRT->GetVariable)(
         L"LastModeState",
         &v7,
         0i64,
         &v34,
         &v46);
  v4 = v46;
  if ( v3 < 0 )
    v4 = 0;
  v46 = v4;
  result = v4 & 0x20;
  if ( (_DWORD)result != v2 )
  {
    v31 = v2 | v4 & 0xFFFFFFDF;
    v34 = 4i64;
    result = ((__int64 (__fastcall *)(const __int16 *, int *, __int64, __int64, unsigned int *))gRT->SetVariable)(
               L"LastModeState",
               &v7,
               7i64,
               4i64,
               &v31);
    LOBYTE(v4) = v46;
  }
  if ( v2 )
  {
    if ( (v4 & 0x20) == 0 )
    {
      v45 = 1;
      ((void (__fastcall *)(const __int16 *, int *, __int64, __int64, char *))gRT->SetVariable)(
        L"DFMMRecordFlag",
        &v18,
        3i64,
        1i64,
        &v45);
      result = ((__int64 (__fastcall *)(const __int16 *, EFI_GUID *, unsigned int *, __int64 *, _BYTE *))gRT->GetVariable)(
                 L"Setup",
                 &EFI_SETUP_VARIABLE_GUID,
                 &v32,
                 &v36,
                 v37);
      if ( result >= 0 )
      {
        v39 = 2;
        v40 = 0;
        v33 = 563i64;
        ((void (__fastcall *)(const __int16 *, EFI_GUID *, unsigned int *, __int64 *, _BYTE *))gRT->GetVariable)(// <= first call (we can rewrite DataSize here)
          L"IntelSetup",
          &EFI_SETUP_VARIABLE_GUID_0,
          &v30,
          &v33,
          v44);
        v44[108] = 1;
        ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, __int64, _BYTE *))gRT->SetVariable)(// <= second call
          L"IntelSetup",
          &EFI_SETUP_VARIABLE_GUID_0,
          v30,
          v33,
          v44);
        v6 = v38;
        if ( !v1 )
          v6 = 1;
        v38 = v6;
        v37[755] = 1;
        v37[756] = 1;
        v37[757] = 1;
        v37[758] = 1;
        v37[759] = 1;
        v37[760] = 1;
        v37[761] = 1;
        v37[762] = 1;
        v43 = 2;
        v42 = 1;
        v41 = 0;
        v37[651] = 1;
        v37[652] = 1;
        memset(&v37[655], 1, 33);
        ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, __int64, _BYTE *))gRT->SetVariable)(
          L"Setup",
          &EFI_SETUP_VARIABLE_GUID,
          v32,
          1805i64,
          v37);
        ((void (__fastcall *)(_QWORD, _QWORD, _QWORD, _QWORD))gRT->ResetSystem)(0i64, 0i64, 0i64, 0i64);
        v35[1] = 1i64;
        while ( 1 )
          ;
      }
    }
  }
  return result;
}
