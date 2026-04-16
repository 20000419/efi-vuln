#include <Library/SmmServicesTableLib.h>

EFI_STATUS __fastcall SmiHandler_1690(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    CommBufferStruct *CommBuffer,
    UINTN *CommBufferSize
) {
    EFI_STATUS Status = EFI_UNSUPPORTED;
    if (!CommBuffer || !CommBufferSize || *CommBufferSize != sizeof(CommBufferStruct)) {
        Status = EFI_INVALID_PARAMETER;
        goto _Exit;
    }
    if (gComparePointersRes) {
        UINTN Case = CommBuffer->Case;
        if (Case == 5) {
            void *Dst = CommBuffer->Dst;
            if (Dst) {
                EFI_PHYSICAL_ADDRESS DstAddr = (EFI_PHYSICAL_ADDRESS)(UINTN)Dst;
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
                    if (DstAddr >= SmramBase && DstAddr < SmramEnd) {
                        IsInSmram = TRUE;
                        break;
                    }
                }
                
                if (IsInSmram) {
                    Status = EFI_SECURITY_VIOLATION;
                    goto _Exit;
                }
                
                UINTN DstSize = CommBuffer->DstSize;
                UINTN SrcBufferSize = *gSrcBuffer;
                if (DstSize >= SrcBufferSize) {
                    CopyMemS(Dst, DstSize, gSrcBuffer + 2, SrcBufferSize);
                    Status = EFI_SUCCESS;
                    CommBuffer->DstSize = *gSrcBuffer;
                } else {
                    Status = EFI_BUFFER_TOO_SMALL;
                }
            }
        }
    }
_Exit:
    return Status;
}
