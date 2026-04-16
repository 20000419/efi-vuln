char __fastcall sub_6B8(unsigned int a1)
{
  unsigned int v2; // ebx
  char result; // al
  EFI_GUID VendorGuid; // [rsp+30h] [rbp-10h] BYREF
  bool Data; // [rsp+58h] [rbp+18h] BYREF
  UINTN DataSize; // [rsp+60h] [rbp+20h] BYREF

  VendorGuid.Data1 = -1954858115;
  *&VendorGuid.Data2 = 1210466085;
  *VendorGuid.Data4 = 365057174;
  *&VendorGuid.Data4[4] = 845990413;
  Data = 0;
  DataSize = 1i64;
  if ( (gRT->GetVariable(L"EfiExternalGfxState", &VendorGuid, 0i64, &DataSize, &Data) & 0x8000000000000000ui64) != 0i64 )
  {
    if ( sub_630() )
    {
      Data = 1;
      v2 = 240;
    }
    else
    {
      Data = 0;
      v2 = 180;
    }
    DataSize = 1; // Re-initialize DataSize with correct buffer size
    gRT->SetVariable(
      L"EfiExternalGfxState",
      &VendorGuid,
      7u,
      DataSize,
      &Data);
    if ( a1 < v2 )
      __outbyte(0xCF9u, 6u);
  }
  result = sub_630();
  if ( Data != (result != 0) )
  {
    Data = result != 0;
    DataSize = 1; // Re-initialize DataSize with correct buffer size
    (gRT->SetVariable)(L"EfiExternalGfxState", &VendorGuid, 7i64, DataSize, &Data);
    result = 6;
    __outbyte(0xCF9u, 6u);
  }
  return result;
}
