__int64 sub_1D38()
{
  // ...

  DataSize = 139;
  result = (gRT->GetVariable)(L"LenovoSecurityConfig", &LENOVO_SECURITY_CONFIG_VARIABLE_GUID, &DataSize, LenovoSecurityConfigValue);
  if ( (result & 0x8000000000000000) == 0 )
  {
    if...
    if ( gLenovoRuntimeConfigFlag2 | gLenovoRuntimeConfigFlag1 )
    {
      GetVariable = gRT->GetVariable;
      DataSize = 49;
      (GetVariable)(L"LenovoFunctionConfig", &gVariableGuid, &Attributes, &DataSize, LenovoFunctionConfigValue);
      LenovoFunctionConfigValue[0] = 0;
      
      // Re-initialize DataSize to correct value before SetVariable
      DataSize = 49;
      (gRT->SetVariable)(L"LenovoFunctionConfig", &gVariableGuid, Attributes, DataSize, LenovoFunctionConfigValue);
    }
    return 0;
  }
  return result;
}
