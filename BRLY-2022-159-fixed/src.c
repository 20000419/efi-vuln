EFI_STATUS __fastcall sub_8AC()
{
  EFI_GUID VendorGuid; // [rsp+30h] [rbp-D0h] BYREF
  EFI_GUID v2; // [rsp+40h] [rbp-C0h] BYREF
  EFI_GUID v3; // [rsp+50h] [rbp-B0h] BYREF
  char Data[226]; // [rsp+60h] [rbp-A0h] BYREF
  __int16 v5; // [rsp+142h] [rbp+42h]
  int v6[2]; // [rsp+300h] [rbp+200h] BYREF
  char v7; // [rsp+30Ah] [rbp+20Ah]
  char v8; // [rsp+930h] [rbp+830h]
  UINT32 Attributes; // [rsp+A90h] [rbp+990h] BYREF
  char v10; // [rsp+A98h] [rbp+998h] BYREF
  int v11; // [rsp+A99h] [rbp+999h]
  __int16 v12; // [rsp+A9Dh] [rbp+99Dh]
  UINTN DataSize; // [rsp+AA0h] [rbp+9A0h] BYREF

  VendorGuid.Data1 = -1332766721;
  *&VendorGuid.Data2 = 1100211944;
  *VendorGuid.Data4 = -1637967959;
  *&VendorGuid.Data4[4] = 853215899;
  v2.Data1 = 1165015025;
  *&v2.Data2 = 1229172200;
  *v2.Data4 = 1681965965;
  *&v2.Data4[4] = -2078047118;
  v3.Data1 = -1426528487;
  *&v3.Data2 = 1083787512;
  *v3.Data4 = 1600452518;
  *&v3.Data4[4] = 1028417981;
  sub_1130(v6, 0, 0x77Fui64);
  v10 = 0;
  v11 = 0;
  v12 = 0;
  DataSize = 667i64;
  gRT->GetVariable(L"CpuSetup", &VendorGuid, &Attributes, &DataSize, Data);
  v5 = 256;
  gRT->SetVariable(L"CpuSetup", &VendorGuid, Attributes, DataSize, Data);
  DataSize = 1919i64;
  gRT->GetVariable(L"PchSetup", &v2, &Attributes, &DataSize, v6);
  v8 = 0;
  v7 = 0;
  gRT->SetVariable(L"PchSetup", &v2, Attributes, DataSize, v6);
  DataSize = 7i64;
  gRT->GetVariable(L"SiSetup", &v3, &Attributes, &DataSize, &v10);
  LOBYTE(v11) = 0;
  DataSize = 7i64; // Reinitialize DataSize to correct value (7)
  return gRT->SetVariable(L"SiSetup", &v3, Attributes, DataSize, &v10);
}
