EFI_STATUS SwSmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    if ( *((_BYTE *)gUnknownProtocol2 + 0x19B2) )
    {
        *((_QWORD *)gUnknownProtocol2 + 0x334) = 3;
        if ( !sub_8000717C((_QWORD *)gUnknownProtocol2 + 0x71) )
        {
            (*((_QWORD *)gUnknownProtocol2 + 0x50) + 0xC0))(&unk_8000ABD0, sub_800018D8, v9);
... 
//As we can see, depending on the contents of a protocol pointed by gUnknownProtocol2 a function is invoked pointed by a value extracted from it. This protocol is located and configured during the initialization procedure in the driver.

...
gUnknownProtocol2Guid = {"c965c76a-d71e-4e66-ab06-c6230d528425"};
gEfiBootServices->LocateProtocol(&gUnknownProtocol2Guid, 0, &UnknownProtocol2);
...
