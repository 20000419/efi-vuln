EFI_STATUS __fastcall SwSmiHandler_1574(EFI_HANDLE DispatchHandle)
{
  EFI_STATUS result;
  UINT32 Attributes;
  UINTN DataSize;
  EFI_SMM_SW_DISPATCH2_PROTOCOL *EfiSmmSwDispatch2;
  __int64 Data[6];

  Attributes = 6;
  DataSize = 32i64;
  if ( (gRT_20F8->GetVariable(L"AmdMemContextData", &VendorGuid, &Attributes, &DataSize, Data) & 0x8000000000000000ui64) == 0i64 )
    x_AmdMemContextHandler(Data);
  result = gSmst_20F0->SmmLocateProtocol(&EFI_SMM_SW_DISPATCH_PROTOCOL_GUID_2050, 0i64, &EfiSmmSwDispatch2);
  if ( (result & 0x8000000000000000ui64) == 0i64 )
    return (EfiSmmSwDispatch2->UnRegister)(EfiSmmSwDispatch2, DispatchHandle);
  return result;
}

EFI_STATUS __fastcall EfiEventReadyToBootNotifier(EFI_EVENT Event)
  {
    EFI_STATUS status;
    EFI_SMM_CONTROL2_PROTOCOL *EfiSmmControl2Protocol;
    char DataPort;
    char CommandPort;

    status = gBS_2098->LocateProtocol(&EFI_SMM_CONTROL2_PROTOCOL_GUID_2030, 0i64, &EfiSmmControl2Protocol);
    if ( (status & 0x8000000000000000ui64) == 0i64 )
    {
      CommandPort = 0xAE;
      DataPort = 1;
      (EfiSmmControl2Protocol->Trigger)(EfiSmmControl2Protocol, &CommandPort, &DataPort, 0i64, 0i64);
      return gBS_2098->CloseEvent(Event);
    }
    return status;
  }
