//In the function at offset 0x1068 (image sha256: 4143f3774dd14fcfc1afc3d7ee774f97e4ca556032bbc7c3133f5ba9b0045402), the child software System Management Interrupt (SWSMI) handler with the GUID 56947330-585c-4470-a95d-c55c529feb47 is registered:

if ( SmstIsNotNull() )
{
  Handle1 = 0;
  gBS_E738->InstallProtocolInterface(&Handle1, &ProprietaryProtocol_D8C0, EFI_NATIVE_INTERFACE, 0);
  gHandle = Handle;
  return gSmst_E718->SmiHandlerRegister(SmiHandler_1C10, &gSmiHandlerGuid, &DispatchHandle);
}
//Find below the decompiled SWSMI handler code:

EFI_STATUS __fastcall SmiHandler_1C10(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( CommBuffer && CommBufferSize )
  {
    if ( *CommBuffer == 1 )
    {
      Buffer = 0;
      if ( gBS_E738->LocateHandleBuffer(ByProtocol, &EFI_ATA_PASS_THRU_PROTOCOL_GUID_D660, 0, &NoHandles, &Buffer) )
      {
        Status = EFI_NOT_FOUND;
      }
      else
      {
        Buffer = 0;
        BufferSize = 0;
        v6 = gSmst_E718->SmmLocateHandle(ByProtocol, &EFI_ATA_PASS_THRU_PROTOCOL_GUID_D660, 0, &BufferSize, 0);
        Status = EFI_NOT_FOUND;
        if ( v6 )
        {
          if ( v6 == EFI_BUFFER_TOO_SMALL )
          {
            gSmst_E718->SmmAllocatePool(EfiRuntimeServicesData, BufferSize, &Buffer);
            if ( !Buffer )
            {
              Status = 0x8000000000000009;
              goto _WriteStatus;
            }
            v6 = gSmst_E718->SmmLocateHandle(
                   ByProtocol,
                   &EFI_ATA_PASS_THRU_PROTOCOL_GUID_D660,
                   0,
                   &BufferSize,
                   Buffer);
          }
          else if ( v6 != EFI_NOT_FOUND )
          {
            goto _WriteStatus;
          }
        }
        if ( v6 == EFI_NOT_FOUND )
          v7 = 0;
        else
          v7 = BufferSize >> 3;
        gSmst_E718->SmmFreePool(Buffer);
        if ( v7 == NoHandles )
          goto _SetEfiSuccessStatus;
        if ( !Handle )
        {
          Status = EFI_NOT_READY;
          goto _WriteStatus;
        }
        Status = sub_1E6C();
        if ( !Status )
        {
          Status = gBS_E738->HandleProtocol(Handle, &EFI_LOADED_IMAGE_PROTOCOL_GUID_D710, &Interface);
          if ( !Status )
          {
            Interface->Unload = sub_2C74;
            if ( !gBS_E738->LocateProtocol(&EFI_ACPI_SUPPORT_PROTOCOL_GUID_D6E0, 0, &v15) )
            {
              v8 = 0;
              do
              {
                v9 = (v15->GetAcpiTable)(v15, v8, &v16, &v18, v17);
                if ( !v9 )
                {
                  if ( *v16 == 'PCAF' )
                  {
                    v9 = EFI_ABORTED;
                    dword_E6E0 = *(v16 + 19);
                  }
                  gBS_E738->FreePool(v16);
                }
                ++v8;
              }
              while ( !v9 );
            }
          }
          goto _WriteStatus;
        }
        if ( Status == EFI_NOT_STARTED )
_SetEfiSuccessStatus:
          Status = EFI_SUCCESS;
      }
    }
    else
    {
      Status = EFI_UNSUPPORTED;
    }
_WriteStatus:
    *(CommBuffer + 1) = Status;
  }
  return 0;
}
