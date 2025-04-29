//The vulnerable module registers a child SW SMI handler with GUID 2970687c-618c-4de5-b8f9-6c7576dca83d:

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

        ...

        case 3:
          if ( *((_QWORD *)CommBuffer_1 + 3) <= 0x1000 )
          {
            Status = SmfbFunc2(
                       0,
                       *((char **)CommBuffer + 2),
                       (unsigned __int64 *)CommBuffer + 3,
                       CommBuffer + 0x20);
            goto LABEL_17;
          }
          break;


__int64 __fastcall SmfbFunc2(__int64 a1, char *addr, unsigned __int64 *size_ptr, char *dest)
{
  switch ( *(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 )
  {
    case 0:
      return sub_800027F8((__int64)gValueInitializedByUnknownProtocol1c2e4602, addr, dest, size_ptr);// SMM memory corruption
    case 1:
      return sub_80002BFC(                      // SMM memory corruption
               gValueInitializedByUnknownProtocol1c2e4602,
               addr,
               dest,
               size_ptr,
               addr);
    case 3:
      return sub_80003044(
               gValueInitializedByUnknownProtocol1c2e4602,
               addr,
               dest,
               size_ptr,
               addr);
  }
  return EFI_UNSUPPORTED;
}

MACRO_EFI __fastcall sub_800027F8(__int64 val, char *addr, char *dest, unsigned __int64 *size_ptr)
{
  if ( *(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 )
    return EFI_UNSUPPORTED;

  v8 = *((_QWORD *)gValueInitializedByUnknownProtocol1c2e4602 + 0xB);
  v9 = EFI_SUCCESS;

  counter = 0;

  v11 = *(void **)(v8 + 0x10);
  v12 = *(void **)(v8 + 8);
  v16 = *(void **)(v8 + 0x10);

  if ( !*size_ptr )
    return v9;

  while ( 1 )
  {
    if ( addr == dest || !CompareMemory(addr, dest, 1i64) )
      goto LABEL_12;
    SetMemory(v12, 1ui64, 0xAA);
    SetMemory(v11, 1ui64, 0x55);
    SetMemory(v12, 1ui64, 0xA0);
    SetMemory(addr, 1ui64, *dest);              // Write controllable byte to a controllable address

unsigned __int64 __fastcall sub_80002BFC(__int64 val, char *addr, __int64 dest, unsigned __int64 *size_ptr, __int64 addr_copy)
{
  v5 = 0;
  v8 = 0;
  if ( *size_ptr )
  {
    v9 = dest - (_QWORD)addr;
    do
    {
      SetMemory(addr, 1, 0x40);           // Write byte to a controllable address
      SetMemory(addr, 1, addr[v9]);       // Write byte to a controllable address
      SetMemory(addr, 1, 0x70);           // Write byte to a controllable address
      v10 = 0i64;
      while ( *addr_1 >= 0 )
      {
        sub_80003D5C();
        v10 += 2;
        if ( v10 >= 0x989680 )
        {
          *size_ptr = v8;
          v5 = EFI_DEVICE_ERROR;

          goto LABEL_7;
        }
      }
      ++v8;
      ++addr;
    }
    while ( v8 < *size_ptr );
  }
LABEL_7:
  SetMemory((void *)addr_copy, 1ui64, 0x50);    // Write byte to a controllable address
  SetMemory((void *)addr_copy, 1ui64, 0xFF);    // Write byte to a controllable address

  return v5;
}

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

        ...

        case 4:
          Status = SmfbFunc3(0, *((_QWORD *)CommBuffer + 2), (unsigned __int64 *)CommBuffer + 3);
__int64 __fastcall SmfbFunc3(__int64 a1, unsigned __int64 addr, unsigned __int64 *size_ptr)
{
  size = *size_ptr;
  if ( *(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 )
  {
    if ( *(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 == 1 )
    {
      if ( (_WORD)size )
      {
        result = EFI_INVALID_PARAMETER;
      }
      else
      {
        for ( counter = *size_ptr >> 16; counter; --counter )
        {
          SetMemory((void *)addr_1, 1ui64, 0x20);    // Write byte to a controllable address
          SetMemory((void *)addr_1, 1ui64, 0xD0);    // Write byte to a controllable address
          SetMemory((void *)addr_1, 1ui64, 0x70);    // Write byte to a controllable address
