//In the function at offset 0xEBC (image sha256: 4b91d7456d48b897106f97d419426840ef3c62844797b21b4c46fb4628fbae58), the child software System Management Interrupt (SWSMI) handler with the GUID 54c03d2d-5903-4dfb-88b7-fa7636be03d1 is registered:

if ( SmstIsNotNull() )
{
  Handle1 = 0;
  gBS_E738->InstallProtocolInterface(&Handle1, &ProprietaryProtocol_D8C0, EFI_NATIVE_INTERFACE, 0);
  gHandle = Handle;
  return gSmst_E718->SmiHandlerRegister(SmiHandler_1C10, &gSmiHandlerGuid, &DispatchHandle);
}

EFI_STATUS __fastcall SmiHandler_80000A14(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( !CommBuffer || !CommBufferSize )
    return 0;
  if ( *CommBuffer == 1 )
  {
    Buffer = 0;
    if ( gBS_8000C6E0->LocateHandleBuffer(
           ByProtocol,
           &EFI_ATA_PASS_THRU_PROTOCOL_GUID_8000BE10,
           0,
           &NoHandles,
           &Buffer) )
    {
      Status = EFI_NOT_FOUND;
    }
    else
    {
      gBS_8000C6E0->FreePool(Buffer);
      Buffer = 0;
      BufferSize = 0;
      v6 = gSmst_8000C718->SmmLocateHandle(
             ByProtocol,
             &EFI_ATA_PASS_THRU_PROTOCOL_GUID_8000BE10,
             0,
             &BufferSize,
             0);
      Status = EFI_NOT_FOUND;
      if ( v6 )
      {
        if ( v6 == EFI_BUFFER_TOO_SMALL )
        {
          gSmst_8000C718->SmmAllocatePool(EfiRuntimeServicesData, BufferSize, &Buffer);
          if ( !Buffer )
          {
            Status = EFI_OUT_OF_RESOURCES;
            goto _WriteStatus;
          }
          v6 = gSmst_8000C718->SmmLocateHandle(
                 ByProtocol,
                 &EFI_ATA_PASS_THRU_PROTOCOL_GUID_8000BE10,
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
      gSmst_8000C718->SmmFreePool(Buffer);
      if ( v7 == NoHandles )
        goto LABEL_18;
      if ( !Handle )
      {
        Status = EFI_NOT_READY;
        goto _WriteStatus;
      }
      Status = sub_8000082C(1, Handle);
      if ( !Status || Status == EFI_ALREADY_STARTED )
      {
        result = gBS_8000C6E0->HandleProtocol(Handle, &EFI_LOADED_IMAGE_PROTOCOL_GUID_8000BF00, &EfiLoadedImageProtocol);
        if ( result )
          return result;
        EfiLoadedImageProtocol->Unload = Unload;
        if ( !gBS_8000C6E0->LocateProtocol(&EFI_ACPI_SUPPORT_PROTOCOL_GUID_8000BE90, 0, &EfiAcpiSupport) )
        {
          v9 = 0;
          do
          {
            v10 = (EfiAcpiSupport->GetAcpiTable)(EfiAcpiSupport, v9, &Buffer, &v18, v17);
            if ( !v10 )
            {
              if ( *Buffer == 'PCAF' )
              {
                v10 = EFI_ABORTED;
                gFacpValue = *(Buffer + 19);
              }
              gBS_8000C6E0->FreePool(Buffer);
            }
            ++v9;
          }
          while ( !v10 );
        }
        goto _WriteStatus;
      }
      if ( Status == EFI_NOT_STARTED )
LABEL_18:
        Status = 0;
    }
  }
  else
  {
    Status = EFI_UNSUPPORTED;
  }
_WriteStatus:
  *(CommBuffer + 4) = Status;
  return 0;
}

EFI_STATUS __fastcall sub_8000082C(char a1, EFI_STATUS (__cdecl *a2)(EFI_ATA_PASS_THRU_PROTOCOL *This, UINT16 *Port))
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  NoHandles = 0;
  Buffer = 0;
  v4 = gBS_8000C6E0->LocateProtocol(&EFI_LEGACY_BIOS_PROTOCOL_GUID_8000BE40, 0, &EfiLegacyBiosProtocol);
  v5 = byte_8000C6A8;
  if ( !v4 )
    v5 = 1;
  byte_8000C6A8 = v5;
  if ( !a1 )
    return 0;
  if ( !gBS_8000C6E0->LocateProtocol(&EFI_SMM_RUNTIME_PROTOCOL_GUID_8000BDE0, 0, &gEfiSmmRuntimeProtocol) )
    (gEfiSmmRuntimeProtocol->Method_0)(&EFI_SMM_RUNTIME_PROTOCOL_GUID_8000BDE0, 0, &gEfiSmmRuntimeProtocol);
  result = gBS_8000C6E0->LocateHandleBuffer(
             ByProtocol,
             &EFI_ATA_PASS_THRU_PROTOCOL_GUID_8000BE10,
             0,
             &NoHandles,
             &Buffer);
  ...
  return result;
}
