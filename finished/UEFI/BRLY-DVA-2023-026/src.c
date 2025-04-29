EFI_STATUS __fastcall ChildSwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        _QWORD *CommBuffer,
        UINTN *CommBufferSize)
{
  char *WpdhStructure; // rbp
  EFI_STATUS Status; // rbx
  _QWORD *Ptr2; // rcx
  _QWORD *i; // rax
  EFI_HANDLE *v9; // rdi
  EFI_HANDLE *Buffer; // rax
  UINTN v11; // r12
  UINTN v12; // r13
  _QWORD *Address; // r14
  __int64 v14; // r15
  EFI_DEVICE_PATH_PROTOCOL *v15; // rbx
  __int64 Ptr1; // [rsp+30h] [rbp-48h]
  EFI_DEVICE_PATH_PROTOCOL *EfiDevicePathProtocol; // [rsp+38h] [rbp-40h] BYREF
  void *EfiStorageSecurityCommandProtocol; // [rsp+40h] [rbp-38h] BYREF
  UINTN BufferSize; // [rsp+90h] [rbp+18h] BYREF

  if ( !CommBuffer || !CommBufferSize )
    return EFI_SUCCESS;
  if ( CommBuffer != (gBuffer + 24) )
    return EFI_ACCESS_DENIED;
  WpdhStructure = (CommBuffer + 2);
  if ( *CommBuffer == 1 )
    goto _CheckSize;
  if ( *CommBuffer != 2 )
  {
    if ( *CommBuffer != 3 )
    {
      if ( *CommBuffer == 4 )
      {
        if ( *CommBufferSize == 17 )
        {
          gFlag = *WpdhStructure;
          goto _ExitSuccess;
        }
        return EFI_ACCESS_DENIED;
      }
_Unsupported:
      Status = EFI_UNSUPPORTED;
      goto _Exit;
    }
_CheckSize:
    if ( *CommBufferSize != 248 )
      return EFI_ACCESS_DENIED;
    Ptr2 = (CommBuffer[22] + 8);
    for ( i = *Ptr2; i != Ptr2; i = *i )
    {
      i[24] = 0;                             // unchecked write (SMRAM corruption)
      i[4] = 0;                              // unchecked write (SMRAM corruption)
      i[6] = 0;                              // unchecked write (SMRAM corruption)
    }
    if ( *WpdhStructure == 'wpdh' )
    {
      Ptr1 = CommBuffer[22];
      if ( !Ptr1 )
      {
        Status = EFI_NOT_READY;
        goto _Exit;
      }
      BufferSize = 0;
      v9 = 0;
      Status = gSmst_0->SmmLocateHandle(
                 ByProtocol,
                 &EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID,
                 0,
                 &BufferSize,
                 0);
      if ( Status == EFI_BUFFER_TOO_SMALL )
      {
        Buffer = AllocatePool(6);
        v9 = Buffer;
        if ( !Buffer )
        {
          Status = EFI_OUT_OF_RESOURCES;
          goto _Exit;
        }
        Status = gSmst_0->SmmLocateHandle(
                   ByProtocol,
                   &EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID,
                   0,
                   &BufferSize,
                   Buffer);
      }
      if ( Status )
      {
        if ( v9 )
          Free(v9);
      }
      else if ( v9 )
      {
        v11 = 0;
        v12 = BufferSize >> 3;
        if ( BufferSize >> 3 )
        {
          do
          {
            Status = gSmst_0->SmmHandleProtocol(
                       v9[v11],
                       &EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID,
                       &EfiStorageSecurityCommandProtocol);
            if ( !Status )
            {
              Status = gSmst_0->SmmHandleProtocol(v9[v11], &EFI_DEVICE_PATH_PROTOCOL_GUID, &EfiDevicePathProtocol);
              if ( !Status )
              {
                Address = *(Ptr1 + 8);
                if ( Address != (Ptr1 + 8) )
                {
                  while ( 2 )
                  {
                    v14 = Address[57];
                    v15 = EfiDevicePathProtocol;
                    while ( *v14 != 127 || *(v14 + 1) != 0xFF )
                    {
                      if ( v15->Type == 127 && v15->SubType == 0xFF )
                      {
                        if ( *v14 != 127 || *(v14 + 1) != 0xFF )
                          goto _Continue;
                        break;
                      }
                      if ( *(v14 + 2) != *v15->Length || *v15->Length && v14 != v15 && sub_1060(v14, v15, *v15->Length) )
                        goto _Continue;
                      v14 += *(v14 + 2);
                      v15 = (v15 + *v15->Length);
                    }
                    if ( v15->Type == 127 && v15->SubType == 0xFF )
                    {
                      Status = 0;
                      Address[24] = v9[v11];    // unchecked write (SMRAM corruption)
                      Address[4] = v9[v11];     // unchecked write (SMRAM corruption)
                      Address[6] = EfiStorageSecurityCommandProtocol;// unchecked write (SMRAM corruption)
                      goto _Next;
                    }
_Continue:
                    Address = *Address;
                    if ( Address != (Ptr1 + 8) )
                      continue;
                    break;
                  }
                  Status = EFI_ABORTED;
                }
              }
            }
_Next:
            ++v11;
          }
          while ( v11 < v12 );
          WpdhStructure = (CommBuffer + 2);
        }
        Free(v9);
        if ( *CommBuffer == 1 || !gWpdhBuffer )
          sub_5B7C(WpdhStructure);              // unchecked write (SMRAM corruption) inside this function
        goto _Exit;
      }
    }
    goto _Unsupported;
  }
  if ( *CommBufferSize == 16 )
  {
    if ( !gAcpiRestoreRegistration )
    {
      Status = gSmst_0->SmmRegisterProtocolNotify(
                 &ACPI_RESTORE_CALLBACK_START_PROTOCOL_GUID,
                 AcpiRestoreNotifier,
                 &gAcpiRestoreRegistration);
      goto _Exit;
    }
_ExitSuccess:
    Status = 0;
_Exit:
    CommBuffer[1] = Status;
    return 0;
  }
  return EFI_ACCESS_DENIED;
}
