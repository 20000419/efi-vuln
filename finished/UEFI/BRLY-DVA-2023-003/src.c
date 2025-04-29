MACRO_EFI sub_167C()
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  SmiData = __inbyte(gB3DataPort);
  if ( SmiData < 36 )
    goto _EfiUnsupported;
  if ( SmiData > 38 )
  {
    if ( SmiData > 47 )
    {
      if ( SmiData <= 49 )
      {
        VendorGuid.Data1 = 0xA04A27F4;
        *&VendorGuid.Data2 = 0x4D42DF00;
        *VendorGuid.Data4 = 0x513952B5;
        *&VendorGuid.Data4[4] = 0x3D110213;
        gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, 0, &EfiSmmVariableProtocol);
        DataSize = 1200;
        EfiSmmVariableProtocol->SmmGetVariable(L"Setup", &VendorGuid, 0, &DataSize, Data);
        Data[240] = SmiData == 48;
        goto _SmmSetSetupVariable;
      }
      if ( SmiData <= 0x33 )
      {
        VendorGuid.Data1 = 0xA04A27F4;
        *&VendorGuid.Data2 = 0x4D42DF00;
        *VendorGuid.Data4 = 0x513952B5;
        *&VendorGuid.Data4[4] = 0x3D110213;
        gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, 0, &EfiSmmVariableProtocol);
        DataSize = 1200;
        EfiSmmVariableProtocol->SmmGetVariable(L"Setup", &VendorGuid, 0, &DataSize, Data);
        Data[244] = SmiData == 50;
        goto _SmmSetSetupVariable;
      }
      if ( SmiData <= 0x35 )
      {
        VendorGuid.Data1 = 0xA04A27F4;
        *&VendorGuid.Data2 = 0x4D42DF00;
        *VendorGuid.Data4 = 0x513952B5;
        *&VendorGuid.Data4[4] = 0x3D110213;
        gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, 0, &EfiSmmVariableProtocol);
        DataSize = 1200;
        EfiSmmVariableProtocol->SmmGetVariable(L"Setup", &VendorGuid, 0, &DataSize, Data);
        Data[246] = SmiData == 0x35;
_SmmSetSetupVariable:
        EfiSmmVariableProtocol->SmmSetVariable(L"Setup", &VendorGuid, 7, DataSize, Data);
        Status = EFI_SUCCESS;
        goto _Exit;
      }
    }
_EfiUnsupported:
    Status = EFI_UNSUPPORTED;
    goto _Exit;
  }
  gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, 0, &EfiSmmVariableProtocol);
  DataSize = 1143;
  EfiSmmVariableProtocol->SmmGetVariable(L"SaSetup", &SA_SETUP_VARIABLE_GUID, 0, &DataSize, Data);
  Value = 4;
  if ( SmiData == 38 )
    Value = 1;
  Status = EFI_SUCCESS;
  if ( SmiData == 36 )
    Value = 0;
  Data[177] = Value;
  EfiSmmVariableProtocol->SmmSetVariable(L"SaSetup", &SA_SETUP_VARIABLE_GUID, 7, DataSize, Data);
_Exit:
  __outbyte(gB3DataPort, 0);
  return Status;
}
