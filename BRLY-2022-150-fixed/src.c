void __fastcall sub_2A5C(EFI_EVENT Event, void *Context)
{
  unsigned __int64 v2; // rbx
  int v3; // edi
  int v4; // esi
  __int64 v5; // rcx
  int v6; // r8d
  unsigned int v7; // ecx
  __int64 v8; // rax
  char v9; // cl
  int v10; // [rsp+30h] [rbp-20h] BYREF
  __int64 v11; // [rsp+38h] [rbp-18h] BYREF
  __int64 v12; // [rsp+40h] [rbp-10h] BYREF
  void (__fastcall **v13)(_QWORD, __int64, void *, __int64 *, __int64 *); // [rsp+48h] [rbp-8h] BYREF
  char v14; // [rsp+90h] [rbp+40h] BYREF
  __int64 v15; // [rsp+98h] [rbp+48h] BYREF

  v10 = 0;
  v2 = *(unsigned int *)(sub_2A2C() + 12);
  v3 = -1;
  v14 = 0;
  v4 = 0;
  v11 = 1i64;
  ((void (__fastcall *)(EFI_GUID *, _QWORD, void (__fastcall ***)(_QWORD, __int64, void *, __int64 *, __int64 *)))gBS->LocateProtocol)(
    &DELL_PROPERTY_DXE_PROTOCOL_GUID,
    0i64,
    &v13);
  v12 = 1i64;
  (*v13)(v13, 3610i64, &unk_4140, &v12, &v15);
  if ( !(_BYTE)v15 )
    goto LABEL_20;
  if ( (unsigned int)v2 <= 0x20 )
  {
    v5 = 0x100040010i64;
    if ( _bittest64(&v5, v2) )
      goto LABEL_20;
  }
  sub_3C58(v5, 293613704, v6, &v10);
  if ( MEMORY[0xE001A000] != -1 && (unsigned __int8)(MEMORY[0xE001A019] - 1) <= 0xFDu )
  {
    v7 = MEMORY[0xE001A019] << 20;
    v3 = *(_DWORD *)(v7 + 0xE0000000i64);
    if ( v3 != -1 )
      v4 = *(_DWORD *)(v7 + 48 + 0xE0000000i64);
  }
  if ( (v10 & 0xF) != 1 && MEMORY[0xE001A000] != -1 && v3 != -1 && v4 )
  {
    v14 = 0;
    v11 = 1; // Reinitialize DataSize to the correct size
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, __int64, char *))gRT->SetVariable)(
      L"RebootCounter10GLom",
      &VendorGuid,
      7i64,
      v11,
      &v14);
    goto LABEL_20;
  }
  v8 = ((__int64 (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, __int64 *, char *))gRT->GetVariable)(
         L"RebootCounter10GLom",
         &VendorGuid,
         0i64,
         &v11,
         &v14);
  if ( v8 >= 0 )
  {
    v9 = v14;
  }
  else
  {
    v9 = v14;
    if ( v8 == 0x800000000000000Eui64 )
      v9 = 0;
  }
  if ( (unsigned __int8)v9 >= 5u )
LABEL_20:
    JUMPOUT(0x2C24i64);
  sub_2BE9(v9 + 1);
}
