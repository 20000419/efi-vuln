EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    if ( gUnknownProtocol != CommBuffer || *CommBufferSize != 0x20 || !CommBuffer )
        return 0;
    if ( *(_QWORD *)CommBuffer != 1 )
    {
        if ( *(_QWORD *)CommBuffer != 2 )
            return 0x8000000000000003;    
            
        ...
        
        return 0;
    }
  
    gPointer = *((_QWORD *)CommBuffer + 2);
    result = sub_800014C0(DispatchHandle, Context);
...
}
//As we can see in case 1 is passed in the first QWORD inside a Communication Buffer, a pointer is extracted from it and saved to gPointer, then sub_800014C0() is invoked, where the following code is executed:

for ( i = Deref(gPointer); ; i = Deref2(gPointer, v1) )
{
    v1 = i;
    if ( CompareValues(gPointer, i) )
        break;
    v2 = *(_QWORD *)(v1 - 0x10);
    if ( !*(_BYTE *)(v1 - 8) )
    {
        if ( *(_BYTE *)(*(_QWORD *)(v2 + 0xB0) + 0x100) & 1 )
        {
            *(_QWORD *)(v1 - 0xD0) = sub_800041E8;
            *(_QWORD *)(v1 - 0xC8) = sub_800044E8;
