#include <Library/SmmServicesTableLib.h>

// 定义协议中使用的函数指针类型
typedef EFI_STATUS (*PROTOCOL_FUNCTION)(VOID *Parameter1, VOID *Parameter2, UINTN Parameter3);

// 全局变量，在初始化阶段缓存协议中的函数指针
STATIC PROTOCOL_FUNCTION gCachedFunction = NULL;

EFI_STATUS InitializeProtocol2(void) {
    EFI_STATUS Status;
    VOID *UnknownProtocol2;
    
    // 在驱动初始化阶段获取协议
    Status = gBS->LocateProtocol(&gUnknownProtocol2Guid, NULL, &UnknownProtocol2);
    if (EFI_ERROR(Status)) return Status;
    
    // 提取并缓存需要的函数指针（假设0x50偏移处为函数表基址，0xC0为具体函数偏移）
    gCachedFunction = (PROTOCOL_FUNCTION)((UINTN)UnknownProtocol2 + 0x50 + 0xC0);
    return EFI_SUCCESS;
}

EFI_STATUS SwSmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize) {
    if (!gCachedFunction) return EFI_PROTOCOL_ERROR; // 确保初始化完成
    
    if (*((UINT8 *)gUnknownProtocol2 + 0x19B2)) {
        *((UINT64 *)gUnknownProtocol2 + 0x334) = 3;
        if (!sub_8000717C((UINT64 *)gUnknownProtocol2 + 0x71)) {
            // 使用缓存的函数指针，避免直接解引用协议结构中的值
            gCachedFunction(&unk_8000ABD0, sub_800018D8, v9);
        }
    }
    return EFI_SUCCESS;
}
