EFI_STATUS __fastcall SmiHandler_1988(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  if (CommBuffer && CommBufferSize)
  {
    if (*CommBufferSize < sizeof(EFI_SMM_COMMUNICATE_HEADER))
      return EFI_INVALID_PARAMETER;

    EFI_SMRAM_DESCRIPTOR *SmramMap;
    UINTN MapSize, DescriptorCount;
    EFI_STATUS Status = GetSmramMap(&MapSize, &SmramMap, &DescriptorCount);
    if (EFI_ERROR(Status))
      return Status;

    // Validate CommBuffer is not in SMRAM
    if (IsPointerInSmram(CommBuffer, *CommBufferSize, SmramMap, DescriptorCount))
      return EFI_ACCESS_DENIED;

    if (*(_DWORD *)CommBuffer == 'DFCH')
    {
      EFI_SMM_SYSTEM_TABLE2 *SmmST = GetSmmSystemTable();
      if (!SmmST)
        return EFI_NOT_FOUND;

      Status = SmmST->SmmAllocatePool(EfiRuntimeServicesData, 175 * BlocksNum, &DstBuffer);
      if (EFI_ERROR(Status))
        return Status;

      Size = 175 * BlocksNum;
      *((_QWORD *)CommBuffer + 1) = BlocksNum;

      // Validate gSrcBuffer is not in SMRAM
      if (gSrcBuffer && IsPointerInSmram(gSrcBuffer, Size, SmramMap, DescriptorCount))
      {
        SmmST->SmmFreePool(DstBuffer);
        return EFI_ACCESS_DENIED;
      }

      if (DstBuffer && Size && gSrcBuffer && DstBuffer != gSrcBuffer)
        CopyMem(DstBuffer, gSrcBuffer, Size);
    }
  }
  return EFI_SUCCESS;
}
