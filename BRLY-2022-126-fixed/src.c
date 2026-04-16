__int64 __fastcall sub_F9AC()
{
  char v1[304]; // [rsp+30h] [rbp-D0h] BYREF
  char v2[672]; // [rsp+160h] [rbp+60h] BYREF
  char v3[1024]; // [rsp+400h] [rbp+300h] BYREF
  char v4[1920]; // [rsp+800h] [rbp+700h] BYREF
  char Data[3600]; // [rsp+F80h] [rbp+E80h] BYREF
  char v6; // [rsp+1DA0h] [rbp+1CA0h] BYREF
  char v7; // [rsp+1DA8h] [rbp+1CA8h] BYREF
  UINTN DataSize; // [rsp+1DB0h] [rbp+1CB0h] BYREF

  DataSize = 3600i64;
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, UINTN *, char *))gRT_0->GetVariable)(
    L"Setup",
    &EFI_SETUP_VARIABLE_GUID,
    0i64,
    &DataSize,
    Data);
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, UINTN, char *))gRT_0->SetVariable)(
    L"ColdReset",
    &EFI_SETUP_VARIABLE_GUID,
    2i64,
    DataSize,
    Data);
  DataSize = 1018i64;
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, UINTN *, char *))gRT_0->GetVariable)(
    L"SaSetup",
    &SA_SETUP_VARIABLE_GUID,
    0i64,
    &DataSize,
    v3);
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, UINTN, char *))gRT_0->SetVariable)(
    L"SaColdReset",
    &SA_SETUP_VARIABLE_GUID,
    2i64,
    DataSize,
    v3);
  DataSize = 297i64;
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, UINTN *, char *))gRT_0->GetVariable)(
    L"MeSetup",
    &ME_SETUP_VARIABLE_GUID,
    0i64,
    &DataSize,
    v1);
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, UINTN, char *))gRT_0->SetVariable)(
    L"MeColdReset",
    &ME_SETUP_VARIABLE_GUID,
    2i64,
    DataSize,
    v1);
  DataSize = 667i64;
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, UINTN *, char *))gRT_0->GetVariable)(
    L"CpuSetup",
    &CPU_SETUP_VARIABLE_GUID,
    0i64,
    &DataSize,
    v2);
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, UINTN, char *))gRT_0->SetVariable)(
    L"CpuColdReset",
    &CPU_SETUP_VARIABLE_GUID,
    2i64,
    DataSize,
    v2);
  DataSize = 1919i64;
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, UINTN *, char *))gRT_0->GetVariable)(
    L"PchSetup",
    &PCH_SETUP_VARIABLE_GUID,
    0i64,
    &DataSize,
    v4);
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, UINTN, char *))gRT_0->SetVariable)(
    L"PchColdReset",
    &PCH_SETUP_VARIABLE_GUID,
    2i64,
    DataSize,
    v4);
  DataSize = 7i64;
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, UINTN *, char *))gRT_0->GetVariable)(
    L"SiSetup",
    &SI_SETUP_VARIABLE_GUID,
    0i64,
    &DataSize,
    &v7);
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, UINTN, char *))gRT_0->SetVariable)(
    L"SiColdReset",
    &SI_SETUP_VARIABLE_GUID,
    2i64,
    DataSize,
    &v7);
  DataSize = 4i64;
  ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, UINTN *, char *))gRT_0->GetVariable)(
    L"AmiWrapperSetup",
    &stru_22D78,
    0i64,
    &DataSize,
    &v6);
  DataSize = 4i64; // Re-initialize DataSize with correct buffer size
  return ((__int64 (__fastcall *)(const __int16 *, EFI_GUID *, __int64, UINTN, char *))gRT_0->SetVariable)(
           L"AmiWrapperColdReset",
           &stru_22D78,
           2i64,
           DataSize,
           &v6);
}
