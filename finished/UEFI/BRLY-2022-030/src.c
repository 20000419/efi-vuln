  ...
  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".Type");
  Flag = 0;
  if ( !(gRT->GetVariable)(VariableName, &gVariableGuid, 0, &DataSize, VariableValue) )
  {
    Flag = 1;
    dword_1E630 = VariableValue[0];
  }
  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".FwName");
  if ( !(gRT->GetVariable)(VariableName, &gVariableGuid, 0, &DataSize, VariableValue) )
  {
    sub_9B38(word_1E634, 0x1F, VariableValue, 0x1F);
    Flag = 1;
  }
  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".PartiLabel");
  if ( !(gRT->GetVariable)(VariableName, &gVariableGuid, 0, &DataSize, VariableValue) )
  {
    sub_9B38(word_1E674, 0x1F, VariableValue, 0x1F);
    Flag = 1;
  }
  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".PartiRootGuid");
  if ( !(gRT->GetVariable)(VariableName, &gVariableGuid, 0, &DataSize, VariableValue) )
  {
    sub_8E98(&byte_1E6B4, VariableValue);
    Flag = 1;
  }
  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".PartiGuid");
  if ( !(gRT->GetVariable)(VariableName, &gVariableGuid, 0, &DataSize, VariableValue) )
  {
    sub_8E98(&byte_1E6C4, VariableValue);
    Flag = 1;
  }
  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".ImagePath");
  if ( !(gRT->GetVariable)(VariableName, &gVariableGuid, 0, &DataSize, VariableValue) )
  {
    sub_9B38(word_1E6D4, 0x1F, VariableValue, 0x1F);
    Flag = 1;
  }
  ...
