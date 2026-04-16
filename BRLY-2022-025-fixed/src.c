// Helper function to check if address range is within SMRAM
EFI_STATUS ValidateAddressNotInSmram(VOID *Address, UINTN Size) {
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
    EFI_PHYSICAL_ADDRESS CheckStart = (EFI_PHYSICAL_ADDRESS)Address;
    EFI_PHYSICAL_ADDRESS CheckEnd = CheckStart + Size;

    // Check for overlap with any SMRAM region
    for (i = 0; i < DescriptorCount; i++) {
        EFI_PHYSICAL_ADDRESS RegionStart = SmramMap[i].PhysicalStart;
        EFI_PHYSICAL_ADDRESS RegionEnd = RegionStart + SmramMap[i].CpuVisibleLength;
        
        if (CheckStart < RegionEnd && CheckEnd > RegionStart) {
            FreePool(SmramMap);
            return EFI_ACCESS_DENIED; // Block SMRAM access
        }
    }
    
    FreePool(SmramMap);
    return EFI_SUCCESS;
}

// Fixed SmfbFunc1 with SMRAM access validation
__int64 __fastcall SmfbFunc1(__int64 a1, __int64 addr, __int64 offset, _QWORD *size_ptr, __int64 dest) {
    const void *src = (const void *)(offset + addr);
    UINTN size = *size_ptr;
    EFI_STATUS status;

    // Validate source address is NOT in SMRAM
    status = ValidateAddressNotInSmram((VOID *)src, size);
    if (EFI_ERROR(status)) return status;
    
    // Validate destination address if used (optional, based on use case)
    if (dest && size) {
        status = ValidateAddressNotInSmram((VOID *)dest, size);
        if (EFI_ERROR(status)) return status;
    }

    if (*(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 == 3)
        return sub_800031CC(size, dest, src);
    if (*(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 > 1u)
        return EFI_UNSUPPORTED;

    if (size && (const void *)dest != src) {
        // Perform copy only after validation
        memcpy((void *)dest, src, size);
    }

    return 0;
}

// Updated SMI handler with argument validation (cmd=0 case)
EFI_STATUS __fastcall SmiHandler(...) {
    // ... existing parameter checks ...
    
    if (cmd == 0) {
        __int64 addr = *((_QWORD *)CommBuffer + 2);
        UINTN size = *((_QWORD *)CommBuffer + 3);
        __int64 dest = (char *)CommBuffer + 0x20;
        
        // Pre-validate address range before calling SmfbFunc1
        if (ValidateAddressNotInSmram((VOID *)(offset + addr), size) != EFI_SUCCESS) {
            Status = EFI_ACCESS_DENIED;
            goto LABEL_18;
        }
        
        Status = (*(UnknownProtocol297067C + 8))(
            *(_QWORD *)(gBuffer + 8),
            addr,
            0,
            dest,
            (char *)CommBuffer + 0x28
        );
    }
    
    // ...
}
