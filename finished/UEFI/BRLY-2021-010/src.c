//First, let's look at a routine located at offset 0x29C8 in the NvmExpressDxe driver. Its DXE branch (code intended to be executed during DXE phase) allocates a buffer for a protocol in the system memory:

if ( IsSmstFound() )
{
    // SMM branch
    ...
}
else
{
    // DXE branch
    result = gEfiBootServices->AllocatePool(EfiReservedMemoryType, 0x38, &gBuffer);
    if ( result >= 0 )
    {
        gCommBuffer = gBuffer;
        gCommSize = 0x38;
        
        ZeroMemory((char *)gBuffer, 0x38);
        
        ...
        
        gUnknownProtocol = (char *)gCommBuffer + 0x18;
        
        ...
              v6 = sub_80002FE8(0x38ui64);
              gCommBuffer_plus10_val = v6;
              if ( !v6 )
                return 0x8000000000000009;
              *((_QWORD *)v6 + 2) = 'IPVN';
              
              ...

              gEfiBootServices->InstallProtocolInterface((EFI_HANDLE *)&UnknownProtocolEffb22f6, &gUnknownProtocolGuid, EFI_NATIVE_INTERFACE, gUnknownProtocol);

        ...
}
//The SMM branch (code intended to be executed in System Management Mode) of this function extracts the pointer to the buffer and registers a child software System Management Interrupt (SWSMI) handler with GUID 52c78312-8edc-4233-98f2-1a1aa5e388a5, which contains the actual vulnerability:

if ( IsSmstFound() )
{
    // SMM branch
    gEfiBootServices->LocateProtocol(&gUnknownProtocolGuid, 0i64, &gUnknownProtocol);

    v7 = 0;
    gSmst->SmiHandlerRegister(SmiHandler, &gSmiHandlerGuid, &v7);
}
else
{
    // DXE branch
    ...
}
//The SMI handler itself is located at offset 0x2F90 in the driver:

EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
  if ( gUnknownProtocol == CommBuffer && *CommBufferSize == 0x20 && CommBuffer )
  {
    gCommBuffer_plus10_val = *((_QWORD *)CommBuffer + 2);
    if ( *(_QWORD *)CommBuffer == 1 )
    {
      result = sub_8000358C();
      if ( (result & 0x8000000000000000) != 0 )
        return result;
    }
    else
    {
      if ( *(_QWORD *)CommBuffer != 3 )
        return 0x8000000000000003;
      sub_80003484();
    }
  }

  return 0;
}
//Obviously, an attacker can craft the Communication Buffer contents to enter the sub_8000358C() routine that starts with the following code:

for ( ptr = ReadQword(gCommBuffer_plus10_val); ; ptr = ReadQword2(gCommBuffer_plus10_val, ptr_1) )
  {
    if ( Compare(gCommBuffer_plus10_val, ptr) )
      break;
    v2 = *(_QWORD *)(ptr - 16);
    if ( !*(_BYTE *)(ptr - 8) )
    {
      *(_QWORD *)(ptr - 0x1D0) = 04;
      if ( *(_BYTE *)(*(_QWORD *)(v2 + 192) + 256) & 1 )
      {
        *(_QWORD *)(ptr - 208) = sub_80004F70;
        *(_QWORD *)(ptr - 200) = sub_800050FC;

...
