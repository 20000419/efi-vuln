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
            if ( *(_QWORD *)CommBuffer != 3i64 )
                goto LABEL_43;
        }
        
        ...
        
        CommBuffer[1] = Status;
    }
    
    return EFI_SUCCESS;
}
