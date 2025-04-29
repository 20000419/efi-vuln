EFI_STATUS __fastcall ChildSwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        _QWORD *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( !gAmiSmmBufferValidationProtocol
    || (gAmiSmmBufferValidationProtocol->ValidateMemoryBuffer)(
         CommBuffer,
         48,
         CommBuffer,
         CommBufferSize) < 0 )
  {
    return 0;
  }
  switch ( *CommBuffer )
  {
    case 1:
      v13 = CommBuffer[1];
      if ( v13
        && (!gAmiSmmBufferValidationProtocol
         || (gAmiSmmBufferValidationProtocol->ValidateMemoryBuffer)(v13, 4095) < 0) )
      {
        return 0;
      }
      v14 = CommBuffer[4];
      if ( v14 )
      {
        if ( !gAmiSmmBufferValidationProtocol
          || (gAmiSmmBufferValidationProtocol->ValidateMemoryBuffer)(v14, 8) < 0 )
        {
          return 0;
        }
      }
      LOBYTE(CommBuffer14b) = *((_BYTE *)CommBuffer + 20);
      Status = gSmbiosElog->ApiFunc1(
                 gSmbiosElog,
                 CommBuffer[1],
                 *((unsigned int *)CommBuffer + 4),
                 CommBuffer14b,
                 CommBuffer[3],
                 CommBuffer[4]);
_SetStatusAndReturn:
      CommBuffer[5] = Status;
      return 0;
    case 2:
      Arg1 = CommBuffer[1];
      if ( Arg1
        && (!gAmiSmmBufferValidationProtocol
         || (gAmiSmmBufferValidationProtocol->ValidateMemoryBuffer)(Arg1, 4095) < 0) )
      {
        return 0;
      }
      Arg3_MaxSize = CommBuffer[3];
      if ( Arg3_MaxSize )
      {
        if ( !gAmiSmmBufferValidationProtocol
          || (gAmiSmmBufferValidationProtocol->ValidateMemoryBuffer)(Arg3_MaxSize, 8) < 0 )
        {
          return 0;
        }
      }
      Arg4 = CommBuffer[4];
      if ( Arg4 )
      {
        if ( !gAmiSmmBufferValidationProtocol
          || (gAmiSmmBufferValidationProtocol->ValidateMemoryBuffer)(Arg4, 8) < 0 )
        {
          return 0;
        }
      }
      Status = gSmbiosElog->ApiFunc2(
                 gSmbiosElog,
                 CommBuffer[1],
                 *((unsigned int *)CommBuffer + 4),
                 CommBuffer[3],
                 CommBuffer[4]);
      goto _SetStatusAndReturn;
    case 3:
      Arg2_1 = CommBuffer[2];
      if ( !Arg2_1
        || gAmiSmmBufferValidationProtocol
        && (gAmiSmmBufferValidationProtocol->ValidateMemoryBuffer)(Arg2_1, 8) >= 0 )
      {
        CommBuffer[3] = gSmbiosElog->ApiFunc3(gSmbiosElog, *((unsigned int *)CommBuffer + 2), CommBuffer[2]);
      }
      break;
    case 4:
      Arg2 = CommBuffer[2];
      if ( !Arg2
        || gAmiSmmBufferValidationProtocol
        && (gAmiSmmBufferValidationProtocol->ValidateMemoryBuffer)(Arg2, 1) >= 0 )
      {
        Arg3 = CommBuffer[3];
        if ( !Arg3
          || gAmiSmmBufferValidationProtocol
          && (gAmiSmmBufferValidationProtocol->ValidateMemoryBuffer)(Arg3, 1) >= 0 )
        {
          CommBuffer[4] = gSmbiosElog->ApiFunc4(
                            gSmbiosElog,
                            *((unsigned int *)CommBuffer + 2),
                            CommBuffer[2],
                            CommBuffer[3]);
        }
      }
      break;
  }
  return 0;
}

MACRO_EFI __fastcall FuncCase1(__int64 SmbiosElog, __int16 *Arg1, __int64 Arg2, __int64 Arg3, UINTN Arg4, _QWORD *Arg5)
{
  ...
  unsigned __int8 DestinationBuffer[127];

  if ( Arg2 )
    return EFI_NOT_FOUND;
  if ( !gFlag )
    return EFI_UNSUPPORTED;
  if ( !Arg1 )
    return EFI_INVALID_PARAMETER;
  Arg5_1 = Arg5;
  if ( !Arg5 )
    return EFI_INVALID_PARAMETER;
  p_ValueFromArg1_1 = &ValueFromArg1_1;
  SetTimeInfo(&ValueFromArg1, Arg1, Arg2);
  Case = 0xFF;
  if ( *Arg1 == 0xE2 )
  {
    Value = *(Arg1 + 1);                        // should be set to 0x81 (as an example)
                                                // Value >= 0x80 and not in gCases, gCases1
    p_ValueFromArg1_1 = Arg1;
  }
  else...
  ValueFromArg1 = Value;
  if ( Value > 23 || (v13 = 0xFF7FFE, !_bittest(&v13, Value)) )
  {
    if ( Value < 0x80 )
      return EFI_UNSUPPORTED;
  }
  v14 = 0;
  while ( gCases[2 * v14] != Value )
  {
    if ( ++v14 >= 25 )
      goto _LeaveCaseFF;
  }
  Case = gCases1[2 * v14];
_LeaveCaseFF:
  ZeroMem(DestinationBuffer, 127);
  v16 = 8;
  switch...
  v30 = v16;
  switch...
  v16 = Arg4 + 8;
  v30 = Arg4 + 8;
  if ( Arg4 && DestinationBuffer != (Arg1 + 4) )
  {
    // will overwrite the return address if Arg4 >= 0x130
    CopyMem(DestinationBuffer, Arg1 + 4, Arg4);
    v16 = v30;
  }
  ...
  return EFI_OUT_OF_RESOURCES;
}
