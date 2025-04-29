if ( result >= 0 )
  {
    InputPtr1 = ReadFromRegBuffer(44);
    InputPtr2 = ReadFromRegBuffer(45);
    if ( !PtrIsInsideSpecialBuffer(InputPtr1, 16i64) )
      return 32811i64;
    if ( !PtrIsInsideSpecialBuffer(InputPtr2, 32i64) )
      return 32811i64;
    Data = &InputPtr2->Data;
    if ( !ChecksVariableNamePtr(InputPtr1->VariableName) )
      return 32811i64;
    DataSize = InputPtr2->DataSize;
    if ( InputPtr2->DataSize )
    {
      if ( !PtrIsInsideSpecialBuffer(&InputPtr2->Data, DataSize) )
        return 32811i64;
    }
    VariableName = InputPtr1->VariableName;
    v6 = 0i64;
    if ( *InputPtr1->VariableName )
    {
      do
      {
        VariableName += 2;
        ++v6;
      }
      while ( *VariableName );
    }
    if ( &InputPtr1->VariableName[2 * v6 + 2] <= InputPtr2 || InputPtr1 >= (&InputPtr2->Data + InputPtr2->DataSize) )
    {
      CheckSum = 0;
      for ( i = 0i64; i < DataSize; CheckSum += v9 )
        v9 = *(Data + i++);
      if ( CheckSum + BYTE2(InputPtr2->CheckSum) )
      {
        return 32786i64;
      }
      else
      {
        Attributes = *&InputPtr2->Attributes;
        if ( !Attributes )
        {
          Attributes = 7i64;
          *&InputPtr2->Attributes = 7;
        }
        v11 = 32788i64;
        if ( gEfiSmmVariableProtocol )
        {
          v12 = (gEfiSmmVariableProtocol->SmmSetVariable)(
                  InputPtr1->VariableName,
                  InputPtr1,
                  Attributes,
                  DataSize,
                  Data);
          if ( v12 < 0 )
            return 32788i64;
          return v12;
        }
        return v11;
      }
    }
    else
    {
      return 32811i64;
    }
  }
  return result;
