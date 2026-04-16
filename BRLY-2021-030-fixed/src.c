#include <Library/SmmServicesTableLib.h>

EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize) {
    EFI_STATUS Status = EFI_SUCCESS;
    if (gUnknownProtocol != CommBuffer || *CommBufferSize != 0x20 || !CommBuffer) return EFI_INVALID_PARAMETER;
    UINT64 command = *(UINT64 *)CommBuffer;
    if (command != 1 && command != 2) return EFI_UNSUPPORTED;
    
    if (command == 1) {
        UINT64 gPointerCandidate = *((UINT64 *)CommBuffer + 2);
        EFI_PHYSICAL_ADDRESS PointerAddr = (EFI_PHYSICAL_ADDRESS)gPointerCandidate;
        EFI_SMRAM_DESCRIPTOR *Descriptor = NULL;
        UINTN DescriptorCount = 0;
        UINTN Index;
        
        if (EFI_ERROR(gSmst->SmmGetSmramMap(&DescriptorCount, &Descriptor))) return EFI_UNSUPPORTED;
        
        BOOLEAN IsInSmram = FALSE;
        for (Index = 0; Index < DescriptorCount; Index++) {
            EFI_PHYSICAL_ADDRESS SmramBase = Descriptor[Index].PhysicalStart;
            EFI_PHYSICAL_ADDRESS SmramEnd = SmramBase + Descriptor[Index].RegionLength;
            if (PointerAddr >= SmramBase && PointerAddr < SmramEnd) {
                IsInSmram = TRUE;
                break;
            }
        }
        
        if (IsInSmram) return EFI_SECURITY_VIOLATION;
        
        gPointer = gPointerCandidate;
        Status = sub_800014C0(DispatchHandle, Context);
    } else {
        // 处理命令2的逻辑
    }
    
    return Status;
}
