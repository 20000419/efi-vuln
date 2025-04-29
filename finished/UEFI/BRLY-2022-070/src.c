__int64 __fastcall sub_143C()
{
  __int64 v1; // [rsp+40h] [rbp+8h] BYREF

  v1 = 8i64;
  (gRT_0->GetVariable)(                         // <= first call (we can rewrite DataSize here)
    L"SmbiosEntryPointTable",
    &EFI_SMBIOS_NVRAM_DATA_GUID,
    0i64,
    &v1,
    &gSmbiosEntryPointTable);
  (gRT_0->GetVariable)(                         // <= second call
    L"SmbiosEntryPointTableF000",
    &EFI_SMBIOS_NVRAM_DATA_GUID,
    0i64,
    &v1,
    &gSmbiosEntryPointTableF000);
  v1 = 8i64;
  (gRT_0->GetVariable)(L"SmbiosV3EntryPointTable", &EFI_SMBIOS_NVRAM_DATA_GUID, 0i64, &v1, &qword_69E8);
  v1 = 8i64;
  (gRT_0->GetVariable)(L"SmbiosScratchBuffer", &EFI_SMBIOS_NVRAM_DATA_GUID, 0i64, &v1, &qword_69F8);
  v1 = 2i64;
  return (gRT_0->GetVariable)(L"MaximumTableSize", &EFI_SMBIOS_NVRAM_DATA_GUID, 0i64, &v1, &word_6B10);
}
