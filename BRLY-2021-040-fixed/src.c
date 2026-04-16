#include <Library/SmmServicesTableLib.h>

// 定义PCD协议类型
typedef struct {
    EFI_STATUS (*Get8)(UINTN PcdId, UINT8 *Value);
    // 其他协议函数...
} PCD_PROTOCOL;

// 全局变量，在初始化阶段获取并存储PCD协议实例
STATIC PCD_PROTOCOL *gPcdProtocol = NULL;

// 驱动初始化函数，在驱动入口点调用
EFI_STATUS InitializePcdProtocol(void) {
    EFI_STATUS Status;
    // 在初始化阶段使用Boot Services获取协议
    Status = gBS->LocateProtocol(&PCD_PROTOCOL_GUID, NULL, (VOID **)&gPcdProtocol);
    return Status;
}

EFI_STATUS __fastcall SmiHandler_17C8(
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
    if (CommBuffer->Sig != 'GFCU') {
        Status = EFI_INVALID_PARAMETER;
        goto _Exit;
    }
    if (CommBuffer->Case == 16 && !CommBuffer->BufferPtr1) {
        // 避免在SMI处理程序中调用Boot Services，直接使用预获取的协议
        if (!gPcdProtocol) {
            Status = EFI_PROTOCOL_ERROR;
            goto _Exit;
        }
        UINT8 PcdValue;
        Status = gPcdProtocol->Get8(0x2C4, &PcdValue);
        if (!EFI_ERROR(Status) && PcdValue == 1) {
            HandlerUnregister();
        }
    }
_Exit:
    return Status;
}

// 移除不安全的运行时Boot Services调用，依赖初始化阶段获取的协议
PCD_PROTOCOL *BsLocatePcdProtocol() {
    return gPcdProtocol; // 直接返回预获取的协议实例
}
