VendorGuid.Data1 = 0x8BE4DF61;
*&VendorGuid.Data2 = 0x11D293CA;
*VendorGuid.Data4 = 0xE0000DAA;
*&VendorGuid.Data4[4] = 0x8C2B0398;
Buffer = 0i64;
DataSize = 8i64;                              // data size only initialize once
if ( IsNotEqual(buf, g_buf) )                 // False (buf = g_buf)
{
  gBS_157B28->SetMem(&Buffer, 8ui64, 0);
  sprintf_s(&Buffer, 8i64, "%a", vLang);
}
else if ( (gRT_157B30->GetVariable(L"PlatformLang", &VendorGuid, 0i64, &DataSize, &Buffer) & 0x8000000000000000ui64) == 0i64 )
{
  WriteLog(L"PlatformLang reported as %a.\r\n", &Buffer);
}
else
{
  // DataSize didn't change after the first GetVariable call which leads stack buffer overflow
  if ( (gRT_157B30->GetVariable(L"Lang", &VendorGuid, 0i64, &DataSize, &Buffer) & 0x8000000000000000ui64) != 0i64 )
  {
    result = WriteLog(L"Unable to find Lang variable, defaulting to English.\r\n");
    g_LangVarFound = 0i64;
    return result;
  }
  WriteLog(L"Lang reported as %a.\r\n", &Buffer);
}
