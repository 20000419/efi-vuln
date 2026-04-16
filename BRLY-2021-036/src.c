EEFI_STATUS __fastcall SmiHandler_1CA4(
        EFI_HANDLE DispatchHandle,
        const void *BufferSize,
        CommBufferStruct *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( CommBuffer && CommBufferSize && (-(*CommBufferSize != 28) & 0x8000000000000002) == 0 )
  {
    if ( !CommBuffer->BufferPtr )
      goto _Exit;
    p_BufferSize = &CommBuffer->BufferSize;
    Size = *&CommBuffer->BufferSize;
    if ( !Size )
      goto _Exit;
    Res = SmmIsBufferOutsideSmmValid(CommBuffer->BufferPtr, Size);
    Status = -(Res == 0) & EFI_SECURITY_VIOLATION;
    if ( Res )
    {
      Res1 = 0;
      if ( p_BufferSize )
        Res1 = SmmIsBufferOutsideSmmValid(p_BufferSize, 8);
      Status = -(Res1 == 0) & EFI_SECURITY_VIOLATION;
    }
    if ( !Status )
    {
_Exit:
      BufferPtr = CommBuffer->BufferPtr;
      if ( CommBuffer->Case == 1 )
        Status1 = sub_1A48(BufferPtr);
      else
        // Vulnerability here
        Status1 = sub_1AB8(BufferPtr);
      Status = Status1;
    }
    CommBuffer->Status = Status;
  }
  return 0i64;
}

EFI_STATUS __fastcall sub_1AB8(__int64 BufferPtr)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  Status = EFI_INVALID_PARAMETER;
  if ( BufferPtr )
  {
    AllocatedBuffer = SmmAllocatePool(BufferPtr, 0x30);
    if ( AllocatedBuffer )
    {
      Buffer = ZeroMem(AllocatedBuffer, 0x30);
      if ( Buffer )
      {
        // Always return 0
        Status = sub_1F20(&v7);
        if ( !Status )
        {
          *(_DWORD *)(BufferPtr + 21) = v7;
          *(_WORD *)(BufferPtr + 25) = v8;
          *(_BYTE *)(BufferPtr + 27) = v9;
          CopyMem48BytesMax(Buffer, v5, BufferPtr + 20, *(unsigned __int16 *)(BufferPtr + 2));
        }
        if ( !Status )
          Status = sub_1A48(Buffer);
        Free(Buffer);
      }
    }
  }
  return Status;
}
