__int64 SaPolisyProtocolNotifier()
{
  EFI_STATUS Status; // rax
  __int64 result; // rax
  void *Interface; // [rsp+30h] [rbp-50h] BYREF
  EFI_GUID VendorGuid; // [rsp+48h] [rbp-38h] BYREF
  char IntelTechnologiesOptionsBuffer[40]; // [rsp+58h] [rbp-28h] BYREF
  char Buffer; // [rsp+A0h] [rbp+20h] BYREF
  UINTN DataSize; // [rsp+A8h] [rbp+28h] BYREF
  ...

  VendorGuid.Data1 = 0xFB3B9ECE;
  *&VendorGuid.Data2 = 0x49334ABA;
  *VendorGuid.Data4 = 0xD6B49DB4;
  *&VendorGuid.Data4[4] = 0x5123897D;
  gBS->LocateProtocol(&SA_POLICY_PROTOCOL_GUID, 0, &Interface);
  ...
  ZeroMem(&Buffer, 1);
  DataSize = 0;
  Status = gRT->GetVariable(L"PciePwrMgmt", &VendorGuid, 0, &DataSize, &Buffer);
  if ( Status == EFI_BUFFER_TOO_SMALL )
    Status = gRT->GetVariable(L"PciePwrMgmt", &VendorGuid, 0, &DataSize, &Buffer);
  if ( Status || Buffer )
  {
    ...
  }
  ...
  DataSize = 30;
  gRT->GetVariable(L"IntelTechnologiesOptions", &VendorGuid, 0, &DataSize, IntelTechnologiesOptionsBuffer);
  ...
  return result;
}

