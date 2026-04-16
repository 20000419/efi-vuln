EFI_STATUS __fastcall SmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( !CheckInput(CommBuffer, CommBufferSize) )
  {
    if ( !*(CommBuffer + 16) )
    {
      Status = sub_17D8(*CommBuffer);
      goto _Exit;
    }
    if ( *(CommBuffer + 16) == 1 )
    {
      if ( *CommBuffer )
      {
        Status = sub_181C(**CommBuffer);
        goto _Exit;
      }
    }
    else
    {
      if ( *(CommBuffer + 16) == 2 )
      {
        Status = sub_18E0(*CommBuffer);
        goto _Exit;
      }
      if ( *(CommBuffer + 16) != 3 )
      {
        if ( *(CommBuffer + 16) == 4 )
        {
          Status = sub_1938(*CommBuffer);
        }
        else if ( *(CommBuffer + 16) == 5 )
        {
          Status = sub_198C(*(CommBuffer + 16) - 4, v5, v6);
        }
        else
        {
          Status = EFI_UNSUPPORTED;
        }
        goto _Exit;
      }
      if ( *CommBuffer )
      {
        Status = (ProprietaryProtocol3Interface->Func2)(&gGuid_0, **CommBuffer);
_Exit:
        *(CommBuffer + 3) = Status;
        return 0;
      }
    }
    Status = EFI_INVALID_PARAMETER;
    goto _Exit;
  }
  return 0;
}
//If ( *((_BYTE *)CommBuffer + 16) equal to 0x01, and pointer extracted from CommBuffer is not zero (*(_QWORD *)CommBuffer) the following code will be triggered:

__int64 __fastcall sub_181C(unsigned int CbValue)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  Value1 = 0;
  Value2 = 0;
  Flag = 0;
  if ( !(ProprietaryProtocol3Interface->Func1)(&gGuid_0, &Value1)
    && !(ProprietaryProtocol3Interface->Func3)(&gGuid_0, &Value2) )
  {
    Flag = Value1 != Value2;
  }
  Res = (ProprietaryProtocol3Interface->Func4)(&gGuid_0, CbValue);
  if ( !Res )
  {
    Res = (ProprietaryProtocol3Interface->Func6)(&gGuid_0, CbValue);
    if ( !Res && Flag )
    {
      EfiPcdProtocol = LocateEfiPcdProtocol();
      LOBYTE(Value) = 1;
      (EfiPcdProtocol->SetBool)(&gGuid, 0x40000002, Value);
    }
  }
  return Res;
}
//The pseudocode of the LocateEfiPcdProtocol function is shown below:

EFI_PCD_PROTOCOL *LocateEfiPcdProtocol()
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  result = gEfiPcdProtocol;
  if ( !gEfiPcdProtocol )
  {
    gBS->LocateProtocol(&EFI_PCD_PROTOCOL_GUID, 0, &gEfiPcdProtocol);
    return gEfiPcdProtocol;
  }
  return result;
}
