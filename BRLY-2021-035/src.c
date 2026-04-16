EFI_STATUS __fastcall SmiHandler_168C(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        CommBuffer *CommBuffer,
        UINTN *CommBufferSize)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( CommBuffer && CommBufferSize && *CommBufferSize <= 0x2000 )
  {
    if ( CommBuffer->Case )
    {
      if ( CommBuffer->Case != 1 )
      {
        CommBuffer->Result = EFI_INVALID_PARAMETER;
        return 0i64;
      }
      Flag = 1;
    }
    else
    {
      Flag = 0;
    }
    CommBuffer->Result = sub_1738(Flag, CommBuffer->Msg, CommBuffer->MsgLen);
  }
  return 0i64;
}

//As we can see the input Communication Buffer is not validated to be outside of the SMRAM since the Communication Buffer size (*CommBufferSize) is not checked correctly (it may be 0). If attacker sets *CommBufferSize to 0, he will bypass validation implemented in PiSmmCommunicationSmm before gSmst->SmiManage call:

CommSize = (UINTN)CommunicateHeader->MessageLength;
if (!SmmIsBufferOutsideSmmValid ((UINTN)&CommunicateHeader->Data[0], CommSize)) {
  Status = EFI_SUCCESS;
  goto Done;
}

//
// Call dispatch function
//
Status = gSmst->SmiManage (
                  &CommunicateHeader->HeaderGuid,
                  NULL,
                  &CommunicateHeader->Data[0],
                  &CommSize
                  );
