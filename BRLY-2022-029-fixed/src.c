__int64 sub_1ED8()
{
  char Value[4];

  // Initialize buffer size before each GetVariable call
  if ((gSkipFlag & 1) == 0) {
    gSkipFlag = 1;

    UINTN dataSize = sizeof(Value); // Initialize to buffer size
    if (gRT->GetVariable(L"DISABLEBATTERY", &MICROSOFT_VENDOR_GUID, NULL, &dataSize, Value) == EFI_SUCCESS)
      gDisableBattery = Value[0] != 0;

    dataSize = sizeof(Value); // Reset before next call
    if (gRT->GetVariable(L"PrintChargerAppDbgMsg", &gVariableGuid, NULL, &dataSize, Value) == EFI_SUCCESS)
      gPrintChargerAppDbgMsg = Value[0] != 0;

    dataSize = sizeof(Value); // Reset again
    if (gRT->GetVariable(L"ChargerPDLogLevel", &gVariableGuid, NULL, &dataSize, Value) == EFI_SUCCESS)
      gChargerPDLogLevel = Value[0];

    dataSize = sizeof(Value); // Repeat for each call
    if (gRT->GetVariable(L"ChargerPDLogTimer", &gVariableGuid, NULL, &dataSize, Value) == EFI_SUCCESS) {
      gChargerPDLogTimer = Value[0];
      gChargerPDLogTimerFlag = Value[0] != 0;
    }

    dataSize = sizeof(Value); // Final reset
    if (gRT->GetVariable(L"ForcePowerTesting", &MICROSOFT_VENDOR_GUID, NULL, &dataSize, Value) == EFI_SUCCESS) {
      gForcePowerTestingValue = 2;
      gForcePowerTestingFlag = Value[0] != 0;
    }
  }
  return 0;
}
