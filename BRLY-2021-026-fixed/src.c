#include <Library/SmmServicesTableLib.h>

EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    EFI_STATUS Status = EFI_SUCCESS;
    
    if (CommBuffer && CommBufferSize) {
        // Validate communication buffer size
        if (*CommBufferSize < sizeof(EFI_SMM_COMMUNICATE_HEADER)) {
            Status = EFI_INVALID_PARAMETER;
        } else {
            // Verify the communication buffer is not within SMRAM
            EFI_PHYSICAL_ADDRESS BufferAddr = (EFI_PHYSICAL_ADDRESS)(UINTN)CommBuffer;
            EFI_PHYSICAL_ADDRESS BufferEnd = BufferAddr + *CommBufferSize;
            
            BOOLEAN IsInSmram = FALSE;
            EFI_SMRAM_DESCRIPTOR *Descriptor = NULL;
            UINTN DescriptorCount = 0;
            UINTN Index;
            
            // Get SMRAM descriptor table
            Status = gSmst->SmmGetSmramMap(&DescriptorCount, &Descriptor);
            if (EFI_ERROR(Status)) {
                return Status;
            }
            
            // Check each SMRAM region
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
            } else {
                // Process command only if buffer is valid
                if (*(UINT64 *)CommBuffer == 1) {
                    // Handle command 1
                } else if (*(UINT64 *)CommBuffer == 2) {
                    // Handle command 2
                } else {
                    Status = EFI_UNSUPPORTED;
                }
            }
        }
        
        // Update the status in the communication buffer if it's valid
        if (!EFI_ERROR(Status) && *CommBufferSize >= sizeof(EFI_SMM_COMMUNICATE_HEADER)) {
            ((EFI_SMM_COMMUNICATE_HEADER *)CommBuffer)->Status = Status;
        }
    }
    
    return EFI_SUCCESS;
}
