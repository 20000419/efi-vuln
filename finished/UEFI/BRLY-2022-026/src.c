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
        cmd = cmd - 1;
        // cmd = 2
        if ( cmd )
        {
          if ( cmd != 1 )
          {
LABEL_18:
            *(_QWORD *)CommBuffer = Status;
            return 0;
          }                                     // SmfbFunc3: SMM memory write
          Status = (*(UnknownProtocol297067C + 0x18))(
                     *(_QWORD *)(gBuffer + 8),
                     *((_QWORD *)CommBuffer + 2),
                     v8,
                     v9);
        }
        // cmd = 1
        else
        {                                       // SmbFunc2: SMM memory write
          Status = (*(UnknownProtocol297067C + 0x10))(
                     *(_QWORD *)(gBuffer + 8),
                     *((_QWORD *)CommBuffer + 2),
                     v8,
                     v9);
        }
      }
      else
      {
        ...
      }

      goto LABEL_18;
    }
  }

  return 0;
}
