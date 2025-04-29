__int64 __fastcall Deref1(__int64 Address)
{
  return *Address;
}
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
            Status = gSmst_0->SmmUninstallProtocolInterface(
                       *(Ptr - 136),
                       &EFI_STORAGE_SECURITY_COMMAND_PROTOCOL_GUID,
                       (Ptr - 88));
            if ( Status >= 0 )
            {
              Status = gSmst_0->SmmUninstallProtocolInterface(*(Ptr - 136), &EFI_DEVICE_PATH_PROTOCOL_GUID, *(Ptr - 56));
              if ( Status >= 0 )
                *(Ptr + 16) = 0; // unchecked write (SMRAM corruption)
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
