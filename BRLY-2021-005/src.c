...
Attributes = a2;
DataSize = 0i64;
Interface = 0i64;
gBS_23A0->LocateProtocol(&ProprietaryProtocol_2040, 0i64, &Interface);
if ( gRT_23B0->GetVariable((CHAR16 *)L"DptfOptions", &VendorGuid, (UINT32 *)&Attributes, &DataSize, &Buffer) != EFI_BUFFER_TOO_SMALL
  || gRT_23B0->GetVariable((CHAR16 *)L"DptfOptions", &VendorGuid, (UINT32 *)&Attributes, &DataSize, &Buffer) )
{
  goto _GetCoolControlData;
}
...
