EFI_STATUS __fastcall SmiHandler_800016B0(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  EFI_STATUS Status; // rax

  if ( CommBuffer && CommBufferSize && !gExitBootServices && *CommBufferSize == 0x1020 )
  {
    // Validate input pointers are not in SMRAM
    if (IsPointerInSmram(CommBuffer) || IsPointerInSmram(CommBufferSize)) {
      return EFI_ACCESS_DENIED;
    }
    
    switch ( *CommBuffer )
    {
      case 2: {
        UINTN srcOffset = *(UINT8*)(CommBuffer + 2);
        UINTN destOffset = 32;
        UINTN size = *(UINT8*)(CommBuffer + 3);
        
        // Validate source and destination pointers
        void* src = (UINT8*)CommBuffer + srcOffset;
        void* dest = (UINT8*)CommBuffer + destOffset;
        
        // Check if pointers and size are within valid bounds
        if (srcOffset + size > *CommBufferSize || 
            destOffset + size > *CommBufferSize ||
            IsPointerInSmram(src) || 
            IsPointerInSmram(dest)) {
          return EFI_INVALID_PARAMETER;
        }
        
        Status = sub_80002B00(src, srcOffset, size);
        goto _WriteStatus;
      }
      
      case 3: {
        UINTN param1 = *(UINT8*)(CommBuffer + 2);
        UINTN srcOffset1 = 32;
        UINTN srcOffset2 = 3;
        UINTN size = param1;
        
        // Validate source pointers
        void* src1 = (UINT8*)CommBuffer + srcOffset1;
        void* src2 = (UINT8*)CommBuffer + srcOffset2;
        
        // Check if pointers and size are within valid bounds
        if (srcOffset1 + size > *CommBufferSize || 
            srcOffset2 + size > *CommBufferSize ||
            IsPointerInSmram(src1) || 
            IsPointerInSmram(src2)) {
          return EFI_INVALID_PARAMETER;
        }
        
        Status = sub_80002A38(param1, src1, src2, size);
        goto _WriteStatus;
      }
      
      case 4:
        Status = sub_800029A4(*(UINT8*)(CommBuffer + 2), *(UINT8*)(CommBuffer + 3));
_WriteStatus:
        *(UINT8*)(CommBuffer + 1) = Status;
        break;
    }
  }
  return 0;
}

// Helper function to check if a pointer is within SMRAM
// Implementation depends on platform-specific SMRAM range detection
BOOLEAN IsPointerInSmram(const void* ptr) {
  // Platform-specific implementation to check if ptr is in SMRAM
  // Example:
  // return (ptr >= SmramBase && ptr < SmramBase + SmramSize);
  return FALSE; // Placeholder for actual implementation
}
