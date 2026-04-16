EFI_STATUS __fastcall GetPrimaryDisplay(_BYTE *res)
{
  EFI_STATUS result; // rax
  char PrimaryDisplayValue; // [rsp+40h] [rbp+8h] BYREF
  UINTN DataSize; // [rsp+48h] [rbp+10h] BYREF

  if ( !res )
    return EFI_INVALID_PARAMETER;
  DataSize = 0i64;
  *res = 1;
  result = gRT_2F28->GetVariable(
             L"PrimaryDisplay",
             &EFI_GENERIC_VARIABLE_GUID_2DE0,
             0i64,
             &DataSize,
             &PrimaryDisplayValue);
  if ( result == EFI_BUFFER_TOO_SMALL )
    result = gRT_2F28->GetVariable(
               L"PrimaryDisplay",
               &EFI_GENERIC_VARIABLE_GUID_2DE0,
               0i64,
               &DataSize,
               &PrimaryDisplayValue);
  if ( (result & 0x8000000000000000ui64) == 0i64 )
  {
    if ( (PrimaryDisplayValue & 0xFB) != 0 )
    {
      if ( ((PrimaryDisplayValue - 1) & 0xFD) != 0 )
      {
        if ( PrimaryDisplayValue == 2 )
          *res = 2;
      }
      else
      {
        *res = 1;
      }
    }
    else
    {
      *res = 0;
    }
    return 0i64;
  }
  return result;
}
