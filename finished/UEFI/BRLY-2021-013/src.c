__int64 sub_80001294()
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  v0 = 0;
  if ( SmstIsNotNull() )
  {
    result = gEfiBootServices->LocateProtocol(&EFI_SMM_ACCESS2_PROTOCOL_GUID, 0, &EfiSmmAccess2Protocol);
    if ( result < 0 )
      return result;
    Size = 0;
    EfiSmmAccess2Protocol->GetCapabilities(EfiSmmAccess2Protocol, &Size, 0);
    SmramMap = 0;
    gSmst_36F0->SmmAllocatePool(EfiRuntimeServicesData, Size, &SmramMap);
    EfiSmmAccess2Protocol->GetCapabilities(EfiSmmAccess2Protocol, &Size, SmramMap);
    gSmramRangeCount = Size >> 5;
    return gSmst_36F0->SmiHandlerRegister(SmiHandler_1278, &gSmiHandlerGuid, &DispatchHandle);
  }
  else
  {
    CommBuffer = sub_80001878(56);
    if ( !CommBuffer )
      return EFI_OUT_OF_RESOURCES;
    (CreateEventEx)(8);
  }
  return v0;
}
