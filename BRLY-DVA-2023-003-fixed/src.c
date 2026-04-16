MACRO_EFI sub_167C()
{
  EFI_STATUS Status;
  EFI_SMM_VARIABLE_PROTOCOL *EfiSmmVariableProtocol;
  UINTN DataSize;
  UINT8 Data[1200]; // Assuming fixed buffer size for Setup, adjust SaSetup accordingly
  UINT8 SmiData;
  UINTN Value;
  EFI_GUID VendorGuid;

  SmiData = __inbyte(gB3DataPort);
  if (SmiData < 36)
    goto _EfiUnsupported;
  if (SmiData > 38)
  {
    if (SmiData > 47)
    {
      if (SmiData <= 49)
      {
        VendorGuid.Data1 = 0xA04A27F4;
        VendorGuid.Data2 = 0x4D42DF00;
        VendorGuid.Data4[0] = 0xB5523951; // Correct byte order for Data4 (assuming little-endian)
        VendorGuid.Data4[4] = 0x1302113D;
        Status = gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, NULL, &EfiSmmVariableProtocol);
        if (Status != EFI_SUCCESS)
          goto _EfiUnsupported;
        DataSize = sizeof(Data); // Initialize to fixed buffer size before GetVariable
        Status = EfiSmmVariableProtocol->SmmGetVariable(L"Setup", &VendorGuid, NULL, &DataSize, Data);
        if (Status == EFI_SUCCESS)
        {
          Data[240] = (SmiData == 48);
          DataSize = sizeof(Data); // Reset to known buffer size before SetVariable
          Status = EfiSmmVariableProtocol->SmmSetVariable(L"Setup", &VendorGuid, 7, DataSize, Data);
        }
        goto _Exit;
      }
      if (SmiData <= 0x33)
      {
        VendorGuid.Data1 = 0xA04A27F4;
        VendorGuid.Data2 = 0x4D42DF00;
        VendorGuid.Data4[0] = 0xB5523951;
        VendorGuid.Data4[4] = 0x1302113D;
        Status = gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, NULL, &EfiSmmVariableProtocol);
        if (Status != EFI_SUCCESS)
          goto _EfiUnsupported;
        DataSize = sizeof(Data); // Initialize to fixed buffer size
        Status = EfiSmmVariableProtocol->SmmGetVariable(L"Setup", &VendorGuid, NULL, &DataSize, Data);
        if (Status == EFI_SUCCESS)
        {
          Data[244] = (SmiData == 50);
          DataSize = sizeof(Data); // Reset to known buffer size
          Status = EfiSmmVariableProtocol->SmmSetVariable(L"Setup", &VendorGuid, 7, DataSize, Data);
        }
        goto _Exit;
      }
      if (SmiData <= 0x35)
      {
        VendorGuid.Data1 = 0xA04A27F4;
        VendorGuid.Data2 = 0x4D42DF00;
        VendorGuid.Data4[0] = 0xB5523951;
        VendorGuid.Data4[4] = 0x1302113D;
        Status = gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, NULL, &EfiSmmVariableProtocol);
        if (Status != EFI_SUCCESS)
          goto _EfiUnsupported;
        DataSize = sizeof(Data); // Initialize to fixed buffer size
        Status = EfiSmmVariableProtocol->SmmGetVariable(L"Setup", &VendorGuid, NULL, &DataSize, Data);
        if (Status == EFI_SUCCESS)
        {
          Data[246] = (SmiData == 0x35);
          DataSize = sizeof(Data); // Reset to known buffer size before SetVariable
_SmmSetSetupVariable:
          Status = EfiSmmVariableProtocol->SmmSetVariable(L"Setup", &VendorGuid, 7, DataSize, Data);
        }
        goto _Exit;
      }
    }
_EfiUnsupported:
    Status = EFI_UNSUPPORTED;
    goto _Exit;
  }

  // SaSetup handling
  Status = gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, NULL, &EfiSmmVariableProtocol);
  if (Status != EFI_SUCCESS)
    goto _Exit;
  DataSize = 1143; // Fixed buffer size for SaSetup
  Status = EfiSmmVariableProtocol->SmmGetVariable(L"SaSetup", &SA_SETUP_VARIABLE_GUID, NULL, &DataSize, Data);
  if (Status == EFI_SUCCESS)
  {
    Value = 4;
    if (SmiData == 38)
      Value = 1;
    if (SmiData == 36)
      Value = 0;
    Data[177] = Value;
    DataSize = 1143; // Reset to known buffer size before SetVariable
    Status = EfiSmmVariableProtocol->SmmSetVariable(L"SaSetup", &SA_SETUP_VARIABLE_GUID, 7, DataSize, Data);
  }

_Exit:
  __outbyte(gB3DataPort, 0);
  return Status;
}
