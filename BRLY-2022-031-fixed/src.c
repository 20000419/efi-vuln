__int64 sub_32C8()
{
  int val;
  EFI_SET_VARIABLE SetVariable;
  int VariableValue;
  UINTN DataSize; // Use UINTN for size types

  if (ExitBootServicesEventNotified())
    return 0;

  // Initialize DataSize for GetVariable
  DataSize = sizeof(VariableValue); // 4 bytes
  if (gRT->GetVariable(L"BSPowerCycles", &gVariableGuid, NULL, &DataSize, &VariableValue) != EFI_SUCCESS) {
    val = 1;
    VariableValue = 0;
  } else {
    val = VariableValue + 1;
  }

  // Re-initialize DataSize to match buffer size before SetVariable
  DataSize = sizeof(VariableValue); // Ensure 4 bytes are written
  SetVariable = gRT->SetVariable;
  VariableValue = val;
  return SetVariable(L"BSPowerCycles", &gVariableGuid, EFI_VARIABLE_NON_VOLATILE | EFI_VARIABLE_BOOTSERVICE_ACCESS, DataSize, &VariableValue);
}
