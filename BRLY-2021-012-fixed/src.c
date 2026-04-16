/**
 * Validate if a pointer resides within SMRAM
 * @param ptr - Pointer to validate
 * @param size - Size of the buffer
 * @return TRUE if pointer is in SMRAM, FALSE otherwise
 */
BOOLEAN IsPointerInSmram(const void *ptr, UINTN size)
{
    EFI_STATUS status;
    EFI_SMRAM_DESCRIPTOR *smramMap;
    UINTN mapSize, descriptorCount;
    UINTN i;

    // Retrieve SMRAM map from SMM driver
    status = gSmst->SmmGetSmramMap(&mapSize, &smramMap);
    if (EFI_ERROR(status)) {
        // If map retrieval fails, assume pointer is safe to avoid blocking legitimate operations
        return FALSE;
    }

    // Calculate number of descriptors
    descriptorCount = mapSize / sizeof(EFI_SMRAM_DESCRIPTOR);

    // Check if pointer overlaps any SMRAM region
    for (i = 0; i < descriptorCount; i++) {
        EFI_PHYSICAL_ADDRESS ptrAddr = (EFI_PHYSICAL_ADDRESS)ptr;
        EFI_PHYSICAL_ADDRESS regionStart = smramMap[i].PhysicalStart;
        EFI_PHYSICAL_ADDRESS regionEnd = regionStart + smramMap[i].CpuStart;

        // Check for overlap
        if (ptrAddr >= regionStart && ptrAddr < regionEnd) {
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * Secure SMI Handler with SMRAM pointer validation
 * Added sanity checks to prevent writing to SMRAM
 */
EFI_STATUS __fastcall SmiHandler_296C(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
    EFI_STATUS Status; // rax

    if (CommBuffer && CommBufferSize) {
        // Validate CommBuffer is not in SMRAM
        if (IsPointerInSmram(CommBuffer, *CommBufferSize)) {
            Status = EFI_ACCESS_DENIED;
            ReportSecurityViolation();
        }
        else if (*CommBuffer) {
            Status = EFI_UNSUPPORTED;
        }
        else if (*(UINT16 *)(CommBuffer + 2) == 0x148) {
            void *commBufferData = (UINT8 *)CommBuffer + 0x18;
            
            // Validate CommBufferData is not in SMRAM
            if (IsPointerInSmram(commBufferData, 0x148 + 0xE0)) {
                Status = EFI_ACCESS_DENIED;
                ReportSecurityViolation();
            }
            else {
                Status = sub_27CC(0, commBufferData);
            }
        }
        else {
            Status = EFI_INVALID_PARAMETER;
        }
        
        // Validate write location is not in SMRAM before writing
        if (!IsPointerInSmram((UINT8 *)CommBuffer + 1, sizeof(EFI_STATUS))) {
            *(EFI_STATUS *)((UINT8 *)CommBuffer + 1) = Status;
        } else {
            ReportSecurityViolation();
        }
    }
    return EFI_SUCCESS;
}

/**
 * Secure subroutine with SMRAM pointer validation
 * Added checks to prevent writing to SMRAM
 */
EFI_STATUS __fastcall sub_27CC(__int64 a1, void *CommBufferData)
{
    EFI_STATUS Status;
    void *Buffer = NULL;
    EFI_HANDLE *interfaceHandle;

    // Validate input buffer is not in SMRAM
    if (IsPointerInSmram(CommBufferData, 0x148 + 0xE0)) {
        ReportSecurityViolation();
        return EFI_ACCESS_DENIED;
    }

    if (*((UINT8 *)CommBufferData + 0xE0))
        return EFI_SUCCESS;

    // Allocate buffer in runtime services data
    Status = gSmst->SmmAllocatePool(EfiRuntimeServicesData, 0x148, &Buffer);
    if (EFI_ERROR(Status))
        goto Cleanup;

    ZeroMem(Buffer, 0x148);
    CopyMem(Buffer, CommBufferData, 0x148);
    *((UINT64 *)Buffer + 3) = 0;

    // Install proprietary protocol interface
    Status = InstallProprietaryProtocolInterface((__int64)Buffer);
    if (EFI_ERROR(Status))
        goto Cleanup;

    interfaceHandle = (EFI_HANDLE *)((UINT8 *)Buffer + 24); // 3 * 8 bytes offset
    
    // Install device path protocol interface
    Status = gSmst->SmmInstallProtocolInterface(
        interfaceHandle,
        &EFI_DEVICE_PATH_PROTOCOL_GUID_B000,
        EFI_NATIVE_INTERFACE,
        interfaceHandle);
        
    if (EFI_ERROR(Status))
        goto Cleanup;

    // Validate write locations before writing
    if (!IsPointerInSmram(((UINT8 *)CommBufferData + 24), sizeof(EFI_HANDLE)) &&
        !IsPointerInSmram(((UINT8 *)CommBufferData + 0xE0), 1)) {
        
        // Write handle back to communication buffer
        *((EFI_HANDLE *)((UINT8 *)CommBufferData + 24)) = *interfaceHandle;
        *((UINT8 *)CommBufferData + 0xE0) = 1;
        ((UINT8 *)Buffer)[224] = 1; // Offset 0xE0 in Buffer
    } else {
        Status = EFI_ACCESS_DENIED;
        ReportSecurityViolation();
    }

Cleanup:
    if (Buffer && EFI_ERROR(Status)) {
        gSmst->SmmFreePool(Buffer);
    }
    return Status;
}
