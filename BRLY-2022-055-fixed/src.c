__int64 __fastcall sub_A68(void *a1)
{
  __int64 v1; // rbx
  __int64 result; // rax
  __int64 v3; // rax
  char v4; // cl
  __int64 v5; // rax
  char v6; // cl
  __int64 v7; // rax
  void *v8; // rcx
  char v9; // cl
  char v10[4]; // [rsp+30h] [rbp-848h] BYREF
  unsigned int v11; // [rsp+34h] [rbp-844h] BYREF
  int v12; // [rsp+38h] [rbp-840h] BYREF
  __int16 v13; // [rsp+3Ch] [rbp-83Ch]
  __int16 v14; // [rsp+3Eh] [rbp-83Ah]
  char v15; // [rsp+40h] [rbp-838h]
  char v16; // [rsp+41h] [rbp-837h]
  char v17; // [rsp+42h] [rbp-836h]
  char v18; // [rsp+43h] [rbp-835h]
  char v19; // [rsp+44h] [rbp-834h]
  char v20; // [rsp+45h] [rbp-833h]
  char v21; // [rsp+46h] [rbp-832h]
  char v22; // [rsp+47h] [rbp-831h]
  __int64 v23; // [rsp+48h] [rbp-830h] BYREF
  __int64 v24; // [rsp+50h] [rbp-828h] BYREF
  _QWORD v25[2]; // [rsp+58h] [rbp-820h] BYREF
  __int64 v26; // [rsp+68h] [rbp-810h] BYREF
  _BYTE v27[7]; // [rsp+70h] [rbp-808h] BYREF
  char v28; // [rsp+77h] [rbp-801h]
  char v29; // [rsp+78h] [rbp-800h]
  char v30; // [rsp+79h] [rbp-7FFh]
  char v31; // [rsp+7Ah] [rbp-7FEh]
  char v32; // [rsp+7Bh] [rbp-7FDh]
  char v33; // [rsp+7Ch] [rbp-7FCh]
  char v34; // [rsp+7Dh] [rbp-7FBh]
  char v35; // [rsp+7Eh] [rbp-7FAh]
  char v36; // [rsp+7Fh] [rbp-7F9h]
  char v37; // [rsp+80h] [rbp-7F8h]
  char v38; // [rsp+81h] [rbp-7F7h]
  char v39; // [rsp+82h] [rbp-7F6h]
  char v40; // [rsp+83h] [rbp-7F5h]
  char v41; // [rsp+85h] [rbp-7F3h]
  char v42; // [rsp+86h] [rbp-7F2h]
  char v43; // [rsp+87h] [rbp-7F1h]
  char v44; // [rsp+88h] [rbp-7F0h]
  char v45; // [rsp+89h] [rbp-7EFh]
  char v46; // [rsp+8Ah] [rbp-7EEh]
  char v47; // [rsp+35Bh] [rbp-51Dh]
  char v48; // [rsp+35Dh] [rbp-51Bh]
  char v49; // [rsp+45Ch] [rbp-41Ch]
  void *v50; // [rsp+880h] [rbp+8h] BYREF
  char v51; // [rsp+890h] [rbp+18h] BYREF
  char v52; // [rsp+898h] [rbp+20h] BYREF

  v50 = a1;
  v13 = -5212;
  v14 = 19381;
  v12 = -326642109;
  v15 = -95;
  v16 = -27;
  v17 = 63;
  v18 = 62;
  v19 = 54;
  v20 = -78;
  v21 = 13;
  v22 = -87;
  v51 = 0;
  v24 = 1i64; // Initialize DataSize for first variable
  v25[0] = 0i64;
  v10[0] = 0;
  v26 = 1i64;
  v23 = 2029i64;
  v1 = ((__int64 (__fastcall *)(__int64, __int64, __int64 *))gBS->AllocatePool)(4i64, 40i64, &qword_1230);
  sub_1120(&byte_1210, 0x1Bui64, 0);
  if ( v1 < 0 )
    return 0x8000000000000009ui64;
  if ( ((__int64 (__fastcall *)(EFI_GUID *, _QWORD, _QWORD *))gBS->LocateProtocol)(
         &DELL_PROPERTY_DXE_PROTOCOL_GUID,
         0i64,
         v25) >= 0 )
    (*(void (__fastcall **)(_QWORD, __int64, __int64 *, __int64 *, char *))v25[0])(
      v25[0],
      9346i64,
      qword_240,
      &v26,
      v10);
  v3 = ((__int64 (__fastcall *)(const __int16 *, EFI_GUID *, unsigned int *, __int64 *, char *))gRT->GetVariable)(
         L"InternalDisallowTpmFlag",
         &PEI_TCG_INTERNAL_FLAGS_GUID,
         &v11,
         &v24,
         &v51);
  v4 = v51;
  if ( v3 < 0 )
    v4 = 0;
  v51 = v4;
  
  v24 = 1i64; // Re-initialize DataSize to correct value (1 byte) for second variable
  v5 = ((__int64 (__fastcall *)(const __int16 *, EFI_GUID *, unsigned int *, __int64 *, char *))gRT->GetVariable)(
         L"TcgInternalSyncFlag",
         &TCG_PPI_SYNC_FLAG_GUID,
         &v11,
         &v24,
         &v52);
  v6 = v52;
  if ( v5 < 0 )
    v6 = 0;
  v52 = v6;
  v7 = ((__int64 (__fastcall *)(const __int16 *, int *, unsigned int *, __int64 *, _BYTE *))gRT->GetVariable)(
         L"Setup",
         &v12,
         &v11,
         &v23,
         v27);
  *(_BYTE *)qword_1230 = 2;
  v8 = (void *)(qword_1230 + 1);
  if ( v7 >= 0 )
  {
    sub_1120(v8, 0x1Bui64, 0);
    *(_BYTE *)(qword_1230 + 1) = v33;
    if ( !v33 && !sub_3EC() )
    {
      v28 = 0;
      ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, _QWORD, _QWORD))gRT->SetVariable)(
        L"TpmOldvar",
        &TC_EFI_GLOBAL_VARIABLE_GUID,
        0i64,
        0i64,
        0i64);
    }
    *(_BYTE *)(qword_1230 + 2) = v35;
    *(_BYTE *)(qword_1230 + 3) = v28;
    *(_BYTE *)(qword_1230 + 4) = v38;
    if ( v47 || (v9 = v29) != 0 )
    {
      v9 = sub_3EC() ? 1 : 5;
      v29 = v9;
    }
    *(_BYTE *)(qword_1230 + 5) = v9;
    *(_BYTE *)(qword_1230 + 19) = v52;
    if ( v41 )
      *(_DWORD *)(qword_1230 + 7) = 2;
    else
      *(_DWORD *)(qword_1230 + 7) = 1;
    *(_BYTE *)(qword_1230 + 11) = v46;
    *(_BYTE *)(qword_1230 + 6) = v51;
    *(_BYTE *)(qword_1230 + 12) = 1;
    *(_BYTE *)(qword_1230 + 13) = v30;
    *(_BYTE *)(qword_1230 + 14) = v31;
    *(_BYTE *)(qword_1230 + 15) = v32;
    *(_BYTE *)(qword_1230 + 16) = 0;
    *(_BYTE *)(qword_1230 + 17) = 0;
    *(_BYTE *)(qword_1230 + 18) = v40;
    *(_BYTE *)(qword_1230 + 20) = 0;
    *(_BYTE *)(qword_1230 + 21) = 0;
    *(_BYTE *)(qword_1230 + 22) = 0;
    *(_BYTE *)(qword_1230 + 23) = 0;
    *(_BYTE *)(qword_1230 + 26) = v44;
    *(_BYTE *)(qword_1230 + 25) = v43;
    *(_BYTE *)(qword_1230 + 24) = v42;
    *(_BYTE *)(qword_1230 + 27) = v45;
  }
  else
  {
    sub_1120(v8, 0x1Bui64, 0);
  }
  if ( v10[0] )
  {
    *(_BYTE *)qword_1230 = 2;
    *(_QWORD *)(qword_1230 + 32) = sub_544;
    ((void (__fastcall *)(const __int16 *, int *, unsigned int *, __int64 *, _BYTE *))gRT->GetVariable)(
      L"Setup",
      &v12,
      &v11,
      &v23,
      v27);
    v39 = v51;
    v28 = 0;
    v33 = 0;
    v35 = 0;
    v38 = 0;
    v29 = 0;
    v30 = 0;
    v31 = 0;
    v37 = 0;
    v32 = 0;
    v40 = 0;
    v34 = 0;
    v36 = 0;
    v49 = 0;
    v48 = 0;
    return ((__int64 (__fastcall *)(const __int16 *, int *, _QWORD, __int64, _BYTE *))gRT->SetVariable)(
             L"Setup",
             &v12,
             v11,
             v23,
             v27);
  }
  else
  {
    if ( MEMORY[0xFED40000] == 0xFF )
      goto LABEL_28;
    if ( !v48 )
    {
      v48 = 1;
      ((void (__fastcall *)(const __int16 *, int *, _QWORD, __int64, _BYTE *))gRT->SetVariable)(
        L"Setup",
        &v12,
        v11,
        v23,
        v27);
    }
    if ( MEMORY[0xFED40000] == 0xFF )
    {
LABEL_28:
      if ( v49 || v48 )
      {
        v49 = 0;
        v48 = 0;
        ((void (__fastcall *)(const __int16 *, int *, _QWORD, __int64, _BYTE *))gRT->SetVariable)(
          L"Setup",
          &v12,
          v11,
          v23,
          v27);
      }
    }
    *(_QWORD *)(qword_1230 + 32) = sub_544;
    byte_1210 = *(_BYTE *)(qword_1230 + 1);
    byte_1211 = *(_BYTE *)(qword_1230 + 2);
    byte_1212 = *(_BYTE *)(qword_1230 + 3);
    byte_1213 = *(_BYTE *)(qword_1230 + 4);
    byte_1214 = *(_BYTE *)(qword_1230 + 5);
    dword_1216 = *(_DWORD *)(qword_1230 + 7);
    byte_121A = *(_BYTE *)(qword_1230 + 11);
    byte_121B = *(_BYTE *)(qword_1230 + 12);
    byte_121C = *(_BYTE *)(qword_1230 + 13);
    byte_121D = *(_BYTE *)(qword_1230 + 14);
    byte_121E = *(_BYTE *)(qword_1230 + 15);
    byte_121F = *(_BYTE *)(qword_1230 + 16);
    byte_1220 = *(_BYTE *)(qword_1230 + 17);
    byte_1221 = *(_BYTE *)(qword_1230 + 18);
    byte_1222 = *(_BYTE *)(qword_1230 + 19);
    byte_1223 = *(_BYTE *)(qword_1230 + 20);
    byte_1224 = *(_BYTE *)(qword_1230 + 21);
    byte_1225 = *(_BYTE *)(qword_1230 + 22);
    byte_1226 = *(_BYTE *)(qword_1230 + 23);
    byte_1229 = *(_BYTE *)(qword_1230 + 26);
    byte_1228 = *(_BYTE *)(qword_1230 + 25);
    byte_1227 = *(_BYTE *)(qword_1230 + 24);
    byte_122A = *(_BYTE *)(qword_1230 + 27);
    gBS->InstallMultipleProtocolInterfaces(&v50, &TCG_PLATFORM_SETUP_POLICY_GUID, qword_1230, 0i64);
    gImageHandle = v50;
    result = ((__int64 (__fastcall *)(__int64, __int64, void (__fastcall *)(EFI_EVENT, void *)))gBS->CreateEvent)(
               512i64,
               8i64,
               NotifyFunction);
    if ( result >= 0 )
      return ((__int64 (__fastcall *)(EFI_GUID *, _QWORD, void **))gBS->RegisterProtocolNotify)(
               &BDS_ALL_DRIVERS_CONNECTED_PROTOCOL_GUID,
               v25[1],
               &Registration);
  }
  return result;
}
