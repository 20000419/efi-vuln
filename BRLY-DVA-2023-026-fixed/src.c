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
  EFI_SMRAM_DESCRIPTOR *SmramMap;
  UINTN SmramMapSize;
  UINTN SmramCount;
  UINTN j;

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
    
    // Get SMRAM map for pointer checks
    SmramMapSize = 0;
    gSmst_0->SmmGetSmramMap(&SmramMapSize, NULL);
    SmramMap = AllocatePool(SmramMapSize);
    if (!SmramMap) {
      Status = EFI_OUT_OF_RESOURCES;
      goto _ExitSmramMap;
    }
    if (gSmst_0->SmmGetSmramMap(&SmramMapSize, SmramMap) != EFI_SUCCESS) {
      FreePool(SmramMap);
      Status = EFI_UNSUPPORTED;
      goto _Exit;
    }
    SmramCount = SmramMapSize / sizeof(EFI_SMRAM_DESCRIPTOR);

    for ( i = *Ptr2; i != Ptr2; i = *i )
    {
      // Check each write target against SMRAM
      for (j = 0; j < SmramCount; j++) {
        UINT64 TargetAddr24 = (UINT64)i + 24 * sizeof(_QWORD);
        UINT64 TargetAddr4 = (UINT64)i + 4 * sizeof(_QWORD);
        UINT64 TargetAddr6 = (UINT64)i + 6 * sizeof(_QWORD);
        
        if ( (TargetAddr24 >= SmramMap[j].PhysicalStart && TargetAddr24 < SmramMap[j].PhysicalStart + SmramMap[j].RegionLength) ||
             (TargetAddr4 >= SmramMap[j].PhysicalStart && TargetAddr4 < SmramMap[j].PhysicalStart + SmramMap[j].RegionLength) ||
             (TargetAddr6 >= SmramMap[j].PhysicalStart && TargetAddr6 < SmramMap[j].PhysicalStart + SmramMap[j].RegionLength) ) {
          FreePool(SmramMap);
          return EFI_ACCESS_DENIED; // SMRAM write attempt detected
        }
      }
      
      i[24] = 0;
      i[4] = 0;
      i[6] = 0;
    }
    FreePool(SmramMap); // Free after loop
    
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
                  // Re-get SMRAM map for new pointer checks
                  SmramMapSize = 0;
                  gSmst_0->SmmGetSmramMap(&SmramMapSize, NULL);
                  SmramMap = AllocatePool(SmramMapSize);
                  if (SmramMap && gSmst_0->SmmGetSmramMap(&SmramMapSize, SmramMap) == EFI_SUCCESS) {
                    SmramCount = SmramMapSize / sizeof(EFI_SMRAM_DESCRIPTOR);
                    for (j = 0; j < SmramCount; j++) {
                      UINT64 TargetAddr24 = (UINT64)Address + 24 * sizeof(_QWORD);
                      UINT64 TargetAddr4 = (UINT64)Address + 4 * sizeof(_QWORD);
                      UINT64 TargetAddr6 = (UINT64)Address + 6 * sizeof(_QWORD);
                      
                      if ( (TargetAddr24 >= SmramMap[j].PhysicalStart && TargetAddr24 < SmramMap[j].PhysicalStart + SmramMap[j].RegionLength) ||
                           (TargetAddr4 >= SmramMap[j].PhysicalStart && TargetAddr4 < SmramMap[j].PhysicalStart + SmramMap[j].RegionLength) ||
                           (TargetAddr6 >= SmramMap[j].PhysicalStart && TargetAddr6 < SmramMap[j].PhysicalStart + SmramMap[j].RegionLength) ) {
                        FreePool(SmramMap);
                        Status = EFI_ACCESS_DENIED;
                        goto _ExitSmramMap2;
                      }
                    }
                    FreePool(SmramMap);
                  } else {
                    FreePool(SmramMap);
                    Status = EFI_UNSUPPORTED;
                    goto _Exit;
                  }
                  
                  Address[24] = v9[v11];
                  Address[4] = v9[v11];
                  Address[6] = EfiStorageSecurityCommandProtocol;
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
        {
          // Check before calling sub_5B7C which contains additional writes
          SmramMapSize = 0;
          gSmst_0->SmmGetSmramMap(&SmramMapSize, NULL);
          SmramMap = AllocatePool(SmramMapSize);
          if (SmramMap && gSmst_0->SmmGetSmramMap(&SmramMapSize, SmramMap) == EFI_SUCCESS) {
            SmramCount = SmramMapSize / sizeof(EFI_SMRAM_DESCRIPTOR);
            __int64 CtrlPtr1 = gWpdhBuffer ? gWpdhBuffer : *(CommBuffer[22] + 176 + 16); // Approximation of sub_5B7C pointer logic
            for (j = 0; j < SmramCount; j++) {
              // Example check for common write targets in sub_5B7C
              UINT64 TargetAddr = (UINT64)CtrlPtr1;
              if (TargetAddr >= SmramMap[j].PhysicalStart && TargetAddr < SmramMap[j].PhysicalStart + SmramMap[j].RegionLength) {
                FreePool(SmramMap);
                return EFI_ACCESS_DENIED;
              }
            }
            FreePool(SmramMap);
          }
          sub_5B7C(WpdhStructure);
        }
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

