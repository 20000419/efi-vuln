__int64 sub_800083EC()
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  Handle = 0;
  Status = gSmst_D780->SmiHandlerRegister(SmiHandler_82C4, &gSmiHandlerGuid, &DispatchHandle);
  if ( Status >= 0 )
    return gEfiBootServices->InstallProtocolInterface(&Handle, &ProprietaryProtocol_D288, EFI_NATIVE_INTERFACE, 0);
  return Status;
}
//Find below the decompiled SWSMI handler code:

EFI_STATUS __fastcall SmiHandler_82C4(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        CommBufferStruct *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  Status = EFI_SUCCESS;
  if ( !CommBuffer )
    Status = EFI_DEVICE_ERROR;
  if ( !CommBufferSize )
    Status = EFI_DEVICE_ERROR;
  CommBuffer1 = CommBuffer->byte0;
  if ( CommBuffer1 != 1 )
    return EFI_INVALID_PARAMETER;
  dword19 = CommBuffer->dword19;
  Result = sub_80009CB0(
             CommBuffer->qword9,
             CommBuffer->qword11,
             &dword19,
             CommBuffer->qword1D,
             CommBuffer->dword25,
             &v5,
             &v5 + 2);
  CommBuffer->dword1 = Result;
  CommBuffer->word7 = v5;
  CommBuffer->word5 = WORD2(v5);
  CommBuffer->dword19 = dword19;
  return 0;
}
