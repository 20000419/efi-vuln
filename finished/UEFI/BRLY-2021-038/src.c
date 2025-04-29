EFI_STATUS __fastcall SmiHandler_19A0(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  ...
  // size not validated, we can allocate small buffer, then write out of bounds
  CommBufferCopy = (unsigned __int64 *)GetCopy(*CommBufferSize, CommBuffer);
  if ( CommBufferCopy )
  {
    ...
    *((_QWORD *)CommBufferCopy + 2) = Status;     // OOB write
    CopyMemS(CommBuffer, *CommBufferSize, CommBufferCopy, *CommBufferSize);
    Clear(&CommBufferCopy1, *CommBufferSize);
  }
  return 0;
}
//GetCopy will allocate a buffer of size *CommBufferSize and copy the contents of the CommBuffer into this buffer:

void *__fastcall GetCopy(UINTN Size, const void *Buffer)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  result = AllocatePool(Size); // gSmst->SmmAllocatePool wrapper
  if ( result && Size && result != Buffer )
    return CopyMem(result, Buffer, Size);
  return result;
}
