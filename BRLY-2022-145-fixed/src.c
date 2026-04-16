__int64 __fastcall sub_BC8(EFI_CAPSULE_HEADER **a1)
{
  __int64 result; // rax
  __int64 v3; // [rsp+30h] [rbp-D0h] BYREF
  _BYTE v4[144]; // [rsp+40h] [rbp-C0h] BYREF
  _BYTE v5[688]; // [rsp+D0h] [rbp-30h] BYREF
  _BYTE v6[1072]; // [rsp+380h] [rbp+280h] BYREF
  _BYTE v7[1952]; // [rsp+7B0h] [rbp+6B0h] BYREF
  _BYTE v8[2096]; // [rsp+F50h] [rbp+E50h] BYREF
  __int64 v9; // [rsp+17A0h] [rbp+16A0h] BYREF
  __int64 v10; // [rsp+17A8h] [rbp+16A8h] BYREF

  result = ((__int64 (__fastcall *)(EFI_GUID *, _QWORD, __int64 *))gBS->LocateProtocol)(
             &AMI_TSE_SETUP_ENTER_PROTOCOL_GUID,
             0i64,
             &v3);
  if ( result >= 0 )
  {
    sub_11D84();
    v10 = 1943i64;
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, __int64 *, _BYTE *))gRT->GetVariable)(
      L"Setup",
      &EFI_SETUP_VARIABLE_GUID,
      0i64,
      &v10,
      v7);
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, __int64, _BYTE *))gRT->SetVariable)(
      L"ColdReset",
      &EFI_SETUP_VARIABLE_GUID,
      2i64,
      v10,
      v7);
    v10 = 1057i64;
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, __int64 *, _BYTE *))gRT->GetVariable)(
      L"SaSetup",
      &SA_SETUP_VARIABLE_GUID,
      0i64,
      &v10,
      v6);
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, __int64, _BYTE *))gRT->SetVariable)(
      L"SaColdReset",
      &SA_SETUP_VARIABLE_GUID,
      2i64,
      v10,
      v6);
    v10 = 143i64;
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, __int64 *, _BYTE *))gRT->GetVariable)(
      L"MeSetup",
      &ME_SETUP_VARIABLE_GUID,
      0i64,
      &v10,
      v4);
    v10 = 143i64; // Reinitialize DataSize to buffer size for MeColdReset
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, __int64, _BYTE *))gRT->SetVariable)(
      L"MeColdReset",
      &ME_SETUP_VARIABLE_GUID,
      2i64,
      v10,
      v4);
    v10 = 678i64;
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, __int64 *, _BYTE *))gRT->GetVariable)(
      L"CpuSetup",
      &CPU_SETUP_VARIABLE_GUID,
      0i64,
      &v10,
      v5);
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, __int64, _BYTE *))gRT->SetVariable)(
      L"CpuColdReset",
      &CPU_SETUP_VARIABLE_GUID,
      2i64,
      v10,
      v5);
    v10 = 2083i64;
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, __int64 *, _BYTE *))gRT->GetVariable)(
      L"PchSetup",
      &PCH_SETUP_VARIABLE_GUID,
      0i64,
      &v10,
      v8);
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, __int64, _BYTE *))gRT->SetVariable)(
      L"PchColdReset",
      &PCH_SETUP_VARIABLE_GUID,
      2i64,
      v10,
      v8);
    v10 = 2i64;
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, __int64 *, __int64 *))gRT->GetVariable)(
      L"SiSetup",
      &SI_SETUP_VARIABLE_GUID,
      0i64,
      &v10,
      &v9);
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, __int64, __int64 *))gRT->SetVariable)(
      L"SiColdReset",
      &SI_SETUP_VARIABLE_GUID,
      2i64,
      v10,
      &v9);
    return ((__int64 (__fastcall *)(EFI_CAPSULE_HEADER **))gBS->CloseEvent)(a1);
  }
  return result;
}
