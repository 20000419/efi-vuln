...
Attributes = a2;
Interface = 0i64;
DataSize = 12i64;
gBS_23A0->LocateProtocol(&ProprietaryProtocol_2040, 0i64, &Interface);
if ( gRT->GetVariable(VariableName, &VendorGuid, (UINT32 *)&Attributes, &DataSize, &Data) || DataSize != 12 )
{
  goto _GetCoolControlData;
}
...
