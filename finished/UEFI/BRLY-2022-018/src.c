gSmst->SmiHandlerRegister)(SmiHandler, &UNKNOWN_PROTOCOL_2970687C_GUID, &Handle);
//Also, it installs protocol with the same GUID 2970687c-618c-4de5-b8f9-6c7576dca83d:

Buffer = (char *)AllocPoolWrapper((EFI_MEMORY_TYPE)(gSmramMap != 0i64 ? 6 : 4), 0x58ui64);
gSmfbFuncArray = Buffer;
if ( !Buffer )
  return EFI_OUT_OF_RESOURCES;

ZeroMemory(Buffer, 0x58ui64);
SmfbFuncArray = (_QWORD *)gSmfbFuncArray;

*(_DWORD *)gSmfbFuncArray = 'bfms';
byte_80006B30 = 0;
SmfbFuncArray[9] = &byte_80006B30;
SmfbFuncArray[2] = SmfbFunc0;
SmfbFuncArray[3] = SmfbFunc1;
SmfbFuncArray[4] = SmfbFunc2;
SmfbFuncArray[5] = SmfbFunc3;
SmfbFuncArray[6] = SmfbFunc4;
SmfbFuncArray[7] = SmfbFunc5;
SmfbFuncArray[8] = SmfbFunc6;

Handle = 0;
gSmst->SmmInstallProtocolInterface)(&Handle, &UNKNOWN_PROTOCOL_2970687C_GUID, 0);
//The handler is located at offset 0x19D0:

EFI_STATUS __fastcall SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
  if ( CommBuffer && CommBufferSize && !gExitBootServicesFlag2EfiEventLegacyBootFlag )
  {

    ...

    v6 = (char *) gUnknownProtocol74d936fa;

    ...

    if ( *CommBufferSize == qword_80006B20 - 24 && CommBuffer == v6 + 0x18 )
    {
      switch ( *(_QWORD *)CommBuffer )
      {
        case 2:
          if ( *((_QWORD *)CommBuffer + 3) <= 0x1000 )
          {
            v7 = SmfbFunc1(
                   0,
                   *((_QWORD *)CommBuffer + 2),
                   0,
                   (_QWORD *)CommBuffer + 3,
                   (__int64)(CommBuffer + 0x20));
            goto LABEL_17;
          }
          break;

__int64 __fastcall SmfbFunc1(__int64 a1, __int64 addr, __int64 offset, _QWORD *size_ptr, __int64 dest)
{
  src = (const void *)(offset + addr);
  size = *size_ptr;

  if ( *(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 == 3 )
    return sub_800031CC(size, dest, src);  // SMM memory read from a controllable address
  if ( *(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 > 1u )
    return EFI_UNSUPPORTED;

  v7 = 0;
  if ( size && (const void *)dest != src )
    memcpy((void *)dest, src, *size_ptr);  // SMM memory read from a controllable address

  return v7;
}
