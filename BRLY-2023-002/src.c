__int64 __fastcall AsfSecureBootChanged(EFI_EVENT Event)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  EfiAmtWrapperProtocol = 0;
  Size = 561;
  Status = gBS->LocateProtocol(&EFI_AMT_WRAPPER_PROTOCOL_GUID, 0, &EfiAmtWrapperProtocol);
  Result = Status;
  if ( Status >= 0 )
  {
    gBS->CloseEvent(Event);
    Status = gBS->LocateProtocol(&EFI_NON_VOLATILE_VARIABLE_PROTOCOL_GUID, 0, &EfiNonVolatileVariableProtocol);
    Result = Status;
    if ( Status >= 0 )
    {
      Status = gBS->LocateProtocol(&EFI_SMM_COMMUNICATION_PROTOCOL_GUID, 0, &EfiSmmCommunicationProtocol);
      Result = Status;
      if ( Status >= 0 )
      {
        Status = (*EfiNonVolatileVariableProtocol)(&CommBuffer, &CommSize);
        Result = Status;
        if ( Status >= 0 )
        {
          Status = Size;
          if ( CommSize >= Size )
          {
            Status = gBS->LocateProtocol(&EDKII_VARIABLE_LOCK_PROTOCOL_GUID, 0, &EdkiiVariableLockProtocol);
            Result = Status;
            if ( Status >= 0 )
            {
              Result = EdkiiVariableLockProtocol->RequestToLock(
                         EdkiiVariableLockProtocol,
                         L"AsfSecureBoot",
                         &ASF_SECURE_BOOT_VARIABLE_GUID);
              DataSize = 1;
              Result = CommonGetVariable(L"AsfSecureBoot", &ASF_SECURE_BOOT_VARIABLE_GUID, &DataSize, Data);
              Status = EFI_BUFFER_TOO_SMALL;
              if ( Result == EFI_BUFFER_TOO_SMALL )
              {
                Status = CommonGetVariable(L"AsfSecureBoot", &ASF_SECURE_BOOT_VARIABLE_GUID, &DataSize, Data);
                Result = Status;
              }
              if ( !Result )
              {
                // ...
              }
            }
          }
        }
      }
    }
  }
  return Status;
}
