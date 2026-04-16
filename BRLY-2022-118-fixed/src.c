__int64 __fastcall sub_6EB8(__int64 a1, char a2)
{
  __int64 v5; // [rsp+30h] [rbp-28h] BYREF
  __int16 v6; // [rsp+38h] [rbp-20h]
  int v7; // [rsp+40h] [rbp-18h] BYREF
  __int16 v8; // [rsp+44h] [rbp-14h]
  __int16 v9; // [rsp+46h] [rbp-12h]
  char v10; // [rsp+48h] [rbp-10h]
  char v11; // [rsp+49h] [rbp-Fh]
  char v12; // [rsp+4Ah] [rbp-Eh]
  char v13; // [rsp+4Bh] [rbp-Dh]
  char v14; // [rsp+4Ch] [rbp-Ch]
  char v15; // [rsp+4Dh] [rbp-Bh]
  char v16; // [rsp+4Eh] [rbp-Ah]
  char v17; // [rsp+4Fh] [rbp-9h]
  __int64 v18; // [rsp+60h] [rbp+8h] BYREF
  unsigned int v19; // [rsp+68h] [rbp+10h] BYREF

  v5 = 0i64;
  v6 = 0;
  v8 = -4810;
  v9 = 18896;
  v7 = 2039750349;
  v10 = -127;
  v11 = 36;
  v12 = -28;
  v13 = -61;
  v14 = 26;
  v15 = -57;
  v16 = 92;
  v17 = -44;
  v18 = 10i64;
  v19 = 6;
  ((void (__fastcall *)(const __int16 *, int *, unsigned int *, __int64 *, __int64 *))gRT->GetVariable)(
    L"AmdAcpiVar",
    &v7,
    &v19,
    &v18,
    &v5);
  v5 = a1;
  if ( a2 )
    v6 = 1;
  else
    ++v6;
  UINTN correctDataSize = 10; // Re-initialize DataSize with actual buffer size
  return ((__int64 (__fastcall *)(const __int16 *, int *, _QWORD, __int64, __int64 *))gRT->SetVariable)(
           L"AmdAcpiVar",
           &v7,
           v19,
           correctDataSize,
           &v5);
}
