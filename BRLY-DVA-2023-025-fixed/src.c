EFI_STATUS __fastcall ChildSwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        _QWORD *CommBuffer,
        UINTN *CommBufferSize)
{
  __int64 v4; // r13
  __int64 NestedPtr; // rsi
  __int64 Status; // rbx
  __int64 Ptr; // rdi
  bool Res; // al
  UINTN v10; // rdi
  unsigned __int8 v11; // r12
  __int64 v12; // rax
  EFI_STORAGE_SECURITY_SEND_DATA *p_SendData; // r14
  __int64 i; // rax
  __int64 v15; // rbx
  EFI_STORAGE_SECURITY_COMMAND_PROTOCOL *EfiStorageSecurityCommandProtocol; // [rsp+30h] [rbp-10h] BYREF
  void *Buffer; // [rsp+90h] [rbp+50h] BYREF
  UINTN BufferSize; // [rsp+98h] [rbp+58h] BYREF
  EFI_SMRAM_DESCRIPTOR *SmramMap;
  UINTN SmramMapSize;
  UINTN SmramCount;
  UINTN j;
  bool IsInSmram;

  BufferSize = 0;
  v4 = 0;
  Buffer = 0;
  if ( gUnknownProtocol == CommBuffer && *CommBufferSize == 31 && CommBuffer )
  {
    NestedPtr = CommBuffer[2];
    gGlobalPtr1 = *(NestedPtr - 16);
    gGlobalPtr2 = *(NestedPtr - 8);
    if ( *CommBuffer == 1 )
    {
      Status = Command1(*(NestedPtr + 16), 1, NestedPtr);
      goto _Exit;
    }
    if ( *CommBuffer != 2 )
    {
      if ( *CommBuffer == 3 )
      {
        Ptr = Deref1(NestedPtr);
        Res = Compare(NestedPtr, Ptr);
        Status = Buffer;
        while ( !Res )
        {
          if ( *(Ptr + 16) )
          {
            // Check if target address is within SMRAM
            SmramMapSize = 0;
            gSmst_0->SmmGetSmramMap(&SmramMapSize, NULL);
            SmramMap = AllocatePool(SmramMapSize);
            if (SmramMap) {
              if (gSmst_0->SmmGetSmramMap(&SmramMapSize, SmramMap) == EFI_SUCCESS) {
                IsInSmram = FALSE;
                SmramCount = SmramMapSize / sizeof(EFI_SMRAM_DESCRIPTOR);
                for (j = 0; j < SmramCount; j++) {
                  UINT64 TargetAddr = (UINT64)(Ptr + 16);
                  UINT64 SmramStart = SmramMap[j].PhysicalStart;
                  UINT64 SmramEnd = SmramStart + SmramMap[j].RegionLength;
                  if (TargetAddr >= SmramStart && TargetAddr < SmramEnd) {
                    IsInSmram = TRUE;
                    break;
                  }
                }
                if (!IsInSmram) {
                  Status = gSmst_0->SmmUninstallProtocolInterface(
                             *(Ptr - 136),
                             &EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID,
                             (Ptr - 88));
                  if (Status >= 0) {
                    Status = gSmst_0->SmmUninstallProtocolInterface(*(Ptr - 136), &EFI_DEVICE_PATH_PROTOCOL_GUID, *(Ptr - 56));
                    if (Status >= 0)
                      *(Ptr + 16) = 0; // Only write if not in SMRAM
                  }
                } else {
                  Status = EFI_ACCESS_DENIED; // Deny write to SMRAM
                }
                FreePool(SmramMap);
              } else {
                FreePool(SmramMap);
                Status = EFI_UNSUPPORTED;
              }
            } else {
              Status = EFI_OUT_OF_RESOURCES;
            }
          }
          Ptr = Deref2(NestedPtr, Ptr);
          Res = Compare(NestedPtr, Ptr);
        }
      }
      else
      {
        Status = EFI_UNSUPPORTED;
      }
      goto _Exit;
    }
    ...
_Exit:
    CommBuffer[1] = Status;
  }
  return EFI_SUCCESS;
}
