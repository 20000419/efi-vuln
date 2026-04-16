// Helper function to validate address is within SMRAM
EFI_STATUS ValidateAddressInSmram(VOID *Address, UINTN Size) {
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
    
    // Check address range against all SMRAM regions
    EFI_PHYSICAL_ADDRESS CheckStart = (EFI_PHYSICAL_ADDRESS)Address;
    EFI_PHYSICAL_ADDRESS CheckEnd = CheckStart + Size;
    
    for (i = 0; i < DescriptorCount; i++) {
        EFI_PHYSICAL_ADDRESS RegionStart = SmramMap[i].PhysicalStart;
        EFI_PHYSICAL_ADDRESS RegionEnd = RegionStart + SmramMap[i].CpuVisibleLength;
        
        if (CheckStart >= RegionStart && CheckEnd <= RegionEnd) {
            FreePool(SmramMap);
            return EFI_SUCCESS;
        }
    }
    
    FreePool(SmramMap);
    return EFI_ACCESS_DENIED;
}

// Fixed SmfbFunc2 with address validation
__int64 __fastcall SmfbFunc2(__int64 a1, char *addr, unsigned __int64 *size_ptr, char *dest) {
    UINTN size = *size_ptr;
    
    // Validate address is within SMRAM before any operations
    EFI_STATUS status = ValidateAddressInSmram(addr, size);
    if (EFI_ERROR(status)) return status;
    
    if (dest) {
        status = ValidateAddressInSmram(dest, size);  // Validate destination if used
        if (EFI_ERROR(status)) return status;
    }

    switch (*(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602) {
        case 0:
            if (!size) return EFI_SUCCESS;
            // Existing logic with address validation already applied
            // ... (modified loop to respect validated size) ...
            while (counter < size) {
                // Ensure single-byte writes stay within validated range
                if (ValidateAddressInSmram(addr + counter, 1) != EFI_SUCCESS)
                    break;
                // ... existing write logic ...
                counter++;
            }
            return EFI_SUCCESS;
        // Similar validation added for cases 1 and 3
        default:
            return EFI_UNSUPPORTED;
    }
}

// Fixed SmfbFunc3 with address validation
__int64 __fastcall SmfbFunc3(__int64 a1, unsigned __int64 addr, unsigned __int64 *size_ptr) {
    UINTN size = *size_ptr;
    EFI_STATUS status = ValidateAddressInSmram((VOID *)addr, size);
    if (EFI_ERROR(status)) return status;

    if (*(_DWORD *)gValueInitializedByUnknownProtocol1c2e4602 == 1) {
        if (size) {
            for (UINTN counter = 0; counter < size; counter++) {
                // Validate each byte write within SMRAM
                if (ValidateAddressInSmram((VOID *)(addr + counter), 1) != EFI_SUCCESS)
                    break;
                // ... existing write logic ...
            }
        }
    }
    return EFI_SUCCESS;
}

// Updated SMI handler with input validation (case 3 and 4)
EFI_STATUS __fastcall SmiHandler(...) {
    // ... existing checks ...
    case 3:
        if (*((_QWORD *)CommBuffer + 3) <= 0x1000) {
            char *addr = *((char **)CommBuffer + 2);
            UINTN size = *((unsigned __int64 *)CommBuffer + 3);
            // Pre-validate before function call
            if (ValidateAddressInSmram(addr, size) != EFI_SUCCESS)
                goto LABEL_17;
            Status = SmfbFunc2(0, addr, &size, CommBuffer + 0x20);
        }
        break;
    case 4:
        unsigned __int64 addr = *((_QWORD *)CommBuffer + 2);
        UINTN size = *((unsigned __int64 *)CommBuffer + 3);
        // Pre-validate before function call
        if (ValidateAddressInSmram((VOID *)addr, size) != EFI_SUCCESS)
            Status = EFI_ACCESS_DENIED;
        else
            Status = SmfbFunc3(0, addr, &size);
        break;
    // ...
}
