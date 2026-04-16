__int64 __fastcall sub_13D4()
{
  signed __int64 v0; // rbx
  EFI_EVENT Event; // [rsp+40h] [rbp+10h] BYREF
  UINTN DataSize; // [rsp+48h] [rbp+18h] BYREF

  Event = 0i64;
  DataSize = 8i64;
  gRT->GetVariable(
    (CHAR16 *)L"BIQ_BOOT_INTERRUPTION",
    &VendorGuid,
    0i64,
    &DataSize,
    &Event);
  Event = (char *)Event + 1;
  gRT->SetVariable(
    (CHAR16 *)L"BIQ_BOOT_INTERRUPTION",
    &VendorGuid,
    3u,
    8i64, // Reinitialize DataSize to correct value (8)
    &Event);
  v0 = sub_14D4();
  if ( v0 >= 0 )
  {
    if ( byte_155A0 )
    {
      return sub_3F04();
    }
    else
    {
      Event = 0i64;
      v0 = gBS->CreateEventEx(0x200u, 8ui64, nullsub_1, 0i64, &VariableGuid, &Event);
      if ( v0 >= 0 )
      {
        v0 = gBS->SignalEvent(Event);
        gBS->CloseEvent(Event);
      }
    }
  }
  return v0;
}
