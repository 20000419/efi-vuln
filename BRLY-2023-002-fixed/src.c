__int64 __fastcall AsfSecureBootChanged(EFI_EVENT Event)
{
  EFI_AMT_WRAPPER_PROTOCOL *EfiAmtWrapperProtocol = NULL;
  EFI_NON_VOLATILE_VARIABLE_PROTOCOL *EfiNonVolatileVariableProtocol = NULL;
  EFI_SMM_COMMUNICATION_PROTOCOL *EfiSmmCommunicationProtocol = NULL;
  EDKII_VARIABLE_LOCK_PROTOCOL *EdkiiVariableLockProtocol = NULL;
  UINTN Size = 561;
  UINTN CommSize = 0;
  UINT8 *CommBuffer = NULL;
  UINTN DataSize = 0;
  UINT8 *Data = NULL;
  EFI_STATUS Status;
  EFI_STATUS Result;

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
              
              // First call to get required buffer size
              DataSize = 0;
              Status = CommonGetVariable(L"AsfSecureBoot", &ASF_SECURE_BOOT_VARIABLE_GUID, &DataSize, NULL);
              
              if (Status == EFI_BUFFER_TOO_SMALL && DataSize > 0) {
                // Allocate memory based on required size
                Data = AllocatePool(DataSize);
                if (Data != NULL) {
                  // Second call with properly sized buffer
                  Status = CommonGetVariable(L"AsfSecureBoot", &ASF_SECURE_BOOT_VARIABLE_GUID, &DataSize, Data);
                  Result = Status;
                  
                  if (!Result) {
                    // ... existing code ...
                  }
                  
                  // Free allocated memory
                  if (Data != NULL) {
                    FreePool(Data);
                  }
                } else {
                  Status = EFI_OUT_OF_RESOURCES;
                }
              }
            }
          }
        }
      }
    }
  }
  return Status;
}