__int64 __fastcall sub_5B7C(__int64 WpdhStructure)
{
    __int64 v1; // rax
    __int64 v2; // rdi
    __int64 CtrlPtr1; // rdx
    __int64 CtrlPtr2; // rcx
    __int64 result; // rax
    __int64 v7; // rcx
    EFI_HANDLE Handle; // [rsp+30h] [rbp+8h] BYREF
    EFI_SMRAM_DESCRIPTOR *SmramMap;
    UINTN SmramMapSize;
    UINTN SmramCount;
    UINTN j;

    v1 = *(WpdhStructure + 160);
    v2 = 0;
    if ( !v1 || !*(WpdhStructure + 184) )
        return EFI_NOT_READY;
    
    // SMRAM check before pointer dereferences
    SmramMapSize = 0;
    gSmst_0->SmmGetSmramMap(&SmramMapSize, NULL);
    SmramMap = AllocatePool(SmramMapSize);
    if (!SmramMap || gSmst_0->SmmGetSmramMap(&SmramMapSize, SmramMap) != EFI_SUCCESS) {
        FreePool(SmramMap);
        return EFI_UNSUPPORTED;
    }
    SmramCount = SmramMapSize / sizeof(EFI_SMRAM_DESCRIPTOR);

    CtrlPtr1 = gWpdhBuffer;
    if ( !gWpdhBuffer )
    {
        CtrlPtr2 = *(WpdhStructure + 176);
        // Check CtrlPtr2 and derived addresses
        for (j = 0; j < SmramCount; j++) {
            UINT64 CtrlPtr2Addr = (UINT64)CtrlPtr2;
            UINT64 CtrlPtr1Addr = (UINT64)CtrlPtr1;
            if ( (CtrlPtr2Addr >= SmramMap[j].PhysicalStart && CtrlPtr2Addr < SmramMap[j].PhysicalStart + SmramMap[j].RegionLength) ||
                 (CtrlPtr1Addr >= SmramMap[j].PhysicalStart && CtrlPtr1Addr < SmramMap[j].PhysicalStart + SmramMap[j].RegionLength) ) {
                FreePool(SmramMap);
                return EFI_ACCESS_DENIED;
            }
        }
        // ... existing logic ...
    } else {
        // Check existing CtrlPtr1 against SMRAM
        for (j = 0; j < SmramCount; j++) {
            UINT64 CtrlPtr1Addr = (UINT64)CtrlPtr1;
            if (CtrlPtr1Addr >= SmramMap[j].PhysicalStart && CtrlPtr1Addr < SmramMap[j].PhysicalStart + SmramMap[j].RegionLength) {
                FreePool(SmramMap);
                return EFI_ACCESS_DENIED;
            }
        }
    }

    // ... existing write operations ...
    
    FreePool(SmramMap);
    // ... rest of the function ...
}
