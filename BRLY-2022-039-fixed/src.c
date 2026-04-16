char __fastcall WriteOnceStatusSetVar(char value1, char value2, __int16 value3)
{
  char Result;
  unsigned __int8 Index;
  _BYTE *table_ptr;
  __int64 Counter;
  __int64 Status;
  EFI_RUNTIME_SERVICES *RuntimeServices;
  UINTN Size;
  char WriteOnceStatusData[64];
  UINTN DataSize;

  DataSize = 64;
  Result = 0;
  Index = 0;
  table_ptr = &gTable;
  Counter = 2;
  Status = gRT->GetVariable(L"WriteOnceStatus", &EFI_SMBIOS_NVRAM_DATA_GUID, 0, &DataSize, WriteOnceStatusData);
  do
  {
    if ( *(table_ptr - 1) == value1 && *table_ptr == value2 && table_ptr[1] )
    {
      if...                                     // will not be executed is Status != EFI_SUCCESS
      if ( Index < 0x10 && !Result )
      {
        RuntimeServices = gRT;
        // Re-initialize DataSize to correct buffer size before SetVariable
        DataSize = sizeof(WriteOnceStatusData); // or 64
        Size = DataSize;
        WriteOnceStatusData[4 * Index] = value1;
        WriteOnceStatusData[4 * Index + 1] = value2;
        *&WriteOnceStatusData[4 * Index + 2] = value3;
        Status = (RuntimeServices->SetVariable)(
                   L"WriteOnceStatus",
                   &EFI_SMBIOS_NVRAM_DATA_GUID,
                   7,
                   Size,
                   WriteOnceStatusData);
      }
    }
_Next:
    table_ptr += 3;
    --Counter;
  }
  while ( Counter );
  return Result;
}
