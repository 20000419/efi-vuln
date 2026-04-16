unsigned __int8 __fastcall sub_742C(_DWORD *a1)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS NUMPAD "+" TO EXPAND]

  Guid.Data2 = 0x5A0;
  Guid.Data1 = 0xA602C5B;
  Guid.Data4[0] = 0x91;
  Guid.Data4[1] = 0x81;
  Guid.Data4[2] = 0xED;
  Guid.Data3 = 0x40C4;
  Guid.Data4[3] = 0xCD;
  Guid.Data4[4] = 0x89;
  Guid.Data4[5] = 0x1D;
  Guid.Data4[6] = 0;
  Guid.Data4[7] = 3;
  if ( !gDellGnvsPtr )
  {
    DataSize = 4;
    gRT_0->GetVariable(L"DELL_GNVS_PTR", &Guid, 0, &DataSize, &gDellGnvsPtr);
  }
  a1[6] = 0;
  a1[8] = 0;
  sub_5F58();
  __outbyte(0x380, 0x83);
  v3 = 897LL;
  v4 = __inbyte(0x381);
  if ( (v4 & 2) != 0 )
  {
    // ...
    *(gDellGnvsPtr + 4144) = 2;                 // unchecked write (SMRAM corruption)
  }
  else
  {
    sub_7334(a1);
    *(gDellGnvsPtr + 4144) = 1;                 // unchecked write (SMRAM corruption)
  }
  sub_5F58();
  __outbyte(0x380, 0x83);
  v8 = __inbyte(0x381);
  v9 = 65;
  if ( (v8 & 3) == 0 )
    v9 = 45;
  *(gDellGnvsPtr + 4146) = v9;                  // unchecked write (SMRAM corruption)
  sub_5F58();
  __outbyte(0x380, 0x83);
  v10 = 897;
  v11 = __inbyte(0x381);
  result = v11 & 3;
  if ( result )
    v13 = (result - 1) <= 2;
  else
    v13 = 0;
  v14 = gDellGnvsPtr;
  *(gDellGnvsPtr + 4145) = v13;                 // unchecked write (SMRAM corruption)
  v15 = (gDellGnvsPtr + 4144);
  if ( gDellGnvsPtr != -4144 )
  {
    LOBYTE(v10) = 2;
    LOBYTE(v14) = -82;
    sub_5F94(v14, v10);
    __outbyte(0x380, 0x83);
    result = __inbyte(0x381);
    if ( result == 1 )
    {
      *v15 = 1;
    }
    else if ( result == 2 )
    {
      *v15 = 2;
    }
  }
  a1[5] = 0;
  return result;
}
