#include <Library/SmmServicesTableLib.h>

EFI_STATUS __fastcall SmiHandler_168C(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    CommBuffer *CommBuffer,
    UINTN *CommBufferSize
) {
    EFI_STATUS Status = EFI_SUCCESS;
    if (!CommBuffer || !CommBufferSize || *CommBufferSize < sizeof(CommBufferStruct) || *CommBufferSize > 0x2000) {
        if (CommBuffer) CommBuffer->Result = EFI_INVALID_PARAMETER;
        return Status;
    }

    EFI_PHYSICAL_ADDRESS BufferAddr = (EFI_PHYSICAL_ADDRESS)(UINTN)CommBuffer;
    EFI_PHYSICAL_ADDRESS BufferEnd = BufferAddr + *CommBufferSize;
    EFI_SMRAM_DESCRIPTOR *Descriptor = NULL;
    UINTN DescriptorCount = 0;
    UINTN Index;
    BOOLEAN IsInSmram = FALSE;

    if (EFI_ERROR(gSmst->SmmGetSmramMap(&DescriptorCount, &Descriptor))) {
        if (CommBuffer) CommBuffer->Result = EFI_UNSUPPORTED;
        return Status;
    }

    for (Index = 0; Index < DescriptorCount; Index++) {
        EFI_PHYSICAL_ADDRESS SmramBase = Descriptor[Index].PhysicalStart;
        EFI_PHYSICAL_ADDRESS SmramEnd = SmramBase + Descriptor[Index].RegionLength;
        if ((BufferAddr >= SmramBase && BufferAddr < SmramEnd) ||
            (BufferEnd > SmramBase && BufferEnd <= SmramEnd)) {
            IsInSmram = TRUE;
            break;
        }
    }

    if (IsInSmram) {
        if (CommBuffer) CommBuffer->Result = EFI_SECURITY_VIOLATION;
        return Status;
    }

    UINT32 Flag = CommBuffer->Case ? 1 : 0;
    if (CommBuffer->Case && CommBuffer->Case != 1) {
        CommBuffer->Result = EFI_INVALID_PARAMETER;
    } else {
        CommBuffer->Result = sub_1738(Flag, CommBuffer->Msg, CommBuffer->MsgLen);
    }

    return Status;
}
