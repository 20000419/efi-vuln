_BYTE *__fastcall HandleTpm12VersionInfoAndPCRBitmap(void *a1)
{
  ...
  char Value[20];
  EFI_GUID VendorGuid;
  UINTN DataSize;
  UINT32 SetupAttributes;
  UINTN SetupDataSize;
  char Buffer[128];
  char SetupValue[4787];
  UINT32 Attributes;

  DataSize = 20;
  Attributes = 0;
  SetupDataSize = 0x12B3;
  VendorGuid.Data1 = 0xEC87D643;
  *&VendorGuid.Data2 = 0x4BB5EBA4;
  *VendorGuid.Data4 = 0x3E3FE5A1;
  *&VendorGuid.Data4[4] = 0xA90DB236;
  Res = gRT->GetVariable(L"Setup", &VendorGuid, &SetupAttributes, &SetupDataSize, SetupValue);
  if ( Res >= 0 )
  {
    if ( gEfiHiiStringProtocol
      || (Res = gBS->LocateProtocol(&EFI_HII_STRING_PROTOCOL_GUID, 0, &gEfiHiiStringProtocol), Res >= 0) )
    {
      Res = sub_1073C(a1);
      if ( Res )
      {
        if ( !SetupValue[21] && !SetupValue[17] )
        {
          ...
          if (gRT->GetVariable(L"Tpm12VersionInfo", &PEI_TCG_INTERNAL_FLAGS_GUID, &Attributes, &DataSize, Value) == EFI_SUCCESS)
          {
            ...
          }
        }
        // Re-initialize DataSize before second GetVariable call
        DataSize = 20;
        Res = gRT->GetVariable(L"PCRBitmap", &PEI_TCG_INTERNAL_FLAGS_GUID, &Attributes, &DataSize, Value);
        if ( Res >= 0 )
        {
          ...
        }
      }
    }
  }
  return Res;
}
