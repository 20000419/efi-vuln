#include <Library/SmmServicesTableLib.h>

#define MIN_REQUIRED_BUFFER_SIZE 28  // 覆盖最大访问偏移量27字节

EFI_STATUS __fastcall SmiHandler_1CA4(
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

    UINTN BufferSize = CommBuffer->BufferSize;
    void *BufferPtr = CommBuffer->BufferPtr;
    
    // 检查BufferSize是否小于最小要求且存在有效指针
    if (BufferPtr && BufferSize < MIN_REQUIRED_BUFFER_SIZE) {
        Status = EFI_INVALID_PARAMETER;
        goto _Exit;
    }

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
        // 检查整个缓冲区范围是否与SMRAM重叠
        if ((BufferAddr < SmramEnd && BufferAddr + MIN_REQUIRED_BUFFER_SIZE > SmramBase) ||
            (BufferEnd > SmramBase && BufferEnd <= SmramEnd)) {
            IsInSmram = TRUE;
            break;
        }
    }

    if (IsInSmram) {
        Status = EFI_SECURITY_VIOLATION;
        goto _Exit;
    }

    if (BufferPtr) {
        if (CommBuffer->Case == 1) {
            Status = sub_1A48(BufferPtr);
        } else {
            Status = sub_1AB8(BufferPtr);
        }
    }

_Exit:
    if (CommBuffer) CommBuffer->Status = Status;
    return Status;
}

EFI_STATUS __fastcall sub_1AB8(__int64 BufferPtr) {
    EFI_STATUS Status = EFI_INVALID_PARAMETER;
    if (BufferPtr) {
        UINTN BufferSize = *((UINT32 *)((UINT8 *)BufferPtr + 8));  // 获取实际BufferSize
        if (BufferSize >= MIN_REQUIRED_BUFFER_SIZE) {  // 确保缓冲区足够大以容纳所有访问
            void *AllocatedBuffer = SmmAllocatePool(BufferSize, 0x30);
            if (AllocatedBuffer) {
                void *Buffer = ZeroMem(AllocatedBuffer, 0x30);
                if (Buffer) {
                    Status = sub_1F20(&v7);
                    if (!Status) {
                        // 确保写入位置在有效缓冲区范围内
                        if ((UINTN)BufferPtr + 27 < (UINTN)BufferPtr + BufferSize) {
                            *(_DWORD *)(BufferPtr + 21) = v7;
                            *(_WORD *)(BufferPtr + 25) = v8;
                            *(_BYTE *)(BufferPtr + 27) = v9;
                            CopyMem48BytesMax(Buffer, v5, BufferPtr + 20, *(unsigned __int16 *)(BufferPtr + 2));
                        }
                        if (!Status) Status = sub_1A48(Buffer);
                    }
                    Free(Buffer);
                }
            }
        }
    }
    return Status;
}
