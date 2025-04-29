EFI_STATUS __fastcall SmiHandler_17C8(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        CommBufferStruct *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( CommBuffer )
  {
    if ( CommBufferSize )
    {
      Size = *CommBufferSize;
      if ( (-(*CommBufferSize != 160) & EFI_INVALID_PARAMETER) == 0 )
      {
        Res = 0;
        if ( Size )
          Res = SmmIsBufferOutsideSmmValid(CommBuffer, Size);
        if ( (-(Res == 0) & EFI_INVALID_PARAMETER) == 0 )
        {
          Status = -(CommBuffer->Sig != 'GFCU') & EFI_INVALID_PARAMETER;
          if ( CommBuffer->Sig == 'GFCU' )
          {
            if ( CommBuffer->Case == 16 )
            {
              if ( !gBufferPtr1 )
              {
                BufferPtr1 = GetCopy(120, &CommBuffer->BufferPtr1);
                BufferSize = CommBuffer->BufferSize;
                BufferPtr = CommBuffer->BufferPtr;
                gBufferPtr1 = BufferPtr1;
                // Vulnerability here
                sub_2288(BufferPtr, BufferSize);
                PcdProtocol = BsLocatePcdProtocol();
                if ( (PcdProtocol->Get8)(0x2C4) == 1 )
                  HandlerUnregister();
              }
            }
            ...
          }
          ...
        }
      }
    }
    
//If CommBuffer->Sig == 0x47464355 && CommBuffer->Case == 16 && !CommBuffer->BufferPtr1 following code will trigger:

BufferPtr1 = GetCopy(120, &CommBuffer->BufferPtr1);
BufferSize = CommBuffer->BufferSize;
BufferPtr = CommBuffer->BufferPtr;
gBufferPtr1 = BufferPtr1;
// Vulnerability here
sub_2288(BufferPtr, BufferSize);
PcdProtocol = BsLocatePcdProtocol();
if ( (PcdProtocol->Get8)(0x2C4) == 1 )
  HandlerUnregister();
//Below is the pseudocode of the sub_2288 function:

__int64 __fastcall sub_2288(__int64 Buffer, __int64 Size)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  Model = CheckFamilyAndModel();
  if ( ((Model - 12) & 0xFFFFFFFFFFFFFFFD) == 0 )
  {
    gBufferCopy = GetCopy(Size, Buffer);        // Get copy of Buffer on heap
    Copy = GetCopy(16 * (*gBufferCopy + *(gBufferCopy + 1)), gBufferCopy[1]);
    BufferCopy = gBufferCopy;
    Byte3 = *(gBufferCopy + 3);
    gBufferCopy[1] = Copy;                      // OOB Write if Size < 16
    Data = GetCopy(16 * (*(BufferCopy + 2) + Byte3), BufferCopy[2]);
    BufferCopy2 = gBufferCopy;
    goto _Exit;
  }
  if ( ((Model - 8) & 0xFFFFFFFFFFFFFFFC) == 0 && Model != 9 )
  {
    gBufferCopy1 = GetCopy(Size, Buffer);       // Get copy of Buffer on heap
    Copy1 = GetCopy(16 * (*gBufferCopy1 + *(gBufferCopy1 + 1)), gBufferCopy1[1]);
    BufferCopy1 = gBufferCopy1;
    Byte31 = *(gBufferCopy1 + 3);
    gBufferCopy1[1] = Copy1;                    // OOB Write if Size < 16
    Data = GetCopy(16 * (*(BufferCopy1 + 2) + Byte31), BufferCopy1[2]);
    BufferCopy2 = gBufferCopy1;
_Exit:
    BufferCopy2[2] = Data;                      // OOB Write if Size < 24
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
  }
  return 0;
}
