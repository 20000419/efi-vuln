void sub_27C0()
{
  int v0; // eax
  __int64 v1; // rax
  int v2[4]; // [rsp+30h] [rbp-10h] BYREF
  char v3; // [rsp+50h] [rbp+10h] BYREF
  char v4; // [rsp+58h] [rbp+18h] BYREF
  __int64 v5; // [rsp+60h] [rbp+20h] BYREF

  sub_4C6C(1024i64, "  CcxCheckDownCoreStatus Entry\n");
  v2[0] = 41014;
  v0 = sub_5974(v2);
  v3 = 0;
  v5 = 1i64;
  v4 = v0 == 0;
  v1 = (gRT->GetVariable)(
         L"DownCoreStatus",
         &VendorGuid,
         0i64,
         &v5,
         &v3);
  if ( v4 != v3 || v1 )
  {
    v5 = 1i64; // Reinitialize DataSize to correct value (1)
    (gRT->SetVariable)(
      L"DownCoreStatus",
      &VendorGuid,
      7i64,
      v5,
      &v4);
    if ( v3 && !v4 )
    {
      sub_4C6C(1024i64, aDowncoredAutoI);
      (gRT->ResetSystem)(0i64, 0i64, 0i64, 0i64);
    }
  }
  sub_4C6C(1024i64, aCcxcheckdownco_0);
}
