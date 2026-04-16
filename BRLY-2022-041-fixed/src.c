__int64 ProcessTcgSetup()
{
  //
  // local variables initialization
  //

  Attributes = 3;
  v28 = 0;
  DataSize = 1;
  Data = 0;
  if ( (gBS->LocateProtocol(&SETUP_GUID, 0, &Interface) & 0x8000000000000000) == 0 )
    return (*Interface)();
  result = gBS->LocateProtocol(&EFI_TPM_MP_DRIVER_PROTOCOL_GUID, 0, &v32);
  if ( result >= 0 )
  {
    result = gBS->LocateProtocol(&EFI_TCG_PROTOCOL_GUID, 0, &EfiTcgProtocol);
    if ( result >= 0 )
    {
      result = gBS->LocateProtocol(&TCG_PLATFORM_SETUP_POLICY_GUID, 0, &TcgPlatformSetupPolicy);
      if ( result >= 0 )
      {
        ...
        if ( (gRT->GetVariable(L"TpmOldvar", &TC_EFI_GLOBAL_VARIABLE_GUID, &Attributes, &DataSize, &Data) & 0x8000000000000000) == 0 )
        {
          LOBYTE(v7) = v13;
          if ( Data == v13 )
          {
            if ( v13 != (((v30 | v31) & 1) == 0) )
              v19 = 1;
          }
          else
          {
            Data = v13;
            // Re-initialize DataSize before SetVariable (sub_4D60)
            DataSize = 1;
            sub_4D60(L"TpmOldvar", &TC_EFI_GLOBAL_VARIABLE_GUID, Attributes, DataSize, &Data);
          }
        }
        else
        {
          Data = v13;
          // Re-initialize DataSize before SetVariable
          DataSize = 1;
          gRT->SetVariable(L"TpmOldvar", &TC_EFI_GLOBAL_VARIABLE_GUID, Attributes, DataSize, &Data);
        }
        if ( v19 )
        {
          v13 = ((v30 | v31) & 1) == 0;
          Data = v13;
          v14 = 0;
          v19 = 0;
          // Re-initialize DataSize before SetVariable (sub_4D60)
          DataSize = 1;
          sub_4D60(L"TpmOldvar", &TC_EFI_GLOBAL_VARIABLE_GUID, Attributes, DataSize, &Data);
        }
        ...
      }
    }
  }
  return result;
}
