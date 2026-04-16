#include <Library/SmmServicesTableLib.h>
#include <Protocol/AtaPassThru.h>

// Global variable to store the protocol instances during driver initialization
STATIC EFI_HANDLE *gAtaPassThruHandles = NULL;
STATIC UINTN gAtaPassThruHandleCount = 0;

// Initialization function to be called during driver entry
EFI_STATUS InitializeAtaPassThruProtocol(void)
{
    EFI_STATUS Status;
    
    // Use Boot Services only during initialization
    Status = gBS->LocateHandleBuffer(
        ByProtocol,
        &gEfiAtaPassThruProtocolGuid,
        NULL,
        &gAtaPassThruHandleCount,
        &gAtaPassThruHandles
    );
    
    return Status;
}

// Cleanup function to be called during driver unload
VOID CleanupAtaPassThruProtocol(void)
{
    if (gAtaPassThruHandles != NULL) {
        gSmst->SmmFreePool(gAtaPassThruHandles);
        gAtaPassThruHandles = NULL;
        gAtaPassThruHandleCount = 0;
    }
}

EFI_STATUS SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    EFI_STATUS Status = EFI_SUCCESS;
    
    if (CommBuffer && CommBufferSize) {
        if (*(UINT64 *)CommBuffer == 1) {
            // Use the pre-fetched protocol handles instead of calling Boot Services
            if (gAtaPassThruHandles != NULL && gAtaPassThruHandleCount > 0) {
                // Process using the stored handles
                // Example:
                // for (UINTN i = 0; i < gAtaPassThruHandleCount; i++) {
                //     EFI_ATA_PASS_THRU_PROTOCOL *AtaPassThru;
                //     Status = gSmst->SmmHandleProtocol(
                //         gAtaPassThruHandles[i],
                //         &gEfiAtaPassThruProtocolGuid,
                //         (VOID **)&AtaPassThru
                //     );
                //     // Process the protocol
                // }
            } else {
                Status = EFI_NOT_FOUND;
            }
        } else {
            Status = EFI_UNSUPPORTED;
        }
        
        // Update the status in the communication buffer
        if (!EFI_ERROR(Status) && *CommBufferSize >= sizeof(EFI_SMM_COMMUNICATE_HEADER)) {
            ((EFI_SMM_COMMUNICATE_HEADER *)CommBuffer)->Status = Status;
        }
    }
    
    return EFI_SUCCESS;
}
