__int64 __fastcall UsbApiCoreProc(STRUCT *Struct)
{
  // Validate SubfuncIndex to prevent out-of-bounds array access
  if (Struct->SubfuncIndex >= CORE_PROC_TABLE_SIZE) {
    Struct->RetVal = EFI_INVALID_PARAMETER;
    return EFI_INVALID_PARAMETER;
  }

  // Retrieve function pointer from validated index
  void (*TargetFunc)(void) = gCoreProcTable[Struct->SubfuncIndex];
  
  // Validate the function pointer
  if (TargetFunc == NULL) {
    Struct->RetVal = EFI_UNSUPPORTED;
    return EFI_UNSUPPORTED;
  }

  // Calculate aligned parameter size
  UINTN AlignedSize = (Struct->ParamSizeCoreProc + 3) & ~3u;
  
  // Validate parameter buffer
  if (BufferValidation(Struct->ParamBuffer, AlignedSize) != EFI_SUCCESS) {
    Struct->RetVal = EFI_ACCESS_DENIED;
    return EFI_ACCESS_DENIED;
  }

  // Invoke the function with proper parameter handling
  __int64 result = Invoke(TargetFunc, Struct->ParamBuffer, AlignedSize);
  
  Struct->RetVal = 0;
  *&Struct->ApiRetValCoreProc = result;
  return result;
}
