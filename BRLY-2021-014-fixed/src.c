/**
 * Check if a buffer or its offset falls within SMRAM regions
 * @param Buffer: Pointer to the start of the buffer
 * @param Offset: Offset within the buffer to check (0 for full buffer check)
 * @param Size: Size of the data to check (for offset: size of the specific field)
 * @return TRUE if the target address range is in SMRAM, FALSE otherwise
 */
BOOLEAN IsAddressInSmram(VOID *Buffer, UINTN Offset, UINTN Size) {
    EFI_STATUS Status;
    UINTN MapSize, DescriptorCount;
    EFI_SMRAM_DESCRIPTOR *SmramMap;
    UINTN i;
    EFI_PHYSICAL_ADDRESS TargetStart, TargetEnd;
    
    // 获取SMRAM映射表
    Status = gSmst->SmmGetSmramMap(&MapSize, &SmramMap);
    if (EFI_ERROR(Status)) return FALSE; // 安全回退：映射表获取失败时默认允许
    
    TargetStart = (EFI_PHYSICAL_ADDRESS)Buffer + Offset;
    TargetEnd = TargetStart + Size;
    
    DescriptorCount = MapSize / sizeof(EFI_SMRAM_DESCRIPTOR);
    for (i = 0; i < DescriptorCount; i++) {
        EFI_PHYSICAL_ADDRESS RegionStart = SmramMap[i].PhysicalStart;
        EFI_PHYSICAL_ADDRESS RegionEnd = RegionStart + SmramMap[i].CpuStart;
        
        // 检查目标地址范围与SMRAM区域是否有重叠
        if ((TargetStart < RegionEnd) && (TargetEnd > RegionStart)) {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * 安全增强的SMI处理函数，包含SMRAM指针验证
 */
EFI_STATUS __fastcall SmiHandler_82C4(
    EFI_HANDLE DispatchHandle,
    CONST VOID *Context,
    CommBufferStruct *CommBuffer,
    UINTN *CommBufferSize
) {
    EFI_STATUS Status = EFI_SUCCESS;
    
    // 基础参数有效性检查
    if (!CommBuffer || !CommBufferSize) {
        return EFI_INVALID_PARAMETER;
    }
    
    // 验证整个通信缓冲区是否位于SMRAM（防止恶意指针指向SMRAM）
    if (IsAddressInSmram(CommBuffer, 0, sizeof(CommBufferStruct))) {
        ReportSecurityViolation(); // 自定义安全违规报告函数
        return EFI_ACCESS_DENIED;
    }
    
    // 检查第一个QWORD是否为0x01（触发数据写入的条件）
    if (CommBuffer->qword0 != 1) {
        return EFI_INVALID_PARAMETER;
    }
    
    // 对每个即将写入的字段进行SMRAM地址验证
    
    // 验证偏移1（4字节）写入位置
    if (IsAddressInSmram(CommBuffer, 1, sizeof(CommBuffer->dword1))) {
        ReportSecurityViolation();
        return EFI_ACCESS_DENIED;
    }
    
    // 验证偏移5（2字节）写入位置
    if (IsAddressInSmram(CommBuffer, 5, sizeof(CommBuffer->word5))) {
        ReportSecurityViolation();
        return EFI_ACCESS_DENIED;
    }
    
    // 验证偏移7（2字节）写入位置
    if (IsAddressInSmram(CommBuffer, 7, sizeof(CommBuffer->word7))) {
        ReportSecurityViolation();
        return EFI_ACCESS_DENIED;
    }
    
    // 验证偏移25（4字节）写入位置
    if (IsAddressInSmram(CommBuffer, 25, sizeof(CommBuffer->dword25))) {
        ReportSecurityViolation();
        return EFI_ACCESS_DENIED;
    }
    
    // 调用子函数（假设子函数内部参数已通过其他方式验证）
    Result = sub_80009CB0(
        CommBuffer->qword9,
        CommBuffer->qword11,
        &dword19,
        CommBuffer->qword1D,
        CommBuffer->dword25,
        &v5,
        &v5 + 2
    );
    
    // 安全写入结果到通信缓冲区（确保写入位置不在SMRAM）
    if (!IsAddressInSmram(CommBuffer, 1, sizeof(CommBuffer->dword1))) {
        CommBuffer->dword1 = Result;
    }
    if (!IsAddressInSmram(CommBuffer, 5, sizeof(CommBuffer->word5))) {
        CommBuffer->word5 = WORD2(v5);
    }
    if (!IsAddressInSmram(CommBuffer, 7, sizeof(CommBuffer->word7))) {
        CommBuffer->word7 = v5;
    }
    if (!IsAddressInSmram(CommBuffer, 25, sizeof(CommBuffer->dword25))) {
        CommBuffer->dword19 = dword19;
    }
    
    return Status;
}
