__int64 sub_B70()
{
  char v0; // bp
  char v1; // r13
  char v2; // r12
  __int64 v3; // rax
  __int64 result; // rax
  char v5; // r9
  unsigned __int8 v6; // bl
  unsigned __int8 v7; // cl
  char v8; // dl
  int v9; // ebx
  int v10; // ecx
  char v11; // dl
  char v12; // cl
  unsigned __int8 v13; // cl
  int v14; // esi
  int *v15; // rbx
  int v16; // edi
  char v17; // al
  __int64 v18; // rbx
  _BYTE v19[4]; // [rsp+30h] [rbp-19D8h]
  unsigned int v20; // [rsp+34h] [rbp-19D4h] BYREF
  char v21[4]; // [rsp+38h] [rbp-19D0h] BYREF
  unsigned int v22; // [rsp+3Ch] [rbp-19CCh] BYREF
  __int64 v23; // [rsp+40h] [rbp-19C8h] BYREF
  __int64 v24; // [rsp+48h] [rbp-19C0h] BYREF
  __int64 v25; // [rsp+50h] [rbp-19B8h] BYREF
  __int64 v26; // [rsp+58h] [rbp-19B0h] BYREF
  _QWORD v27[2]; // [rsp+60h] [rbp-19A8h] BYREF
  __int64 v28; // [rsp+70h] [rbp-1998h] BYREF
  EFI_EVENT v29; // [rsp+78h] [rbp-1990h] BYREF
  _BYTE v30[6536]; // [rsp+80h] [rbp-1988h] BYREF
  int *v31; // [rsp+1A20h] [rbp+18h] BYREF
  char v32; // [rsp+1A28h] [rbp+20h] BYREF

  v23 = 0xFFFFFFFFi64;
  v20 = 0;
  v25 = 0i64;
  v0 = 0;
  v1 = 0;
  v2 = 0;
  v24 = 6475i64;
  (gBS->AllocatePages)(1i64, 10i64, 1i64, &v23);
  qword_80D0 = v23;
  (gBS->SetMem)(v23, 29i64, 0i64);
  gUnknownProtocol = qword_80D0;
  (gBS->InstallProtocolInterface)(&v25, &UNKNOWN_PROTOCOL_GUID, 0i64, &gUnknownProtocol);
  if ( gST->Hdr.Revision >= 0x20000 )
    sub_1F50(&v29);
  if ( (sub_1EE8(&TCG_EFI_HOB_LIST_GUID, &qword_87F8) & 0x8000000000000000ui64) != 0i64 )
    return 0x800000000000000Eui64;
  v3 = qword_87F8;
  if ( !qword_87F8 )
    return 0x800000000000000Eui64;
  while ( 1 )
  {
    if ( *v3 == 0xFFFF )
    {
      v3 = 0i64;
    }
    else if ( *v3 != 4 )
    {
      goto LABEL_7;
    }
    if ( !v3 || *&ITBT_INFO_HOB_GUID.Data1 == *(v3 + 8) && *ITBT_INFO_HOB_GUID.Data4 == *(v3 + 16) )
      break;
LABEL_7:
    v3 += *(v3 + 2);
  }
  qword_87F8 = v3;
  if ( !v3 )
    return 0x800000000000000Eui64;
  v28 = 1805i64;
  result = (gRT->GetVariable)(L"Setup", &EFI_SETUP_VARIABLE_GUID_1, &v20, &v28, &unk_80E0);
  if ( result >= 0 )
  {
    (gBS->CreateEvent)(&VariableNameSize, 16i64, sub_A40);
    (gBS->RegisterProtocolNotify)(&UNKNOWN_PROTOCOL_GUID_0, v27[1], &Registration);
    sub_490();
    v5 = byte_8171;
    if ( byte_8171 == -1 )
    {
      v19[0] = 9;
      v19[1] = 22;
      v19[2] = 26;
      v6 = 0;
      while ( 1 )
      {
        v7 = v19[v6];
        if ( v7 )
        {
          if ( sub_1CD8(v7, v21, &v32, &v31) >= 0 )
            break;
        }
        if ( ++v6 >= 3u )
        {
          byte_8171 = 0;
          byte_87F3 = 0;
          sub_9FC(&byte_87F0, 0);
          break;
        }
      }
      v5 = byte_8171;
    }
    v8 = byte_5901;
    if ( byte_87F2 != *(qword_87F8 + 56) )
      v8 = 1;
    byte_5901 = v8;
    if ( !byte_5900 )
      goto LABEL_35;
    if ( !v5 )
      goto LABEL_35;
    byte_5901 = 1;
    if ( v5 != -1 && sub_3AB4(v5, 1, 1) < 0 )
      goto LABEL_35;
    v26 = 1805i64;
    result = (gRT->GetVariable)(L"Setup", &EFI_SETUP_VARIABLE_GUID_1, &v20, &v26, &unk_80E0);
    if ( result >= 0 )
    {
      if ( byte_8171 == -1 )
      {
        if ( sub_9FC(&byte_87F0, 2) >= 0 )
        {
          byte_5901 = 0;
          goto LABEL_34;
        }
      }
      else if ( !sub_964(*(qword_87F8 + 53), *(qword_87F8 + 54), *(qword_87F8 + 55)) )
      {
LABEL_34:
        v2 = 1;
        v0 = 1;
      }
LABEL_35:
      v9 = dword_87F4;
      if ( dword_87F4 < 2 )
        goto LABEL_65;
      if ( byte_5900 )
        goto LABEL_65;
      v10 = *(sub_2024() + 12);
      if ( v10 == 16 || v10 == 17 || v10 == 5 || v10 == 18 || v10 == 32 )
        goto LABEL_65;
      if ( v9 == 2 )
      {
        sub_758(1, qword_87F8);
        v11 = *(qword_87F8 + 52);
        if ( v11 && sub_24C4(255, v11) >= 0 )
        {
          v12 = *(qword_87F8 + 52);
          byte_5901 = 1;
          byte_87F3 = v12;
          sub_9FC(&byte_87F0, 3);
          goto LABEL_52;
        }
      }
      else if ( v9 == 3 )
      {
        sub_758(0, qword_87F8);
        if ( *(qword_87F8 + 52) != byte_87F3 )
        {
          dword_87F4 = 1;
          if ( byte_87F3 == -1 || !byte_87F3 || sub_3AB4(byte_87F3, 0, 0) >= 0 )
          {
            byte_87F3 = 0;
            sub_9FC(&byte_87F0, 2);
            v2 = 1;
LABEL_52:
            v0 = 1;
          }
        }
      }
      if ( !v0
        || (v27[0] = 1805i64,
            result = (gRT->GetVariable)(L"Setup", &EFI_SETUP_VARIABLE_GUID_1, &v20, v27, &unk_80E0),
            result >= 0) )
      {
        if ( !byte_5901 )
          goto LABEL_67;
        if ( !*(qword_87F8 + 52) )
          goto LABEL_67;
        v13 = *(qword_87F8 + 53);
        if ( !v13 && !*(qword_87F8 + 54) && !*(qword_87F8 + 55) )
          goto LABEL_67;
LABEL_65:
        LOBYTE(v14) = *(sub_1F98(v13, *(qword_87F8 + 54), *(qword_87F8 + 55)) + 25);
        if ( v14 )
        {
          v15 = v31;
          v16 = v31;
        }
        else
        {
          v14 = sub_12E0(*(qword_87F8 + 53));
          v15 = (sub_1F98(*(qword_87F8 + 53), *(qword_87F8 + 54), *(qword_87F8 + 55)) + 24);
          v16 = *v15;
          v1 = 1;
          *v15 = *(qword_87F8 + 53) + 65792 * v14;
        }
        sub_1498(*(qword_87F8 + 53), *(qword_87F8 + 54), *(qword_87F8 + 55));
        v17 = sub_1968(
                *(qword_87F8 + 56),
                v14,
                *(qword_87F8 + 49),
                *(qword_87F8 + 25),
                *(qword_87F8 + 29),
                *(qword_87F8 + 50));
        if ( v1 )
          *v15 = v16;
        if ( v17 != -1 )
        {
          byte_87F2 = v17;
          (gRT->SetVariable)(L"TbtHRStatusVar", &VendorGuid, 7i64, DataSize, &byte_87F0);
        }
        else
        {
LABEL_67:
          *(qword_87F8 + 56) = byte_87F2;
          byte_8169 = byte_87F2;
        }
        if ( byte_8158 == 1 && byte_8160 == 2 && byte_87F3 && *(qword_87F8 + 58) == 1 && *(qword_87F8 + 70) < 8u )
        {
          byte_8178 = 8;
          *(qword_87F8 + 70) = 8;
        }
        if ( byte_841F )
        {
          byte_812D = 1;
          (gRT->GetVariable)(
            L"SocketIioConfig",
            &EFI_SOCKET_IIO_VARIABLE_GUID,
            &v22,
            &v24,
            v30);
          v30[4024] = 1;
          v24 = 6475i64; // Reinitialize DataSize to correct value (6475)
          (gRT->SetVariable)(
            L"SocketIioConfig",
            &EFI_SOCKET_IIO_VARIABLE_GUID,
            v22,
            v24,
            v30);
        }
        v18 = (gRT->SetVariable)(L"Setup", &EFI_SETUP_VARIABLE_GUID_1, v20, 1805i64, &unk_80E0);
        if ( v0 )
        {
          __outbyte(0xCF9u, v2 != 0 ? 14 : 6);
          while ( 1 )
            ;
        }
        if ( *(qword_87F8 + 52) && !sub_964(*(qword_87F8 + 53), *(qword_87F8 + 54), *(qword_87F8 + 55)) )
          *(qword_87F8 + 52) = 0;
        return v18;
      }
    }
  }
  return result;
}
