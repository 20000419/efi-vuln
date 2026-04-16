EFI_STATUS __fastcall SmiHandler_1988(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  if (CommBuffer && CommBufferSize)
  {
    if (*(_DWORD *)CommBuffer == 'DFCH')
    {
      EFI_SMM_SYSTEM_TABLE2 *SmmST = NULL;
      EFI_SMM_SW_DISPATCH2_PROTOCOL *SwDispatch = NULL;
      EFI_STATUS Status;
      
      // Retrieve SMM System Table
      Status = EfiGetSystemConfigurationTable(&gEfiSmmSystemTable2Guid, (VOID**)&SmmST);
      if (EFI_ERROR(Status) || !SmmST)
        return Status;
      
      // Allocate SMRAM buffer using SMM Memory Allocation Protocol
      Status = SmmST->SmmAllocatePool(EfiRuntimeServicesData, 175 * BlocksNum, &DstBuffer);
      if (EFI_ERROR(Status))
        return Status;
      
      Size = 175 * BlocksNum;
      *((_QWORD *)CommBuffer + 1) = BlocksNum;
      
      if (DstBuffer && Size && gSrcBuffer && DstBuffer != gSrcBuffer)
        CopyMem(DstBuffer, (const __m128i *)gSrcBuffer, Size);
    }
  }
  return EFI_SUCCESS;
}
