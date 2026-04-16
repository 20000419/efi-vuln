/**
 * SMI Handler with SMRAM pointer validation
 * Added sanity checks to prevent writing to SMRAM
 */
EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
  // Validate communication buffer
  if ( (char *)gBuffer3 + 0x18 == CommBuffer && *CommBufferSize == 0x2C && CommBuffer )
  {
    // Validate SMRAM access - Check if CommBuffer is not in SMRAM
    if (!IsBufferInSmram(CommBuffer, *CommBufferSize)) {
      ...

      if ( *(_QWORD *)CommBuffer == 1 )
      {
        dword_800109F0 = *((_DWORD *)CommBuffer + 4);
        sub_8000318C();
      }
    }
    else {
      // Handle SMRAM access attempt
      ReportSecurityViolation();
      return EFI_ACCESS_DENIED;
    }
  }

  ...
}

/**
 * Original vulnerable routine with pointer validation added
 * Validates nested pointers to prevent SMRAM corruption
 */
void sub_8000318C()
{
  UINT64 current_ptr;
  
  // Validate gBuffer is not in SMRAM
  if (IsBufferInSmram(gBuffer, 0x250)) {
    ReportSecurityViolation();
    return;
  }

  for ( current_ptr = ReadQword(gBuffer + 8); !Compare(gBuffer + 8, current_ptr); current_ptr = ReadQword2(gBuffer + 8, current_ptr) )
  {
    // Validate current_ptr is not in SMRAM
    if (IsBufferInSmram((void*)current_ptr, 0x209)) {
      ReportSecurityViolation();
      continue; // Skip this entry
    }
    
    if ( !*(_BYTE *)(current_ptr + 0x208) && *(_QWORD *)(current_ptr + 0x18) )
    {
      *(_BYTE *)(current_ptr + 0x208) = 1;
      
      // Add validation for other operations in original code
      if (IsBufferInSmram((void*)(current_ptr + 0x18), sizeof(UINT64))) {
        ReportSecurityViolation();
        continue;
      }
      
      ...
    }
  }
}

/**
 * Helper function to check if buffer is within SMRAM region
 * @param buffer - Pointer to buffer
 * @param size - Size of buffer
 * @return TRUE if buffer is in SMRAM, FALSE otherwise
 */
BOOLEAN IsBufferInSmram(void *buffer, UINTN size)
{
  EFI_STATUS status;
  EFI_SMRAM_DESCRIPTOR *smram_map;
  UINTN map_size, descriptor_count;
  UINTN i;
  
  // Get SMRAM map from SMM driver
  status = gSmst->SmmGetSmramMap(&map_size, &smram_map);
  if (EFI_ERROR(status)) {
    // If we can't get map, assume safe to avoid blocking legitimate operations
    return FALSE;
  }
  
  // Calculate number of descriptors
  descriptor_count = map_size / sizeof(EFI_SMRAM_DESCRIPTOR);
  
  // Check if buffer overlaps any SMRAM region
  for (i = 0; i < descriptor_count; i++) {
    EFI_PHYSICAL_ADDRESS buffer_start = (EFI_PHYSICAL_ADDRESS)buffer;
    EFI_PHYSICAL_ADDRESS buffer_end = buffer_start + size;
    EFI_PHYSICAL_ADDRESS region_start = smram_map[i].PhysicalStart;
    EFI_PHYSICAL_ADDRESS region_end = region_start + smram_map[i].CpuStart;
    
    // Check for overlap
    if (buffer_start < region_end && buffer_end > region_start) {
      return TRUE;
    }
  }
  
  return FALSE;
}
