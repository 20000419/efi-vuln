...
_GetCoolControlData:
  DataSize = 8i64;
  vStatus = gRT_23B0->GetVariable(
              (CHAR16 *)L"CoolControlData",
              &gVendorGuid,
              (UINT32 *)&Attributes,
              &DataSize,
              vCoolControlDataValue);
  // If the length of the CoolControlData variable is greater than 8, then at the moment vStatus = EFI_BUFFER_TOO_SMALL
  // (this means that the GetVariable call will occur a second time)
  if ( !vStatus
    || (vStatus = gRT_23B0->GetVariable(
                    (CHAR16 *)L"CoolControlData",
                    &gVendorGuid,
                    (UINT32 *)&Attributes,
                    &DataSize,
                    vCoolControlDataValue)) == 0 )
  {
    LOBYTE(v19) = vCoolControlDataValue[1];
    LOBYTE(v20) = 1;
    sub_1A78(v20, v19);
  }
  return vStatus;
}
