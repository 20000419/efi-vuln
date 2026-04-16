#include <Library/SmmServicesTableLib.h>

EFI_STATUS __fastcall SmiHandler_246C(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    CommBuffer *CommBuffer,
    UINTN *CommBufferSize
) {
    EFI_STATUS Error = EFI_SUCCESS;
    if (!CommBuffer || !CommBufferSize || *CommBufferSize != sizeof(CommBufferStruc)) {
        Error = EFI_INVALID_PARAMETER;
        goto _Exit;
    }
    if (CommBuffer->Header != 0x55424553) {
        Error = EFI_INVALID_PARAMETER;
        goto _Exit;
    }
    if (!CommBuffer->EnableChecks && CommBuffer->Case == 9) {
        EFI_PHYSICAL_ADDRESS DstAddr = (EFI_PHYSICAL_ADDRESS)CommBuffer->Dst;
        EFI_SMRAM_DESCRIPTOR *Descriptor = NULL;
        UINTN DescriptorCount = 0;
        UINTN Index;
        BOOLEAN IsInSmram = FALSE;

        if (EFI_ERROR(gSmst->SmmGetSmramMap(&DescriptorCount, &Descriptor))) {
            Error = EFI_UNSUPPORTED;
            goto _Exit;
        }

        for (Index = 0; Index < DescriptorCount; Index++) {
            EFI_PHYSICAL_ADDRESS SmramBase = Descriptor[Index].PhysicalStart;
            EFI_PHYSICAL_ADDRESS SmramEnd = SmramBase + Descriptor[Index].RegionLength;
            if (DstAddr >= SmramBase && DstAddr < SmramEnd) {
                IsInSmram = TRUE;
                break;
            }
        }

        if (IsInSmram) {
            Error = EFI_SECURITY_VIOLATION;
            goto _Exit;
        }

        ToCopyMemS(CommBuffer->Offset, CommBuffer->Dst, CommBuffer->DstSize);
    }
_Exit:
    return Error;
}

__int64 __fastcall ToCopyMemS(__int64 Offset, void *DstBuffer, unsigned int DstBufferSize) {
    if (!DstBuffer || !DstBufferSize) return EFI_INVALID_PARAMETER;
    CopyMemS(DstBuffer, DstBufferSize, (Offset + gArgs[0]), DstBufferSize);
    return EFI_SUCCESS;
}
