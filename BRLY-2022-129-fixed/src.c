__int64 __fastcall sub_7D8(unsigned __int64 a1, _DWORD *a2)
{
  // ... (existing code unchanged) ...

  v14 = v13 - 100339459;
  if ( !v14 )
  {
    DataSize = 656i64;
    gRT->GetVariable(L"SaSetup", &SA_SETUP_VARIABLE_GUID, 0i64, &DataSize, Data);
    DataSize = 8i64;
    if ( !gRT->GetVariable(L"PRAM_Conf", &EFI_PRAM_CONF_GUID, 0i64, &DataSize, &v47) && v47 != v46 )
    {
      DataSize = 656i64;
      gRT->GetVariable(
        L"SaSetup",
        &SA_SETUP_VARIABLE_GUID,
        &Attributes,
        &DataSize,
        v44);
      v44[519] = v47;
      DataSize = 656; // Re-initialize DataSize with correct buffer size
      gRT->SetVariable(
        L"SaSetup",
        &SA_SETUP_VARIABLE_GUID,
        Attributes,
        DataSize,
        v44);
      gRT->ResetSystem(EfiResetWarm, 0i64, 0i64, 0i64);
      v41[1] = 0i64;
      while ( 1 )
        ;
    }
    // ... (remaining code unchanged) ...
  }

  // ... (rest of the code remains the same) ...
}
