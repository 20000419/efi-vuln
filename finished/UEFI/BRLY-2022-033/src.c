__int64 sub_66E8()
{
  // ...

  __int64 DataSize;
  unsigned __int8 Value;
  int v31;
  __int64 v32;
  unsigned int v33;
  __int64 result;

  result = 0;
  v33 = 1;
  v32 = 32;
  v31 = 32;
  DataSize = 1;
  result = gRT->GetVariable(L"UsbConfigPrimaryPort", &gVariableGuid, 0, &DataSize, &Value);
  if ( result >= 0 )
    LODWORD(v32) = sub_6528(Value);
  else
    LODWORD(v32) = 32;
  result = gRT->GetVariable(L"UsbConfigSecondaryPort", &gVariableGuid, 0, &DataSize, &Value);

  // ...
}
