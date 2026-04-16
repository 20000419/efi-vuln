__int64 __fastcall SwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        void *CommBuffer,
        UINTN *CommBufferSize)
{
  __int64 result;
  UINTN CpuIndex;
  bool CpuIndexNotFound;
  BIOS_VIDEO_DEV_SIMPLE *LocalModeData;
  int VbeModeNumber;
  __int64 i;
  BIOS_VIDEO_SIMPLE_MODE_DATA *SimpleModeData;
  BIOS_VIDEO_SIMPLE_MODE_DATA *ModeData;
  __int64 Index;
  UINTN FrameBufferSize;
  int _Rax;
  int _Rdx;
  int _Rbx;
  EFI_SMM_CPU_PROTOCOL *EfiSmmCpuProtocol;
  __int64 DataSize;
  BIOS_VIDEO_DEV_SIMPLE *Int10HookPrivateDataVariable;
  EFI_SMRAM_DESCRIPTOR *SmramMap;
  UINTN SmramMapSize;
  UINTN SmramCount;
  UINTN j;
  bool OverlapsSmram;

  EfiSmmCpuProtocol = 0;
  _Rax = 0;
  _Rbx = 0;
  _Rdx = 0;
  result = gSmst_0->SmmLocateProtocol(&EFI_SMM_CPU_PROTOCOL_GUID, 0, &EfiSmmCpuProtocol);
  if ( result >= 0 )
  {
    CpuIndex = 0;
    CpuIndexNotFound = gSmst_0->NumberOfCpus == 0;
    if ( gSmst_0->NumberOfCpus )
    {
      while ( 1 )
      {
        EfiSmmCpuProtocol->ReadSaveState(EfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RAX, CpuIndex, &_Rax);
        EfiSmmCpuProtocol->ReadSaveState(EfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RDX, CpuIndex, &_Rdx);
        if ( _Rax == 0x74 && _Rdx == 0xB2 )
          break;
        CpuIndexNotFound = ++CpuIndex == gSmst_0->NumberOfCpus;
        if ( CpuIndex >= gSmst_0->NumberOfCpus )
          goto _Exit;
      }
      EfiSmmCpuProtocol->ReadSaveState(EfiSmmCpuProtocol, 4, EFI_SMM_SAVE_STATE_REGISTER_RBX, CpuIndex, &_Rbx);
      CpuIndexNotFound = CpuIndex == gSmst_0->NumberOfCpus;
    }
_Exit:
    if ( CpuIndexNotFound )
      return EFI_NOT_FOUND;
    LocalModeData = gVideoDevSimple;
    VbeModeNumber = _Rbx & 0x1FF;
    if ( !gVideoDevSimple )
    {
      DataSize = 8;
      if ( CommonGetInt10HookPrivateDataVariable() < 0 )
        return 0;
      LocalModeData = Int10HookPrivateDataVariable;
      gVideoDevSimple = Int10HookPrivateDataVariable;
    }
    i = 0;
    SimpleModeData = LocalModeData->SimpleModeData;
    if ( LocalModeData->MaxMode )
    {
      for ( ModeData = LocalModeData->SimpleModeData;
            LOWORD(ModeData->VbeModeNumber) != VbeModeNumber || ModeData->FrameBufferSize <= 0x800000;
            ++ModeData )
      {
        if ( ++i >= LocalModeData->MaxMode )
          return 0;
      }
      Index = i;
      FrameBufferSize = SimpleModeData[Index].FrameBufferSize;
      if ( FrameBufferSize )
      {
        // Get SMRAM map
        SmramMapSize = 0;
        gSmst_0->SmmGetSmramMap(&SmramMapSize, NULL);
        SmramMap = AllocatePool(SmramMapSize);
        if (!SmramMap)
          return EFI_OUT_OF_RESOURCES;
          
        result = gSmst_0->SmmGetSmramMap(&SmramMapSize, SmramMap);
        if (result != EFI_SUCCESS) {
          FreePool(SmramMap);
          return result;
        }
        
        // Calculate SMRAM regions count
        SmramCount = SmramMapSize / sizeof(EFI_SMRAM_DESCRIPTOR);
        
        // Check if buffer overlaps with any SMRAM region
        OverlapsSmram = FALSE;
        for (j = 0; j < SmramCount; j++) {
          UINT64 BufferStart = (UINT64)SimpleModeData[Index].LinearFrameBuffer;
          UINT64 BufferEnd = BufferStart + FrameBufferSize;
          UINT64 SmramStart = SmramMap[j].PhysicalStart;
          UINT64 SmramEnd = SmramStart + SmramMap[j].RegionLength;
          
          if ((BufferStart < SmramEnd) && (BufferEnd > SmramStart)) {
            OverlapsSmram = TRUE;
            break;
          }
        }
        
        FreePool(SmramMap);
        
        // Only zero memory if it doesn't overlap SMRAM
        if (!OverlapsSmram) {
          ZeroMem(SimpleModeData[Index].LinearFrameBuffer, FrameBufferSize);
        } else {
          return EFI_ACCESS_DENIED;
        }
      }
    }
    return 0;
  }
  return result;
}
