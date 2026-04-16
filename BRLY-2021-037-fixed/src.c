#include <Library/SmmServicesTableLib.h>

#define MIN_REQUIRED_BUFFER_SIZE 0x260  // 覆盖ZeroMem和最大写入操作的最小尺寸

EFI_STATUS __fastcall SmiHandler_1810(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    CommBufferStruct *CommBuffer,
    UINTN *CommBufferSize
) {
    EFI_STATUS Status = EFI_SUCCESS;
    if (!CommBuffer || !CommBufferSize || *CommBufferSize != sizeof(CommBufferStruct)) {
        Status = EFI_INVALID_PARAMETER;
        goto _Exit;
    }

    void *BufferPtr = CommBuffer->BufferPtr;
    UINTN BufferSize = CommBuffer->BufferSize;

    // 检查缓冲区大小是否小于最小要求
    if (BufferSize < MIN_REQUIRED_BUFFER_SIZE) {
        Status = EFI_INVALID_PARAMETER;
        goto _Exit;
    }

    // 验证缓冲区是否完全在SMRAM外
    EFI_PHYSICAL_ADDRESS BufferAddr = (EFI_PHYSICAL_ADDRESS)(UINTN)BufferPtr;
    EFI_PHYSICAL_ADDRESS BufferEnd = BufferAddr + BufferSize;
    EFI_SMRAM_DESCRIPTOR *Descriptor = NULL;
    UINTN DescriptorCount = 0;
    UINTN Index;
    BOOLEAN IsInSmram = FALSE;

    if (EFI_ERROR(gSmst->SmmGetSmramMap(&DescriptorCount, &Descriptor))) {
        Status = EFI_UNSUPPORTED;
        goto _Exit;
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
        Status = EFI_SECURITY_VIOLATION;
        goto _Exit;
    }

    if (LOBYTE(CommBuffer->Case) == 1) {
        Status = sub_189C(BufferPtr);
    } else {
        Status = EFI_INVALID_PARAMETER;
    }

_Exit:
    if (CommBuffer) CommBuffer->Status = Status;
    return Status;
}

EFI_STATUS __fastcall sub_189C(char *Buffer) {
    EFI_STATUS Status0 = EFI_INVALID_PARAMETER;
    if (Buffer) {
        // 确保缓冲区大小足够（已在处理程序中验证，此处可直接使用）
        ZeroMem(Buffer, 0x260);  // 在有效缓冲区范围内操作
        Status0 = EFI_SUCCESS;
        UINTN Index = 0;
        char *DstBuffer = Buffer;
        do {
            if (!DstBuffer) break;
            // 后续操作基于有效的缓冲区范围，无需重复检查
            // ... 原有逻辑 ...
            DstBuffer += 38;
            Index++;
        } while (Index < 0x10u);
    }
    return Status0;
}
