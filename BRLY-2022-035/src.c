unsigned sub_2B18()
{
  // ...
  DataSize = 8;
  if ( (gRT->GetVariable(L"PwdUnlockErr", &gVariableGuid, 0, &DataSize, Value) & 0x8000000000000000) != 0 )
    v10 = 1;
  else
    v10 = *(v6 + 1);
  SetVariable = gRT->SetVariable;
  Value[0] = v10;
  SetVariable(L"PwdUnlockErr", &gVariableGuid, VARIABLE_ATTRIBUTE_NV_BS_RT, DataSize, Value);
  // ...
}
