EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    if ( CommBuffer && CommBufferSize )
    {
        if ( *(_QWORD *)CommBuffer == 1 )
        {
            v11 = 0;
            if ( gEfiBootServices->LocateHandleBuffer)(2, &EFI_ATA_PASS_THRU_PROTOCOL_GUID, 0, &v13, &v11) )
...
