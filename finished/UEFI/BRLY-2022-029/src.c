__int64 sub_1ED8()
{
  __int64 DataSize;
  char Value[4];

  Value[0] = 0;
  DataSize = 1;
  if ( (gSkipFlag & 1) == 0 )
  {
    gSkipFlag = 1;
    if ( !(gRT->GetVariable)(L"DISABLEBATTERY", &MICROSOFT_VENDOR_GUID, 0, &DataSize, Value) )
      gDisableBattery = Value[0] != 0;

    if ( !(gRT->GetVariable)(L"PrintChargerAppDbgMsg", &gVariableGuid, 0, &DataSize, Value) )
      gPrintChargerAppDbgMsg = Value[0] != 0;

    if ( !(gRT->GetVariable)(L"ChargerPDLogLevel", &gVariableGuid, 0, &DataSize, Value) )
      gChargerPDLogLevel = Value[0];

    if ( !(gRT->GetVariable)(L"ChargerPDLogTimer", &gVariableGuid, 0, &DataSize, Value) )
    {
      gChargerPDLogTimer = Value[0];
      gChargerPDLogTimerFlag = Value[0] != 0;
    }

    if ( !(gRT->GetVariable)(L"ForcePowerTesting", &MICROSOFT_VENDOR_GUID, 0, &DataSize, Value) )
    {
      gForcePowerTestingValue = 2;
      gForcePowerTestingFlag = Value[0] != 0;
    }
  }
  return 0;
}
