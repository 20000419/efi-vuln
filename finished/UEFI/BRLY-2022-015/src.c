__int64 sub_16520()
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  GetPackageListHandle = gEsaVarPtr01;
  Arg2 = 0;
  Guid[0] = 0x70E1A818;
  Guid[1] = 0x44490BE1;
  Guid[2] = 0xF69ED4BF;
  Guid[3] = 0xA8027F8C;
  VendorGuid.Data1 = 0xA2DF5376;
  *&VendorGuid.Data2 = 0x49C0C2ED;
  *VendorGuid.Data4 = 0x178BFF90;
  *&VendorGuid.Data4[4] = 0x66D00F3B;
  if ( gEsaVarPtr01
    || (DataSize = 8,
        gRT->GetVariable(L"EsaVarPtr01", &VendorGuid, 0, &DataSize, &gEsaVarPtr01),
        (GetPackageListHandle = gEsaVarPtr01) != 0) )
  {
    Handle = GetPackageListHandle(Guid, &Arg2);
  }
  else
  {
    Handle = -1;
  }
  if ( Handle != -1 )
    return gEfiHiiDatabaseProtocol->RemovePackageList(gEfiHiiDatabaseProtocol, Handle);
  return Handle;
}
