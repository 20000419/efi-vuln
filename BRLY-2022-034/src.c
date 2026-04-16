__int64 sub_2B80()
{
  // starting at basic block 0x3418
  // ...
  GetVariable = gRT->GetVariable;
  DataSize = 49;
  GetVariable(L"LenovoFunctionConfig", &gVariableGuid, &v24, &DataSize, Value);
  Value[0] = 0;
  result = (gRT->SetVariable)(L"LenovoFunctionConfig", &gVariableGuid, v24, DataSize, Value);
  // ...
}
