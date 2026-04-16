// Static SMRAM-resident storage for protocol functions (allocated in SMRAM)
static struct {
  void (*Func1)(UINTN, UINTN);
  void (*Func2)(UINTN);
  BOOLEAN Initialized;
} gUsbLegacyProtocolCache SMRAM_ATTR;

// Driver initialization (outside SMM, uses boot services safely)
EFI_STATUS EFIAPI UsbLegacyControlSmmInitialize(
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
) {
  EFI_STATUS Status;
  EFI_HANDLE *Buffer = NULL;
  UINTN NoHandles = 0;
  VOID *Interface = NULL;

  // Allocate SMRAM buffer for caching (if not already done)
  if (!gUsbLegacyProtocolCache.Initialized) {
    // Locate handles for ProprietaryProtocol
    Status = gBS->LocateHandleBuffer(
      ByProtocol, 
      &ProprietaryProtocol, 
      NULL, 
      &NoHandles, 
      &Buffer
    );
    if (EFI_ERROR(Status)) {
      return Status;
    }

    // Find first valid protocol instance
    for (UINTN i = 0; i < NoHandles; i++) {
      if (gBS->HandleProtocol(Buffer[i], &ProprietaryProtocol, &Interface) == EFI_SUCCESS && 
          !*(UINTN*)(Interface + 24)) {  // Check protocol validity
        gUsbLegacyProtocolCache.Func1 = *(VOID (**)(UINTN, UINTN))(Interface + 1);
        gUsbLegacyProtocolCache.Func2 = *(VOID (**)(UINTN))(Interface + 2);
        gUsbLegacyProtocolCache.Initialized = TRUE;
        break;
      }
    }

    gBS->FreePool(Buffer);
  }

  // Register SMI handler (now uses cached protocols)
  EFI_SMM_USB_DISPATCH2_REGISTER_CONTEXT RegisterContext = {
    .Type = UsbLegacy,
    .Device = &gDevicePath
  };
  return EfiSmmUsbDispatch2Protocol->Register(
    EfiSmmUsbDispatch2Protocol, 
    UsbSmiHandler, 
    &RegisterContext, 
    &Handle
  );
}

// Fixed SMI handler (no boot services used after initialization)
__int64 __fastcall UsbSmiHandler(
  EFI_HANDLE DispatchHandle,
  const void *Context,
  void *CommBuffer,
  UINTN *CommBufferSize
) {
  UINTN result = 0;

  // Get hardware status (unchanged)
  if ((MEMORY[0xC00F8094] & 0xF00) != 0)
    result = (MEMORY[0xC00F8094] >> 8) & 0xF;

  // Use cached protocol functions (initialized once in SMRAM)
  if (gUsbLegacyProtocolCache.Initialized && gUsbLegacyProtocolCache.Func1)
    result = gUsbLegacyProtocolCache.Func1(result, gUsbLegacyProtocolCache.Func2);

  return result;
}
