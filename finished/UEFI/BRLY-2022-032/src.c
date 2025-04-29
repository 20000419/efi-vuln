__int64 __fastcall EventNotifier()
{
  __int64 result;
  EFI_SET_VARIABLE SetVariable;
  EFI_GET_VARIABLE GetVariable;
  EFI_SET_VARIABLE SetVariable_1;
  __int64 DataSize;
  unsigned int Attributes;
  __int64 UnknownProtocolInterface;
  __int16 LenovoAbtStatusValue[7];
  char LenovoSecurityConfig[139];

  result = LocateProtocol(&gProtocolGuid, &gDataSegmentBase);
  if ( (result & 0x8000000000000000) == 0 )
  {
    DataSize = 0x8B;
    result = (gRT->GetVariable)(
               L"LenovoSecurityConfig",
               &LENOVO_SECURITY_CONFIG_VARIABLE_GUID,
               &Attributes,
               &DataSize,
               LenovoSecurityConfig);
    if ( (result & 0x8000000000000000) == 0 )
    {
      SetVariable = gRT->SetVariable;
      LenovoSecurityConfig[38] = 1;
      if ( ((SetVariable)(
              L"LenovoSecurityConfig",
              &LENOVO_SECURITY_CONFIG_VARIABLE_GUID,
              Attributes,
              DataSize,
              LenovoSecurityConfig) & 0x8000000000000000) == 0 )
        (*(UnknownProtocolInterface + 0x10))(); // aa5978d6-4fba-4827-b776-9a11fc8cce4c
      GetVariable = gRT->GetVariable;
      DataSize = 14;
      if ( ((GetVariable)(L"LenovoAbtStatus", &unk_4030, &Attributes, &DataSize, LenovoAbtStatusValue) & 0x8000000000000000) != 0 )
      {
        sub_28A8(LenovoAbtStatusValue, 14);
        LenovoAbtStatusValue[2] = 0x100;
        LenovoAbtStatusValue[0] = 1;
        sub_28A8(&LenovoAbtStatusValue[3], 7);
      }
      SetVariable_1 = gRT->SetVariable;
      LOBYTE(LenovoAbtStatusValue[2]) = 1;
      return (SetVariable_1)(L"LenovoAbtStatus", &unk_4030, Attributes, DataSize, LenovoAbtStatusValue);
    }
  }
  return result;
}
