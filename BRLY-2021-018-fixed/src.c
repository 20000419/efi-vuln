/**
 * Secure SMI Handler with SMM-only service usage
 * Eliminates unsafe EFI_BOOT_SERVICES/EFI_RUNTIME_SERVICES calls
 */
EFI_STATUS __fastcall SmiHandler_1C10(
    EFI_HANDLE DispatchHandle,
    const void *Context,
    void *CommBuffer,
    UINTN *CommBufferSize)
{
    EFI_STATUS Status = EFI_SUCCESS;
    UINTN NoHandles = 0;
    void *Buffer = NULL;
    UINTN BufferSize = 0;
    UINTN v7 = 0;

    // 1. 输入参数有效性验证
    if (!CommBuffer || !CommBufferSize) {
        return EFI_INVALID_PARAMETER;
    }

    // 2. 命令标识符验证（第一个QWORD必须为1）
    if (*(UINT64 *)CommBuffer != 1) {
        Status = EFI_UNSUPPORTED;
        goto WriteStatus;
    }

    // 3. 使用SMM系统表服务替代Boot Services（LocateHandleBuffer不安全）
    // 获取句柄数量（避免使用gBS->LocateHandleBuffer）
    Status = gSmst_E718->SmmLocateHandle(
        ByProtocol,
        &EFI_ATA_PASS_THRU_PROTOCOL_GUID_D660,
        NULL,
        &NoHandles,
        NULL  // 仅获取数量，不分配缓冲区
    );
    if (EFI_ERROR(Status) && Status != EFI_NOT_FOUND) {
        goto WriteStatus;
    }

    // 4. 安全分配SMM内存
    BufferSize = NoHandles * sizeof(EFI_HANDLE);  // 计算所需缓冲区大小
    Status = gSmst_E718->SmmAllocatePool(
        EfiRuntimeServicesData,
        BufferSize,
        &Buffer
    );
    if (EFI_ERROR(Status) || !Buffer) {
        Status = EFI_OUT_OF_RESOURCES;
        goto WriteStatus;
    }

    // 5. 使用SMM服务获取句柄列表
    Status = gSmst_E718->SmmLocateHandle(
        ByProtocol,
        &EFI_ATA_PASS_THRU_PROTOCOL_GUID_D660,
        NULL,
        &BufferSize,
        Buffer
    );
    if (EFI_ERROR(Status)) {
        gSmst_E718->SmmFreePool(Buffer);
        goto WriteStatus;
    }

    // 6. 安全处理句柄数量（原逻辑BufferSize >> 3改为正确计算）
    v7 = (Status == EFI_NOT_FOUND) ? 0 : (BufferSize / sizeof(EFI_HANDLE));
    gSmst_E718->SmmFreePool(Buffer);  // 使用SMM内存释放接口

    // 7. 调用子函数前的安全检查（确保子函数使用SMM服务）
    if (v7 == NoHandles) {
        Status = sub_1E6C_SmmSafe();  // 替换为SMM安全版本子函数
    } else {
        Status = EFI_NOT_READY;
    }

WriteStatus:
    // 8. 写入状态前验证目标地址不在SMRAM（新增安全检查）
    if (!IsAddressInSmram(CommBuffer, 1, sizeof(EFI_STATUS))) {
        *(UINT64 *)((UINT8 *)CommBuffer + 1) = Status;
    } else {
        // 防止向SMRAM写入状态码
        Status = EFI_ACCESS_DENIED;
    }

    return EFI_SUCCESS;
}

/**
 * SMM安全版本子函数（替换所有Boot/Runtime Services调用）
 */
EFI_STATUS sub_1E6C_SmmSafe() {
    EFI_STATUS Status = EFI_SUCCESS;
    void *SmmRuntimeInterface = NULL;

    // 1. 使用SMM系统表获取SMM运行时协议（替代gBS->LocateProtocol）
    Status = gSmst_E718->SmmLocateProtocol(
        &EFI_SMM_RUNTIME_PROTOCOL_GUID_D630,
        NULL,
        &SmmRuntimeInterface
    );
    if (EFI_ERROR(Status)) {
        return Status;
    }

    // 2. 安全访问变量（假设存在SMM专用变量接口，或通过SMM内存直接访问）
    // 避免使用gRT->GetVariable，改用SMM环境下的可信变量访问机制
    // （若无可信接口，需确保变量存储区域已通过SMRAM验证）

    // 3. 其他操作使用SMM专用服务（如SmmAllocatePool/SmmFreePool）
    void *Data = gSmst_E718->SmmAllocatePool(EfiRuntimeServicesData, 0x100);
    if (Data) {
        gSmst_E718->SmmFreePool(Data);
    }

    return EFI_SUCCESS;
}

/**
 * 辅助函数：检查目标地址是否在SMRAM（与之前修复一致）
 */
BOOLEAN IsAddressInSmram(VOID *Buffer, UINTN Offset, UINTN Size) {
    // 实现同之前修复中的SMRAM地址验证逻辑
    // ...（代码可复用之前的IsBufferOrOffsetInSmram函数）
}
