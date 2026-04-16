__int64 sub_192A0()
{
  EFI_GET_VARIABLE GetVariable;
  int ResValue;
  EFI_SET_VARIABLE SetVariable;
  int RunCyclesValue;
  __int64 DataSize;

  RunCyclesValue = 0;
  CheckHwErrRecSupport();
  DataSize = 4;
  if ( (gRT->GetVariable)(L"MTC", &gVariableGuid, 0, &DataSize, &gMtcValue) )
    gMtcValue = 0;
  GetVariable = gRT->GetVariable;
  DataSize = 4;
  if ( (GetVariable)(L"RunCycles", &gVariableGuid, 0, &DataSize, &RunCyclesValue) == EFI_NOT_FOUND )
  {
    ResValue = 1;
    RunCyclesValue = 0;
  }
  else
  {
    ResValue = RunCyclesValue + 1;
  }
  SetVariable = gRT->SetVariable;
  RunCyclesValue = ResValue;
  DataSize = sizeof(RunCyclesValue); // Ensure correct size before SetVariable
  (SetVariable)(L"RunCycles", &gVariableGuid, 7, DataSize, &RunCyclesValue);
  DataSize = sizeof(RunCyclesValue); // Ensure correct size before GetVariable
  return (gRT->GetVariable)(L"RunCycles", &gVariableGuid, 0, &DataSize, &RunCyclesValue);
}
