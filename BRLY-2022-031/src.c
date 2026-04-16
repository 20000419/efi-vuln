__int64 sub_32C8()
{
  int val;
  EFI_SET_VARIABLE SetVariable;
  int VariableValue;
  __int64 DataSize;

  DataSize = 4;
  if ( ExitBootServicesEventNotified() )
    return 0;

  // The following code can only be executed before ExitBootServices
  if ( (gRT->GetVariable)(L"BSPowerCycles", &gVariableGuid, 0, &DataSize, &VariableValue) )
  {
    val = 1;
    VariableValue = 0;
  }
  else
  {
    val = VariableValue + 1;
  }
  SetVariable = gRT->SetVariable;
  VariableValue = val;
  return (SetVariable)(L"BSPowerCycles", &gVariableGuid, 3, DataSize, &VariableValue);
}
