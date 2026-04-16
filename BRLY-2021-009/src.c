//First, let's look at the routine located at offset 0x1DD4 in the AhciBusDxe driver. Its DXE branch (code intended to be executed during DXE phase) allocates several buffers in the system memory:

if ( IsSmstFound() )
{
    // SMM branch
    ...
}
else
{
    // DXE branch
    result = gEfiBootServices->AllocatePool(EfiReservedMemoryType, 0x250, &gBuffer);
    if ( result >= 0 )
    {
        ZeroMemory((char *)gBuffer, 0x250);
        *(_QWORD *)gBuffer = 'ICHA';

        sub_8000B934((_QWORD *)gBuffer + 1);
        result = gEfiBootServices->AllocatePool(EfiReservedMemoryType, 0x190, &gBuffer2);
        if ( result >= 0 )
        {
            ZeroMemory((char *)gBuffer2, 0x190);
            *(_QWORD *)gBuffer2 = 'VEDA';

            ...

            ZeroMemory((char *)gBuffer2, 0x190);
            *(_QWORD *)gBuffer2 = 'VEDA';

            ...

            result = gEfiBootServices->AllocatePool(EfiReservedMemoryType, 0x44, &gBuffer3);
            if ( result >= 0 )
            {
                result = gEfiBootServices->AllocatePool(EfiReservedMemoryType, 0x184, &UnknownProtocol2);
                if ( result >= 0 )
                {
                  Handlea = 0i64;
                  *(_QWORD *)UnknownProtocol2 = gBuffer3;
                  *((_QWORD *)UnknownProtocol2 + 2) = gBuffer;
                  *((_QWORD *)UnknownProtocol2 + 1) = gBuffer2;

                  gEfiBootServices->InstallProtocolInterface(&Handlea, &UNKNOWN_PROTOCOL_2490595F_GUID, EFI_NATIVE_INTERFACE, UnknownProtocol2);

                  ...
}
//The SMM branch (code intended to be executed in System Management Mode) of this function extracts the pointers to these buffers and registers a child software System Management Interrupt (SWSMI) handler with GUID 56947330-585c-4470-a95d-c55c529feb47, which contains the actual vulnerability:

if ( IsSmstFound() )
{
    // SMM branch
    gEfiBootServices->LocateProtocol)(&UNKNOWN_PROTOCOL_2490595F_GUID, 0, &UnknownProtocol2);
    
    gBuffer3 = *UnknownProtocol2;
    gBuffer = *((_QWORD *)UnknownProtocol2 + 2);
    gBuffer2 = *((_QWORD *)UnknownProtocol2 + 1);

    v12 = 0i64;
    gEfiBootServices->InstallProtocolInterface(&v12, &UNKNOWN_PROTOCOL_36CBCA7D_GUID, EFI_NATIVE_INTERFACE, 0);

    result = gSmst->SmiHandlerRegister)(SmiHandler, &gSmiHandlerGuid, v17);
}
else
{
    // DXE branch
    ...
}
//The SMI handler itself is located at offset 0x2DA4 in the driver:

EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
  if ( (char *)gBuffer3 + 0x18 == CommBuffer && *CommBufferSize == 0x2C && CommBuffer )
  {
    ...

    if ( *(_QWORD *)CommBuffer == 1 )
    {
      dword_800109F0 = *((_DWORD *)CommBuffer + 4);
      sub_8000318C();
    }

...
//Obviously, an attacker can craft the Communication Buffer contents to enter the sub_8000318C() routine that starts with the following code:

for ( current_ptr = ReadQword(gBuffer + 8); !Compare(gBuffer + 8, current_ptr); current_ptr = ReadQword2(gBuffer + 8, current_ptr) )
  {
    if ( !*(_BYTE *)(current_ptr + 0x208) && *(_QWORD *)(current_ptr + 0x18) )
    {
      *(_BYTE *)(current_ptr + 0x208) = 1;
      
...
