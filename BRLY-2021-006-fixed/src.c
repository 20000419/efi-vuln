...
_GetCoolControlData:
  DataSize = 8i64;
  v14 = gRT->GetVariable(aCoolcontroldat, &stru_2010, (UINT32 *)&Attributes, &DataSize, v16);
  if ( !v14 && DataSize == 8 )
    sub_1A24(1, v16[1]);
  return v14;
}
