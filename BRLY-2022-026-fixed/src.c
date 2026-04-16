EFI_STATUS ValidateSmramWrite(VOID *Addr, UINTN Size) {
    UINTN MapSize = 0;
    EFI_SMRAM_DESCRIPTOR *SmramMap = NULL;
    EFI_STATUS Status;
    UINTN i, DescriptorCount;

    // Get SMRAM map size
    Status = gSmst->SmmGetSmramMap(&MapSize, NULL);
    if (Status != EFI_BUFFER_TOO_SMALL) return EFI_DEVICE_ERROR;
    
    // Allocate SMRAM map buffer
    SmramMap = AllocatePool(MapSize);
    if (!SmramMap) return EFI_OUT_OF_RESOURCES;
    
    // Fetch SMRAM map
    Status = gSmst->SmmGetSmramMap(&MapSize, SmramMap);
    if (EFI_ERROR(Status)) {
        FreePool(SmramMap);
        return Status;
    }
    
    DescriptorCount = MapSize / sizeof(EFI_SMRAM_DESCRIPTOR);
    EFI_PHYSICAL_ADDRESS Start = (EFI_PHYSICAL_ADDRESS)Addr;
    EFI_PHYSICAL_ADDRESS End = Start + Size;

    // Check if entire range is within any SMRAM region
    for (i = 0; i < DescriptorCount; i++) {
        EFI_PHYSICAL_ADDRESS RegionStart = SmramMap[i].PhysicalStart;
        EFI_PHYSICAL_ADDRESS RegionEnd = RegionStart + SmramMap[i].CpuVisibleLength;
        
        if (Start >= RegionStart && End <= RegionEnd) {
            FreePool(SmramMap);
            return EFI_SUCCESS;
        }
    }
    
    FreePool(SmramMap);
    return EFI_ACCESS_DENIED; // Block invalid SMRAM writes
}

EFI_STATUS __fastcall SmiHandler(...) {
    // ... existing parameter checks ...
    
    if (cmd == 1) { // SmfbFunc2 (SMM memory write)
        __int64 addr = *((_QWORD *)CommBuffer + 2);
        UINTN size = *((_QWORD *)CommBuffer + 3);
        
        // Validate address and size before invoking protocol function
        if (ValidateSmramWrite((VOID *)addr, size) != EFI_SUCCESS) {
            Status = EFI_ACCESS_DENIED;
            goto LABEL_18;
        }
        
        Status = (*(UnknownProtocol297067C + 0x10))(
            *(_QWORD *)(gBuffer + 8),
            addr,
            (char *)CommBuffer + 0x20,
            (char *)CommBuffer + 0x28
        );
    } else if (cmd == 2) { // SmfbFunc3 (SMM memory write)
        __int64 addr = *((_QWORD *)CommBuffer + 2);
        UINTN size = *((_QWORD *)CommBuffer + 3);
        
        if (ValidateSmramWrite((VOID *)addr, size) != EFI_SUCCESS) {
            Status = EFI_ACCESS_DENIED;
            goto LABEL_18;
        }
        
        Status = (*(UnknownProtocol297067C + 0x18))(
            *(_QWORD *)(gBuffer + 8),
            addr,
            (char *)CommBuffer + 0x20,
            (char *)CommBuffer + 0x28
        );
    }
    
    // ...
}

__int64 __fastcall SmfbFunc3(__int64 a1, unsigned __int64 addr, unsigned __int64 *size_ptr) {
    UINTN size = *size_ptr;
    
    // Validate target address and size before writing
    EFI_STATUS status = ValidateSmramWrite((VOID *)addr, size);
    if (EFI_ERROR(status)) return status;
    
    if (*(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 == 1) {
        if (size > 0) {
            // Validate each byte write within SMRAM (defense-in-depth)
            for (UINTN i = 0; i < size; i++) {
                if (ValidateSmramWrite((VOID *)(addr + i), 1) != EFI_SUCCESS) break;
                // Existing write logic (e.g., SetMemory((void *)addr + i, 1, 0x20))
            }
        }
    }
    return EFI_SUCCESS;
}
