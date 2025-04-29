//The vulnerable module registers a child SW SMI handler with GUID 145f21ab-d92c-4eab-ab1e-5d24b90c3c6c:

gSmst->SmiHandlerRegister)(SmiHandler, &gUnknownProtocol145F21ABGuid, &Handle);
//Also, it locates the protocol with GUID 2970687c-618c-4de5-b8f9-6c7576dca83d (implemented in SMM driver FwBlockServiceSmm GUID 74D936FA-D8BD-4633-B64D-6424BDD23D24):

gBuffer = AllocateBuffer(0x10);
  if ( gSmst->SmmLocateProtocol)(&gUnknownProtocol2970687CGuid, 0, gBuffer + 8) >= 0 )
//The handler is located at offset 0x2DC8:

EFI_STATUS __fastcall SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
  if ( !CommBuffer )
    return 0;
  if ( !CommBufferSize )
    return 0;
  CommBufferSize_val = *CommBufferSize;
  if ( *CommBufferSize != gCommBufferSize - 0x18 || CommBuffer != (char *)gCommBuffer + 0x18 )
    return 0;

  ...

  if ( *((_DWORD *)CommBuffer + 2) == 'AFMS' )
  {
    v8 = (char *)CommBuffer + 0x20;
    v9 = (char *)CommBuffer + 0x28;
    if ( *((_QWORD *)CommBuffer + 4) <= *CommBufferSize - 0x28 )
    {
      Status = EFI_UNSUPPORTED;

      cmd = *((_DWORD *)CommBuffer + 6);
      UnknownProtocol297067C = *(_QWORD *)(gBuffer + 8);    // gSmst_2->SmmLocateProtocol)(&gUnknownProtocol297067CGuid, 0, gBuffer + 8)

      if ( cmd )
      {
        ...
      }
      // cmd = 0
      else
      {                                         // SmfbFunc1: SMM memory read
        Status = (*(UnknownProtocol297067C + 8))(
                   *(_QWORD *)(gBuffer + 8),
                   *((_QWORD *)CommBuffer + 2),
                   0,
                   (char *)CommBuffer_1 + 0x20,
                   (char *)CommBuffer_1 + 0x28);
      }

      goto LABEL_18;
    }
  }
  
  return 0;
}

__int64 __fastcall SmfbFunc1(__int64 a1, __int64 addr, __int64 offset, _QWORD *size_ptr, __int64 dest)
{
  src = (const void *)(offset + addr);
  size = *size_ptr;

  if ( *(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 == 3 )
    return sub_800031CC(size, dest, src);  // SMM memory read from a controllable address
  if ( *(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 > 1u )
    return EFI_UNSUPPORTED;

  v7 = 0;
  if ( size && (const void *)dest != src )
    memcpy((void *)dest, src, *size_ptr);  // SMM memory read from a controllable address

  return v7;
}
