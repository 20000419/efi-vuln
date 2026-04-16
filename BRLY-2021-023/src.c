//The vulnerability exists in the child SW SMI handler registered with the GUID 1d3de7f0-0807-424f-aa69-11a54e19a46f and located at offset 0x1E0C in the driver:

EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    if ( CommBuffer && CommBufferSize )
    {
        if ( *(_QWORD *)CommBuffer == 1 )
        {
            LOBYTE(Context) = 1;
            Status = sub_80001508(*((_QWORD *)CommBuffer + 2), (char)Context);
            ...
        }
...
//As we can see in case 1 is passed as the first QWORD inside a Communication Buffer the sub_80001508() function is called. The second argument of this routine indicates whether the function is executed in SMM (from SMRAM) or not, thus the routine contains the following constructions:

EFI_STATUS sub_80001508(__int64 Pointer, char InSmm)
{
    if ( InSmm )
    {
        // usage of gSmst
        ...
    }
    else
    {
        // usage of gBS
        ...
    }
}
//Still, at least one EFI_BOOT_SERVICES dereferencing operation is left without any dependency to InSmm flag:

...

Status = InSmm
    ?
    gSmst->SmmHandleProtocol(v15, &EFI_ATA_PASS_THRU_PROTOCOL_GUID, (void **)&EfiAtaPassThruProtocol)
    :
    gEfiBootServices->HandleProtocol(v15, &EFI_ATA_PASS_THRU_PROTOCOL_GUID, (void **)&EfiAtaPassThruProtocol);
				
if ( !Status )
{
    if ( EfiAtaPassThruProtocol )
    {
        Status = gEfiBootServices->LocateHandleBuffer(ByProtocol, &EFI_DISK_INFO_PROTOCOL_GUID, 0, &v46, &v38);
        
...
