__int64 __fastcall sub_D1F(__int64 a1, EFI_GUID *a2, EFI_GUID *VendorGuid, _QWORD *a4)
{
  __int64 v4; // rax
  __int64 v5; // rbp
  __int64 v6; // r9
  __int64 v7; // r8
  EFI_RUNTIME_SERVICES *v8; // rax
  __int64 v9; // r9
  __int64 v10; // r8
  EFI_RUNTIME_SERVICES *v11; // rax
  _DWORD v13[4]; // [rsp-BC8h] [rbp-BC8h] BYREF
  _DWORD v14[750]; // [rsp-BB8h] [rbp-BB8h] BYREF

  sub_11E8((__int64)&EFI_ODMEM_GNVS_AREA_PROTOCOL_GUID, (__int64)sub_554, (__int64)VendorGuid, a4, v4);
  v14[0] = -1332766721;
  v14[1] = 1100211944;
  v14[2] = -1637967959;
  v14[3] = 853215899;
  v13[0] = 1165015025;
  v13[1] = 1229172200;
  v13[2] = 1681965965;
  v13[3] = -2078047118;
  sub_1330((int *)(v5 + 752), 0, 0x7ECui64);
  *(_QWORD *)(v5 + 2840) = 845i64;
  ((void (__fastcall *)(const __int16 *, _DWORD *, __int64, __int64, __int64))gRT->GetVariable)(
    L"CpuSetup",
    v14,
    v5 + 2816,
    v5 + 2840,
    v5 - 96);
  v6 = *(_QWORD *)(v5 + 2840);
  v7 = *(unsigned int *)(v5 + 2816);
  v8 = gRT;
  *(_WORD *)(v5 + 125) = 256;
  ((void (__fastcall *)(const __int16 *, _DWORD *, __int64, __int64, __int64))v8->SetVariable)(
    L"CpuSetup",
    v14,
    v7,
    845i64, // Reinitialize DataSize to correct value (845)
    v5 - 96);
  *(_QWORD *)(v5 + 2840) = 2028i64;
  ((void (__fastcall *)(const __int16 *, _DWORD *, __int64, __int64, __int64))gRT->GetVariable)(
    L"PchSetup",
    v13,
    v5 + 2816,
    v5 + 2840,
    v5 + 752);
  v9 = *(_QWORD *)(v5 + 2840);
  v10 = *(unsigned int *)(v5 + 2816);
  v11 = gRT;
  *(_BYTE *)(v5 + 2471) = 0;
  *(_BYTE *)(v5 + 762) = 0;
  *(_BYTE *)(v5 + 2512) = 0;
  ((void (__fastcall *)(const __int16 *, _DWORD *, __int64, __int64, __int64))v11->SetVariable)(
    L"PchSetup",
    v13,
    v10,
    v9,
    v5 + 752);
  return 0i64;
}
