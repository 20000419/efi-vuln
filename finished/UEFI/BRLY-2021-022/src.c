EFI_STATUS SwSmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    if ( !*((_WORD *)gSmmBuffer + 3) )
        return sub_80000D18();
... 
//As we can see, depending on the contents of a buffer allocated in SMRAM pointed by gSmmBuffer, a routine sub_80000D18() is invoked that dereferences EFI_BOOT_SERVICES pointer to call LocateProtocol():

__int64 sub_80000D18()
{
    gEfiBootServices->LocateProtocol(&EFI_SMM_RUNTIME_PROTOCOL_GUID, 0, &EfiSmmRuntimeProtocol);
  
    if ((gEfiBootServices->LocateProtocol(&UNKNOWN_PROTOCOL_3D819F77_GUID, 0, &UnknownProtocol3d819f77) & 0x8000000000000000) == 0)
    {
        *(_QWORD *)(0x10 * *((unsigned __int16 *)UnknownProtocol3d819f77 + 1) + 0x32) = sub_80001104;
        *(_DWORD *)gSmmBuffer = 'S51I';
        *((_WORD *)gSmmBuffer + 2) = *(_WORD *)UnknownProtocol3d819f77;
        *((_WORD *)gSmmBuffer + 3) = *((_WORD *)UnknownProtocol3d819f77 + 1);
        *((_QWORD *)gSmmBuffer + 2) = sub_80000B2C;
        *((_QWORD *)gSmmBuffer + 3) = sub_80001040;
  
...
