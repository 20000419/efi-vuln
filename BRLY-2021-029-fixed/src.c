#include <Library/SmmServicesTableLib.h>

EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize) {
    EFI_STATUS Status = EFI_SUCCESS;
    if (CommBuffer && CommBufferSize) {
        if (*CommBufferSize < sizeof(EFI_SMM_COMMUNICATE_HEADER)) {
            Status = EFI_INVALID_PARAMETER;
        } else {
            EFI_PHYSICAL_ADDRESS BufferAddr = (EFI_PHYSICAL_ADDRESS)(UINTN)CommBuffer;
            EFI_PHYSICAL_ADDRESS BufferEnd = BufferAddr + *CommBufferSize;
            EFI_SMRAM_DESCRIPTOR *Descriptor = NULL;
            UINTN DescriptorCount = 0;
            UINTN Index;
            BOOLEAN IsInSmram = FALSE;
            
            if (EFI_ERROR(gSmst->SmmGetSmramMap(&DescriptorCount, &Descriptor))) return EFI_UNSUPPORTED;
            
            for (Index = 0; Index < DescriptorCount; Index++) {
                EFI_PHYSICAL_ADDRESS SmramBase = Descriptor[Index].PhysicalStart;
                EFI_PHYSICAL_ADDRESS SmramEnd = SmramBase + Descriptor[Index].RegionLength;
                if ((BufferAddr >= SmramBase && BufferAddr < SmramEnd) || (BufferEnd > SmramBase && BufferEnd <= SmramEnd)) {
                    IsInSmram = TRUE;
                    break;
                }
            }
            
            if (IsInSmram) {
                Status = EFI_SECURITY_VIOLATION;
            } else {
                UINT64 command = *(UINT64 *)CommBuffer;
                if (command != 1) {
                    if (command == 2) {
                        // 处理命令2的逻辑
                    }
                    if (command != 3) goto LABEL_43;
                }
                // 处理命令1和3的逻辑
                Status = EFI_SUCCESS;
            }
        }
        LABEL_43:;
        ((EFI_SMM_COMMUNICATE_HEADER *)CommBuffer)->Status = Status;
    }
    return EFI_SUCCESS;
}
