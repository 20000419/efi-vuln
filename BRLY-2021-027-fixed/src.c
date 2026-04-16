#include <Library/SmmServicesTableLib.h>

// 验证指针是否在SMRAM区域内
BOOLEAN IsPointerInSmram(EFI_PHYSICAL_ADDRESS Pointer)
{
    EFI_STATUS Status;
    EFI_SMRAM_DESCRIPTOR *Descriptor = NULL;
    UINTN DescriptorCount = 0;
    UINTN Index;
    BOOLEAN IsInSmram = FALSE;

    // 获取SMRAM描述符表
    Status = gSmst->SmmGetSmramMap(&DescriptorCount, &Descriptor);
    if (EFI_ERROR(Status)) {
        return TRUE; // 出错时保守处理，视为在SMRAM内
    }

    // 检查每个SMRAM区域
    for (Index = 0; Index < DescriptorCount; Index++) {
        EFI_PHYSICAL_ADDRESS SmramBase = Descriptor[Index].PhysicalStart;
        EFI_PHYSICAL_ADDRESS SmramEnd = SmramBase + Descriptor[Index].RegionLength;

        if (Pointer >= SmramBase && Pointer < SmramEnd) {
            IsInSmram = TRUE;
            break;
        }
    }

    return IsInSmram;
}

// 修复后的Func0函数
__int64 Func0()
{
    UINT64 v0;
    UINT64 ptr;
    UINT8 v2;
    EFI_STATUS Status = EFI_SUCCESS;

    v0 = ReadSaveSate(EFI_SMM_SAVE_STATE_REGISTER_RBX);
    ptr = ReadSaveSate(EFI_SMM_SAVE_STATE_REGISTER_RSI);
    v2 = 1;

    // 验证ptr是否指向SMRAM
    if (IsPointerInSmram((EFI_PHYSICAL_ADDRESS)ptr)) {
        return EFI_SECURITY_VIOLATION;
    }

    // 验证ptr+8是否指向SMRAM
    if (IsPointerInSmram((EFI_PHYSICAL_ADDRESS)ptr + 8)) {
        return EFI_SECURITY_VIOLATION;
    }

    // 验证ptr+0x10是否指向SMRAM
    if (IsPointerInSmram((EFI_PHYSICAL_ADDRESS)ptr + 0x10)) {
        return EFI_SECURITY_VIOLATION;
    }

    // 验证ptr+0x20是否指向SMRAM
    if (IsPointerInSmram((EFI_PHYSICAL_ADDRESS)ptr + 0x20)) {
        return EFI_SECURITY_VIOLATION;
    }

    // 验证ptr+0x28是否指向SMRAM
    if (IsPointerInSmram((EFI_PHYSICAL_ADDRESS)ptr + 0x28)) {
        return EFI_SECURITY_VIOLATION;
    }

    // 原有的功能验证
    if (v0 != sub_80009F6C((__int64)&stru_80011078, v2) + 40 || 
        *(UINT32 *)(ptr + 8) != 'AFMS') {
        return EFI_INVALID_PARAMETER;
    }

    // 验证gSmmBuffer相关指针
    if (IsPointerInSmram((EFI_PHYSICAL_ADDRESS)gSmmBuffer + 8)) {
        return EFI_SECURITY_VIOLATION;
    }

    if (IsPointerInSmram((EFI_PHYSICAL_ADDRESS)*(UINT64 *)(gSmmBuffer + 8))) {
        return EFI_SECURITY_VIOLATION;
    }

    // 调用函数
    UINT64 result = ((__int64 (*)(UINT64, UINT64, UINT64, UINT64, UINT64))(*(UINT64 *)(gSmmBuffer + 8) + 8))(
        *(UINT64 *)(gSmmBuffer + 8), 
        *(UINT64 *)(ptr + 0x10), 
        0, 
        ptr + 0x20, 
        ptr + 0x28
    );

    // 验证写入位置是否在SMRAM外
    if (!IsPointerInSmram((EFI_PHYSICAL_ADDRESS)ptr)) {
        *(UINT64 *)ptr = result;
    } else {
        Status = EFI_SECURITY_VIOLATION;
    }

    return Status == EFI_SUCCESS ? result : Status;
}

// 修复后的SwSmiHandler函数
EFI_STATUS SwSmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
    UINT64 input;
    UINT64 counter;
    UINT64 offset;
    EFI_STATUS Status = EFI_SUCCESS;

    input = ReadSaveSate(EFI_SMM_SAVE_STATE_REGISTER_RAX);
    counter = 0;
    
    if (gFuncsArray[0]) {
        offset = 0;
        while (BYTE1(input) != (UINT32)gIndexArray[offset]) {
            offset = 2 * ++counter;
            if (!gIndexArray[2 * counter + 1]) {
                goto LABEL_12;
            }
        }
        
        // 验证函数指针是否在SMRAM外
        if (IsPointerInSmram((EFI_PHYSICAL_ADDRESS)gFuncsArray[2 * counter])) {
            Status = EFI_SECURITY_VIOLATION;
        } else {
            // 调用函数
            Status = ((EFI_STATUS (*)(UINT64, UINT64, UINT64))gFuncsArray[2 * counter])(
                2 * counter, 
                offset * 8, 
                0x8000000000000003
            );
        }
    }

LABEL_12:
    // 处理返回状态
    return Status;
}
