EFI_STATUS __fastcall SmiHandler_246C(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        CommBuffer *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( CommBuffer && CommBufferSize && (-(*CommBufferSize != 64) & EFI_INVALID_PARAMETER) == 0 )
  {
    Header = 'UBES';
    Error = -(CommBuffer->Header != 'UBES') & EFI_INVALID_PARAMETER;
    if ( CommBuffer->Header == 'UBES' )
    {
      if ( !CommBuffer->EnableChecks
        || !sub_40E8('UBES', Context)
        || CommBuffer->Case == 2
        || sub_324C()
        || sub_3088(CommBuffer->field_30, CommBuffer->field_28, 0i64) )
      {
        Error = 0i64;
      }
      else
      {
        Error = EFI_ACCESS_DENIED;
      }
    }
    if ( Error )
      goto _Exit;
    Case = CommBuffer->Case;
    if ( Case > 5 )
    {
      Case1 = Case - 6;
      if ( Case1 )
      {
        Case2 = Case1 - 1;
        if ( Case2 )
        {
          Case3 = Case2 - 1;
          if ( Case3 )
          {
            if ( Case3 != 1 )
            {
_Exit1:
              Error = EFI_INVALID_PARAMETER;
              goto _Exit;
            }
            // Case3 = CommBuffer->Case - 8 = 1
            // CommBuffer->Case = 9
            Res = ToCopyMemS(CommBuffer->Offset, CommBuffer->Dst, CommBuffer->DstSize);
          }
          ...
        }
        ...
      }
      ...
    }
    ...
  }
  return 0;
}
//CommBuffer->Header should be equal to 0x55424553 (UBES).If we set CommBuffer->EnableChecks to 0x00 and CommBuffer->Case to 0x09 than we will trigger the following code:

Res = ToCopyMemS(CommBuffer->Offset, CommBuffer->Dst, CommBuffer->DstSize);
//Consider the ToCopyMemS function (offset: 0x1774):

__int64 __fastcall ToCopyMemS(__int64 Offset, void *DstBuffer, unsigned int DstBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  Status = 0i64;
  if ( !DstBuffer || !DstBufferSize )
    return EFI_INVALID_PARAMETER;
  if ( gProprietaryprotocol1Located )           // Should be zero
    return (*(gProprietaryprotocol_1 + 2))(gArgs[0] + Offset);
  Func = *(gProprietaryprotocol_2 + 2);
  if ( !Func )                                  // Should be zero
  {
    CopyMemS(DstBuffer, DstBufferSize, (Offset + gArgs[0]), DstBufferSize);
    return Status;
  }
  return Func(gArgs[0] + Offset);
}
//the variable gProprietaryprotocol1Located equals 0 because the gProprietaryprotocol_1 protocol with GUID 2452b851-87b5-4225-abf6-c3819cf11256 cannot be located (it is not installed elsewhere)
//below is code from function with offset 0x27C8 that tries to locate the protocol with GUID 2452b851-87b5-4225-abf6-c3819cf11256 (ProprietaryProtocol1Guid):
    Proprietaryprotocol = 0;
    Status = gSmst->SmmLocateProtocol(&ProprietaryProtocol1Guid, 0, &gProprietaryprotocol_1);
    if ( Status )
      Status = gSmst->SmmLocateProtocol(&ProprietaryProtocol2Guid, 0, &gProprietaryprotocol_2);
    else
      gProprietaryprotocol1Located = 1;
