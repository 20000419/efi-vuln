MACRO_EFI __fastcall FuncCase1(__int64 SmbiosElog, __int16 *Arg1, __int64 Arg2, __int64 Arg3, UINTN Arg4, _QWORD *Arg5)
{
  // [COLLAPSED CODE - UNCHANGED PREVIOUS SECTIONS]

  unsigned __int8 DestinationBuffer[127];

  if (Arg2)
    return EFI_NOT_FOUND;
  if (!gFlag)
    return EFI_UNSUPPORTED;
  if (!Arg1)
    return EFI_INVALID_PARAMETER;
  Arg5_1 = Arg5;
  if (!Arg5)
    return EFI_INVALID_PARAMETER;
  p_ValueFromArg1_1 = &ValueFromArg1_1;
  SetTimeInfo(&ValueFromArg1, Arg1, Arg2);
  Case = 0xFF;
  if (*Arg1 == 0xE2)
  {
    Value = *(Arg1 + 1);
    p_ValueFromArg1_1 = Arg1;
  }
  // [UNCHANGED ELSE/CASE LOGIC FOR VALUE DETERMINATION]

  ValueFromArg1 = Value;
  if (Value > 23 || (v13 = 0xFF7FFE, !_bittest(&v13, Value)))
  {
    if (Value < 0x80)
      return EFI_UNSUPPORTED;
  }
  v14 = 0;
  while (gCases[2 * v14] != Value)
  {
    if (++v14 >= 25)
      goto _LeaveCaseFF;
  }
  Case = gCases1[2 * v14];
_LeaveCaseFF:
  ZeroMem(DestinationBuffer, 127);
  v16 = 8;
  // [UNCHANGED SWITCH LOGIC FOR v16/v30 SETTING]

  v16 = Arg4 + 8;
  v30 = Arg4 + 8;
  if (Arg4 && DestinationBuffer != (Arg1 + 4)) 
  {
    // ADD BOUNDS CHECK TO PREVENT STACK OVERFLOW
    if (Arg4 > sizeof(DestinationBuffer)) {
      return EFI_INVALID_PARAMETER;
    }
    CopyMem(DestinationBuffer, Arg1 + 4, Arg4);
    v16 = v30;
  }
  // [UNCHANGED REMAINING CODE]

  return EFI_OUT_OF_RESOURCES;
}
