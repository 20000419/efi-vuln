//In the function at offset 0xB94 (image sha256: a6f1c365d80a77c85964a4dd477e4986e20d296ae8744c7ef33931e24cfcbb3f), the child software System Management Interrupt (SWSMI) handler with the GUID 3779ad93-b988-43bc-91f0-3b6c6e38fadb is registered:

if ( v4 )
{
  result = gSmst_80003EB8->SmiHandlerRegister(SmiHandler_80000984, &gSmiHandlerGuid, &DispatchHandle);
  if ( result >= 0 )
  {
    Status = gSmst_80003EB8->SmmRegisterProtocolNotify(&Protocol, Function, v8);
    if ( Status < 0 )
      return Status;
    return v3;
  }
}
//Find below the decompiled SWSMI handler code:

EFI_STATUS __fastcall SmiHandler_80000984(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  CommBuffer1 = CommBuffer;
  if ( CommBuffer && CommBufferSize )
  {
    if ( *CommBuffer )
    {
      Status = EFI_UNSUPPORTED;
    }
    else if ( *(CommBuffer + 2) == 0x130 )
    {
      CommBuffer1 = CommBuffer + 0x18;
      Status = sub_800007F8(0, CommBuffer + 0x18);
    }
    else
    {
      Status = EFI_INVALID_PARAMETER;
    }
    *(CommBuffer1 + 1) = Status;
  }
  return 0;
}
//The sub_800007F8 function contains the following code snippet:

if ( !gPMTimerBlock
  // SMM callout
  && (gBS_80003E80->LocateProtocol(&EFI_ACPI_SUPPORT_PROTOCOL_GUID_80003C60, 0, &EfiAcpiSupportProtocol) & 0x8000000000000000) == 0 )
{
  Index = 0;
  do
  {
    Status = (EfiAcpiSupportProtocol->GetAcpiTable)(EfiAcpiSupportProtocol, Index, &FacpBuffer, &v14, v13);
    if ( Status >= 0 )
    {
      if ( FacpBuffer->h.Signarure == 'PCAF' )
      {
        Status = EFI_ABORTED;
        gPMTimerBlock = FacpBuffer->PMTimerBlock;
      }
      gBS_80003E80->FreePool(FacpBuffer);
    }
    ++Index;
  }
  while ( !Status );
}

