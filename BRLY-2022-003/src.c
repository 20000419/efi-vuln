__int64 __fastcall SwSmiHandlerB2(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // Local variables initialization

  Res = 0;
  v43 = 0;
  v44 = 0;
  v45 = 0;
  DataSize = 0x75;
  v26 = 0;
  v30 = 0;
  Status = gEfiSmmVariableProtocol->SmmGetVariable(L"OcSetup", &gVariableGuid, &Attributes, &DataSize, Data);
  if ( Status < 0 )
    return Status;
  if ( !Data[39] )
    return Status;
  CpuIndex = 0xFFFFFFFFFFFFFFFF;
  if ( CommBuffer && CommBufferSize )
    CpuIndex = *CommBuffer;
  if ( CpuIndex == -1 )
    return EFI_UNSUPPORTED;
  Status = (SmmCpuProtocol->ReadSaveState)(SmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RBX, CpuIndex, &RbxValue);
  Status = (SmmCpuProtocol->ReadSaveState)(SmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RCX, CpuIndex, &RcxValue);
  Ptr = RbxValue;
  Ptr16 = (RbxValue + 16);
  v27 = sub_3544();
  v29 = sub_352C();
  v28 = sub_3514();
  if ( RcxValue >= 3 )
  {
    Res = 0x8004;
    result = (SmmCpuProtocol->WriteSaveState)(SmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RBX, CpuIndex, &Res);
    Status = result;
    return result;
  }
  if ( !RcxValue )
  {
    v46 = 12;
    v26 = 456;
    v30 = 55;
    if ( v27 )
    {
      v26 += 8;
      ++v30;
      if ( v29 )
      {
        v26 += 32;
        v30 += 4;
      }
      if ( v28 )
      {
        v26 += 8 * word_40E8;
        v30 += word_40E8;
      }
    }
    if ( *Ptr != '2DB$' )
    {
      if ( *Ptr == '$DB$' )
      {
        *Ptr = '2DB$';
        *(Ptr + 4) = v26;
        *(Ptr + 8) = 2;
        *(Ptr + 10) = 0;
        Res = 1;
      }
      else
      {
        Res = 0x8001;
      }
      result = (SmmCpuProtocol->WriteSaveState)(SmmCpuProtocol, 4, 39, CpuIndex, &Res);
      Status = result;
      return result;
    }
    if ( *(Ptr + 4) <= v26 )
    {
      if ( *(Ptr + 4) < v46 )
      {
        Res = 0x8003;
        result = (SmmCpuProtocol->WriteSaveState)(SmmCpuProtocol, 4, 39, CpuIndex, &Res);
        Status = result;
        return result;
      }
      if ( *(Ptr + 4) < v26 )
      {
        *(Ptr + 4) = v26;
        *(Ptr + 8) = 2;
        *(Ptr + 10) = 0;
        Res = 0x8002;
        result = (SmmCpuProtocol->WriteSaveState)(SmmCpuProtocol, 4, 39, CpuIndex, &Res);
        Status = result;
        return result;
      }
      Res = 0;
      Status = (SmmCpuProtocol->WriteSaveState)(SmmCpuProtocol, 4, 39, CpuIndex, &Res);
      *(Ptr + 8) = 2;
      *(Ptr + 10) = 0;
    }
    else
    {
      *(Ptr + 4) = v26;
      *(Ptr + 8) = 2;
      *(Ptr + 10) = 0;
      Res = 2;
      Status = (SmmCpuProtocol->WriteSaveState)(SmmCpuProtocol, 4, 39, CpuIndex, &Res);
    }
    *(Ptr + 12) = v30;
    *Ptr16 = 0x29;
    Ptr16[1] = Data[40];
    Ptr16[2] = 0;
    Ptr16[3] = Data[41];
    Ptr16[4] = 7;
    Ptr16[5] = Data[1];
    Ptr16[6] = 8;
    Ptr16[7] = Data[2];
    Ptr16[8] = 10;
    Ptr16[9] = *&Data[3];
    Ptr16[10] = 11;
    if ( Data[5] )
      Ptr16[11] = Data[5];
    else
      Ptr16[11] = -2;
    Ptr16[12] = 21;
    Ptr16[13] = *&Data[6];
    Ptr16[14] = 22;
    Ptr16[15] = Data[8];
    Ptr16[16] = 23;
    Ptr16[17] = Data[9];
    Ptr16[18] = 25;
    Ptr16[19] = Data[10];
    Ptr16[20] = 40;
    Ptr16[21] = *&Data[11];
    Ptr16[22] = 24;
    if ( Data[14] )
      Ptr16[23] = Data[14];
    else
      Ptr16[23] = -2;
    Ptr16[24] = 19;
    if ( Data[16] == Data[15] )
      Ptr16[25] = -2;
    else
      Ptr16[25] = Data[16];
    Ptr16[26] = 5;
    Ptr16[27] = *&Data[18];
    Ptr16[28] = 1;
    Ptr16[29] = *&Data[21];
    Ptr16[30] = 59;
    Ptr16[31] = Data[25];
    Ptr16[32] = 101;
    Ptr16[33] = Data[99];
    Ptr16[34] = 88;
    Ptr16[35] = Data[44];
    Ptr16[36] = 284;
    Ptr16[37] = Data[108];
    Ptr16[38] = 102;
    Ptr16[39] = *&Data[95];
    Ptr16[40] = 114;
    Ptr16[41] = Data[97];
    Ptr16[42] = 115;
    Ptr16[43] = Data[98];
    v5 = 22;
    if ( Data[44] )
    {
      if ( Data[44] == 1 )
      {
        Ptr16[44] = 2;
        Ptr16[45] = *&Data[45];
        v5 = 23;
      }
    }
    else
    {
      Ptr16[44] = 2;
      Ptr16[45] = *&Data[47];
      v5 = 23;
    }
    if ( Data[51] == 1 )
      v33 = 1000 - *&Data[49];
    else
      v33 = *&Data[49] + 1000;
    Ptr16[2 * v5] = 34;
    Ptr16[2 * v5 + 1] = v33;
    v6 = v5 + 1;
    Ptr16[2 * v6] = 66;
    Ptr16[2 * v6++ + 1] = Data[61];
    Ptr16[2 * v6] = 64;
    Ptr16[2 * v6++ + 1] = Data[26];
    Ptr16[2 * v6] = 73;
    Ptr16[2 * v6 + 1] = Data[27];
    v7 = v6 + 1;
    if ( v27 )
    {
      Ptr16[2 * v7] = 26;
      Ptr16[2 * v7++ + 1] = Data[62];
      if ( v28 )
      {
        Ptr16[2 * v7] = 29;
        Ptr16[2 * v7 + 1] = Data[63];
        v8 = v7 + 1;
        Ptr16[2 * v8] = 30;
        Ptr16[2 * v8 + 1] = Data[64];
        v7 = v8 + 1;
        if ( word_40E8 > 2u )
        {
          Ptr16[2 * v7] = 31;
          Ptr16[2 * v7 + 1] = Data[65];
          v9 = v7 + 1;
          Ptr16[2 * v9] = 32;
          Ptr16[2 * v9 + 1] = Data[66];
          v7 = v9 + 1;
          if ( word_40E8 > 4u )
          {
            Ptr16[2 * v7] = 42;
            Ptr16[2 * v7 + 1] = Data[67];
            v10 = v7 + 1;
            Ptr16[2 * v10] = 43;
            Ptr16[2 * v10 + 1] = Data[68];
            v7 = v10 + 1;
            if ( word_40E8 > 6u )
            {
              Ptr16[2 * v7] = 96;
              Ptr16[2 * v7 + 1] = Data[69];
              v11 = v7 + 1;
              Ptr16[2 * v11] = 97;
              Ptr16[2 * v11 + 1] = Data[70];
              v7 = v11 + 1;
            }
          }
        }
      }
      if ( v29 )
      {
        Ptr16[2 * v7] = 50;
        Ptr16[2 * v7 + 1] = Data[71];
        v12 = v7 + 1;
        Ptr16[2 * v12] = 49;
        Ptr16[2 * v12 + 1] = Data[80];
        v13 = v12 + 1;
        Ptr16[2 * v13] = 47;
        if ( *&Data[81] == *&Data[85] )
          Ptr16[2 * v13 + 1] = -2;
        else
          Ptr16[2 * v13 + 1] = *&Data[81];
        v14 = v13 + 1;
        Ptr16[2 * v14] = 48;
        if ( *&Data[72] == *&Data[76] )
          Ptr16[2 * v14 + 1] = -2;
        else
          Ptr16[2 * v14 + 1] = *&Data[72];
        v7 = v14 + 1;
      }
    }
    Ptr16[2 * v7] = 76;
    Ptr16[2 * v7 + 1] = Data[52];
    v15 = v7 + 1;
    v32 = (Data[89] & 1) == 0;
    Ptr16[2 * v15] = 80;
    Ptr16[2 * v15++ + 1] = v32;
    Ptr16[2 * v15] = 82;
    Ptr16[2 * v15 + 1] = Data[28];
    v16 = v15 + 1;
    if ( Data[28] )
    {
      if ( Data[28] == 1 )
      {
        Ptr16[2 * v16] = 81;
        Ptr16[2 * v16++ + 1] = *&Data[32];
      }
    }
    else
    {
      Ptr16[2 * v16] = 81;
      Ptr16[2 * v16++ + 1] = *&Data[34];
    }
    if ( Data[31] == 1 )
      v24 = 1000 - *&Data[29];
    else
      v24 = *&Data[29] + 1000;
    Ptr16[2 * v16] = 83;
    Ptr16[2 * v16 + 1] = v24;
    v17 = v16 + 1;
    Ptr16[2 * v17] = 98;
    Ptr16[2 * v17 + 1] = Data[100];
    v18 = v17 + 1;
    if ( Data[100] )
    {
      if ( Data[100] == 1 )
      {
        Ptr16[2 * v18] = 99;
        Ptr16[2 * v18++ + 1] = *&Data[104];
      }
    }
    else
    {
      Ptr16[2 * v18] = 99;
      Ptr16[2 * v18++ + 1] = *&Data[106];
    }
    if ( Data[103] == 1 )
      v24 = 1000 - *&Data[101];
    else
      v24 = *&Data[101] + 1000;
    Ptr16[2 * v18] = 100;
    Ptr16[2 * v18 + 1] = v24;
    v19 = v18 + 1;
    if ( Data[38] == 1 )
      v34 = 1000 - *&Data[36];
    else
      v34 = *&Data[36] + 1000;
    Ptr16[2 * v19] = 85;
    Ptr16[2 * v19 + 1] = v34;
  }
  if ( RcxValue == 1 )
  {
    ...
  }
  return Status;
}

