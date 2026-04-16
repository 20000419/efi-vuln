// Add SMRAM range validation function
EFI_STATUS ValidateAddressNotInSmram(VOID *Address, UINTN Size) {
  EFI_STATUS Status;
  UINTN MapSize = 0;
  EFI_SMRAM_DESCRIPTOR *SmramMap = NULL;
  UINTN DescriptorCount;
  UINTN i;

  // Get SMRAM map size
  Status = gSmst->SmmGetSmramMap(&MapSize, NULL);
  if (Status != EFI_BUFFER_TOO_SMALL) {
    return EFI_DEVICE_ERROR;
  }

  // Allocate buffer for SMRAM map
  SmramMap = AllocatePool(MapSize);
  if (!SmramMap) {
    return EFI_OUT_OF_RESOURCES;
  }

  // Get SMRAM map
  Status = gSmst->SmmGetSmramMap(&MapSize, SmramMap);
  if (EFI_ERROR(Status)) {
    FreePool(SmramMap);
    return Status;
  }

  // Calculate descriptor count
  DescriptorCount = MapSize / sizeof(EFI_SMRAM_DESCRIPTOR);

  // Check if address overlaps any SMRAM region
  for (i = 0; i < DescriptorCount; i++) {
    EFI_PHYSICAL_ADDRESS RegionStart = SmramMap[i].PhysicalStart;
    EFI_PHYSICAL_ADDRESS RegionEnd = RegionStart + SmramMap[i].CpuVisibleLength;
    EFI_PHYSICAL_ADDRESS CheckStart = (EFI_PHYSICAL_ADDRESS)Address;
    EFI_PHYSICAL_ADDRESS CheckEnd = CheckStart + Size;

    if (CheckEnd > CheckStart &&      // Prevent underflow
        CheckStart < RegionEnd && 
        CheckEnd > RegionStart) {
      FreePool(SmramMap);
      return EFI_ACCESS_DENIED;
    }
  }

  FreePool(SmramMap);
  return EFI_SUCCESS;
}

// Modified SmfbFunc1 with address validation
__int64 __fastcall SmfbFunc1(__int64 a1, __int64 addr, __int64 offset, _QWORD *size_ptr, __int64 dest)
{
  const void *src = (const void *)(offset + addr);
  UINTN size = *size_ptr;
  EFI_STATUS Status;

  // Validate source address is not in SMRAM
  Status = ValidateAddressNotInSmram((VOID *)src, size);
  if (EFI_ERROR(Status)) {
    return EFI_ACCESS_DENIED;
  }

  // Validate destination address is not in SMRAM (if applicable)
  if (size && (const void *)dest != src) {
    Status = ValidateAddressNotInSmram((VOID *)dest, size);
    if (EFI_ERROR(Status)) {
      return EFI_ACCESS_DENIED;
    }
  }

  if ( *(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 == 3 )
    return sub_800031CC(size, dest, src);  // SMM memory read with validated address
  if ( *(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 > 1u )
    return EFI_UNSUPPORTED;

  if ( size && (const void *)dest != src )
    memcpy((void *)dest, src, size);  // SMM memory read with validated address

  return 0;
}
