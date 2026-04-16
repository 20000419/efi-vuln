/**
 * Secure SMI Handler with SMM-only service usage
 * Replaced unsafe EFI_BOOT_SERVICES calls with SMM System Table services
 */
__int64 __fastcall SmiHandler_17D4(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN NoHandles = 0;
    UINTN SourceSize = 0;
    void *Buffer = NULL;
    UINTN BufferSize = 0;
    UINTN Res = 0;

    // 1. Input parameter validation
    if (!CommBuffer || !CommBufferSize) {
        return EFI_INVALID_PARAMETER;
    }

    // 2. Check command identifier (first QWORD must be 1)
    if (*(UINT64 *)CommBuffer != 1) {
        return EFI_UNSUPPORTED;
    }

    // 3. Use SMM System Table service instead of EFI_BOOT_SERVICES
    //    Original: gBS->LocateHandleBuffer() - UNSAFE IN SMM
    //    Replaced with SmmLocateHandle() to get handle count safely
    Status = gSmst_62B0->SmmLocateHandle(
        ByProtocol,
        &EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID_5AF0,
        NULL,  // No search key
        &NoHandles,  // Output handle count (size in handles, not bytes)
        NULL   // No buffer needed for count-only query
    );
    if (EFI_ERROR(Status) && Status != EFI_NOT_FOUND) {
        return Status;
    }

    // 4. Allocate buffer using SMM memory allocation
    BufferSize = NoHandles * sizeof(EFI_HANDLE);  // Calculate required buffer size
    Status = gSmst_62B0->SmmAllocatePool(
        EfiRuntimeServicesData,  // Use SMM-managed memory
        BufferSize,
        &SourceSize
    );
    if (EFI_ERROR(Status)) {
        return EFI_OUT_OF_RESOURCES;
    }

    // 5. Retrieve handles using SMM service
    Status = gSmst_62B0->SmmLocateHandle(
        ByProtocol,
        &EFI_NVM_EXPRESS_PASS_THRU_PROTOCOL_GUID_5AF0,
        NULL,
        &NoHandles,
        SourceSize  // Pre-allocated SMM buffer
    );
    if (EFI_ERROR(Status)) {
        gSmst_62B0->SmmFreePool(SourceSize);  // Always free on error
        return Status;
    }

    // 6. Safe handle count calculation (original logic adjusted for SMM services)
    Res = Status == EFI_NOT_FOUND ? 0 : NoHandles;  // Handle count in handles, not bytes

    // 7. Free buffer using SMM service (avoid gBS->FreePool())
    gSmst_62B0->SmmFreePool(SourceSize);

    // 8. Call subroutine with SMM-safe logic (ensure sub_428() also uses SMM services)
    Status = sub_428_SmmSafe();  // Hypothetical SMM-safe version of sub_428()
    if (EFI_ERROR(Status)) {
        return Status;
    }

    return EFI_SUCCESS;
}

/**
 * SMM-safe replacement for sub_428() (example implementation)
 * Ensures no EFI_BOOT_SERVICES calls are used
 */
EFI_STATUS sub_428_SmmSafe() {
    // Use SMM services like SmmHandleProtocol() instead of gBS->HandleProtocol()
    // Example:
    /*
    EFI_STATUS Status;
    void *ProtocolInterface;
    Status = gSmst->SmmHandleProtocol(
        Handle,
        &ProtocolGuid,
        &ProtocolInterface
    );
    */
    return EFI_SUCCESS;
}


