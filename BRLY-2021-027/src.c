EFI_STATUS SwSmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    ...

    input = ReadSaveSate(EFI_SMM_SAVE_STATE_REGISTER_RAX);
    counter = 0;
    if ( gFuncsArray[0] )
    {
        offset = 0;
        while ( BYTE1(input) != (__int64)SLODWORD(gIndexArray[offset]) )
        {
            offset = 2 * ++counter;
            if ( !gIndexArray[2 * counter + 1] )
                goto LABEL_12;
        }
        v7 = gFuncsArray[2 * counter])(2 * counter, offset * 8, 0x8000000000000003);

...
//As we can see, the input for this SW SMI handler is passed using CPU Save State. The contents of RAX register allows a handler's caller to choose the function for invoking from an array gFuncsArray:

.data:00000000800113E8 gFuncsArray     dq offset Func0
.data:00000000800113F0                 dq 1
.data:00000000800113F8                 dq offset Func1
.data:0000000080011400                 dq 2
.data:0000000080011408                 dq offset Func2
//Let's look at Func0() for example located at 0x3848 in the driver:

__int64 Func0()
{
    v0 = ReadSaveSate(EFI_SMM_SAVE_STATE_REGISTER_RBX);
    ptr = ReadSaveSate(EFI_SMM_SAVE_STATE_REGISTER_RSI);
    LOBYTE(v2) = 1;
    
    if ( v0 != sub_80009F6C((__int64)&stru_80011078, v2) + 40 || *(_DWORD *)(ptr + 8) != 'AFMS' )
        return 0x8000000000000003ui64;
    
    result = (*(_QWORD *)(gSmmBuffer + 8) + 8))(*(_QWORD *)(gSmmBuffer + 8), *(_QWORD *)(ptr + 0x10), 0, ptr + 0x20, ptr + 0x28);
    
    *(_QWORD *)ptr = result;
    
    return result;
}
