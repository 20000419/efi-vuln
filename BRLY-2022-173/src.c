__int64 __fastcall sub_7CC(__int64 a1, EFI_SYSTEM_TABLE *SystemTable)
{
  __int64 v2; // rbx
  __int64 v3; // r8
  __int64 v5; // [rsp+30h] [rbp-20h] BYREF
  _DWORD v6[6]; // [rsp+38h] [rbp-18h] BYREF
  __int64 v7; // [rsp+60h] [rbp+10h] BYREF
  unsigned int v8; // [rsp+70h] [rbp+20h] BYREF
  __int64 v9; // [rsp+78h] [rbp+28h] BYREF

  v7 = a1;
  v2 = 0i64;
  v6[0] = -2117640072;
  v9 = 0i64;
  v6[1] = 1130938334;
  v6[2] = 156733591;
  v6[3] = 1696251924;
  if ( !gST_0 )
  {
    gST_0 = SystemTable;
    gBS_0 = SystemTable->BootServices;
    gRT = SystemTable->RuntimeServices;
  }
  if ( sub_8D4(a1) )
  {
    v9 = 0i64;
    (gBS_0->InstallProtocolInterface)(&v9, &AMI_SETUP_NVRAM_UPDATE_GUID, 0i64, 0i64);
    v5 = 4i64;
    if ( (gRT->GetVariable)(L"AmiHardwareSignatureSetupUpdateCountVar", v6, &v8, &v5, &v7) >= 0 )
    {
      LODWORD(v2) = v7;
      v3 = v8;
    }
    else
    {
      v3 = 7i64;
      v8 = 7;
    }
    LODWORD(v7) = v2 + 1;
    return (gRT->SetVariable)(L"AmiHardwareSignatureSetupUpdateCountVar", v6, v3, v5, &v7);
  }
  return v2;
}
