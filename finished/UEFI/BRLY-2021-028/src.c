EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    if ( CommBuffer && CommBufferSize )
    {
        if ( *(_QWORD *)CommBuffer != 1 )
        {
            if ( *(_QWORD *)CommBuffer == 2 )
            {
                ...
            }
            if ( *(_QWORD *)CommBuffer != 3 )
                goto LABEL_43;
        }
        v5 = gEfiBootServices->LocateProtocol)(&UNKNOWN_PROTOCOL_9C28BE0C_GUID, 0, &v16);
...
