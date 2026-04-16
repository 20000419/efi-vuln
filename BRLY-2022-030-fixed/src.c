  ...
  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".Type");
  {
    UINTN DataSize = sizeof(VariableValue); // Initialize before each call
    Flag = 0;
    if (gRT->GetVariable(VariableName, &gVariableGuid, NULL, &DataSize, VariableValue) == EFI_SUCCESS) {
      Flag = 1;
      dword_1E630 = VariableValue[0];
    }
  }

  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".FwName");
  {
    UINTN DataSize = sizeof(VariableValue); // Reset before next call
    if (gRT->GetVariable(VariableName, &gVariableGuid, NULL, &DataSize, VariableValue) == EFI_SUCCESS) {
      sub_9B38(word_1E634, 0x1F, VariableValue, 0x1F);
      Flag = 1;
    }
  }

  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".PartiLabel");
  {
    UINTN DataSize = sizeof(VariableValue); // Fresh initialization
    if (gRT->GetVariable(VariableName, &gVariableGuid, NULL, &DataSize, VariableValue) == EFI_SUCCESS) {
      sub_9B38(word_1E674, 0x1F, VariableValue, 0x1F);
      Flag = 1;
    }
  }

  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".PartiRootGuid");
  {
    UINTN DataSize = sizeof(VariableValue); // Consistent reset
    if (gRT->GetVariable(VariableName, &gVariableGuid, NULL, &DataSize, VariableValue) == EFI_SUCCESS) {
      sub_8E98(&byte_1E6B4, VariableValue);
      Flag = 1;
    }
  }

  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".PartiGuid");
  {
    UINTN DataSize = sizeof(VariableValue); // Per-call initialization
    if (gRT->GetVariable(VariableName, &gVariableGuid, NULL, &DataSize, VariableValue) == EFI_SUCCESS) {
      sub_8E98(&byte_1E6C4, VariableValue);
      Flag = 1;
    }
  }

  AsciiStrToUnicodeStr(&Name, VariableName);
  StrCatS(VariableName, 0x80, L".ImagePath");
  {
    UINTN DataSize = sizeof(VariableValue); // Final safe initialization
    if (gRT->GetVariable(VariableName, &gVariableGuid, NULL, &DataSize, VariableValue) == EFI_SUCCESS) {
      sub_9B38(word_1E6D4, 0x1F, VariableValue, 0x1F);
      Flag = 1;
    }
  }
  ...
