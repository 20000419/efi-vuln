__int64 __fastcall SwSmiHandlerB2(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  EFI_STATUS Status;
  UINTN DataSize = 0x75;
  UINT8 *Data = AllocatePool(DataSize); // Assume proper allocation in SMRAM
  EFI_SMRAM_DESCRIPTOR *SmramMap;
  UINTN SmramMapSize, SmramDescriptorCount;
  UINT64 Ptr, Ptr16;
  UINTN CpuIndex;

  // Retrieve SMRAM map for validation
  Status = GetSmramMap(&SmramMapSize, &SmramMap, &SmramDescriptorCount);
  if (EFI_ERROR(Status)) return Status;

  // Existing variable retrieval logic
  Status = gEfiSmmVariableProtocol->SmmGetVariable(L"OcSetup", &gVariableGuid, &Attributes, &DataSize, Data);
  if (EFI_ERROR(Status)) return Status;
  if (!Data[39]) return Status;

  CpuIndex = (CommBuffer && CommBufferSize) ? *CommBuffer : 0xFFFFFFFFFFFFFFFF;
  if (CpuIndex == -1) return EFI_UNSUPPORTED;

  // Read CPU save state values
  Status = SmmCpuProtocol->ReadSaveState(SmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RBX, CpuIndex, &RbxValue);
  Status = SmmCpuProtocol->ReadSaveState(SmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RCX, CpuIndex, &RcxValue);
  if (EFI_ERROR(Status)) return Status;

  Ptr = RbxValue;
  Ptr16 = RbxValue + 16;

  // Validate RBX pointer is outside SMRAM
  if (IsPointerInSmram((VOID*)Ptr, DataSize, SmramMap, SmramDescriptorCount)) {
    return EFI_SECURITY_VIOLATION; // Block access to SMRAM
  }

  // Existing logic with validation added before pointer usage
  if (RcxValue >= 3) {
    // ... (existing error handling)
  } else if (!RcxValue) {
    // Check for valid magic numbers and validate buffer outside SMRAM
    if (*Ptr != '2DB$' && *Ptr != '$DB$') {
      // ... (existing error handling)
    } else {
      // Proceed only if pointer is valid and outside SMRAM
      if (*(Ptr + 4) <= v26) {
        // ... (existing logic with SMRAM-safe pointer operations)
      }
      // ... (remaining buffer operations with validated pointer)
    }
  }

  // Free resources and return
  FreePool(Data);
  return Status;
}

// Helper function to check if pointer is in SMRAM (assumed implemented)
BOOLEAN IsPointerInSmram(VOID *Buffer, UINTN Size, EFI_SMRAM_DESCRIPTOR *SmramMap, UINTN DescriptorCount) {
  UINTN i;
  VOID *End = (VOID*)((UINTN)Buffer + Size);
  for (i = 0; i < DescriptorCount; i++) {
    if ((UINTN)Buffer < SmramMap[i].PhysicalStart + SmramMap[i].PhysicalSize &&
        (UINTN)End > SmramMap[i].PhysicalStart) {
      return TRUE; // Overlaps with SMRAM
    }
  }
  return FALSE;
}
