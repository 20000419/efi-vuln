Below is the decompiled code of the vulnerable handler:

EFI_STATUS __fastcall SwSmiHandler_474(__int64 a1, __int64 a2, UINTN *CpuIndex)
{
  EFI_STATUS Status; // rax
  UINTN CurrentCpuIndex; // rbx
  bool NotFound; // zf
  UINTN CpuNum; // r9
  char AsfSecureBootValue[4]; // [rsp+30h] [rbp-10h] BYREF
  void *RegisterValue; // [rsp+34h] [rbp-Ch] BYREF

  LODWORD(Status) = 0;
  if ( !g_ReadyToBootRegistered )
  {
    LODWORD(Status) = (gSmmCpu_10A0->ReadSaveState)(
                        gSmmCpu_10A0,
                        4i64,
                        EFI_SMM_SAVE_STATE_REGISTER_RBX,
                        *CpuIndex,
                        &RegisterValue);
    // compare RBX value with "$H2O" for each CPU
    for ( CurrentCpuIndex = 0i64; ; ++CurrentCpuIndex )
    {
      NotFound = CurrentCpuIndex == gSmst_1068->NumberOfCpus;
      if ( CurrentCpuIndex >= gSmst_1068->NumberOfCpus )
        break;
      Status = (gSmmCpu_10A0->ReadSaveState)(
                 gSmmCpu_10A0,
                 4i64,
                 EFI_SMM_SAVE_STATE_REGISTER_RBX,
                 CurrentCpuIndex,
                 &RegisterValue);
      if ( !Status && RegisterValue == '$H2O' )
      {
        NotFound = CurrentCpuIndex == gSmst_1068->NumberOfCpus;
        break;
      }
    }
    // if RBX value is "$H2O" for some CPU
    if ( !NotFound )
    {
      Status = (gSmmCpu_10A0->ReadSaveState)(
                 gSmmCpu_10A0,
                 4i64,
                 EFI_SMM_SAVE_STATE_REGISTER_RAX,
                 *CpuIndex,
                 &RegisterValue);
      if ( (Status & 0x8000000000000000ui64) == 0i64 )
      {
        AsfSecureBootValue[0] = BYTE1(RegisterValue);
        // Set "AsfSecureBoot" to dword from RAX
        Status = gRT_1018->SetVariable(L"AsfSecureBoot", &VendorGuid, 7u, 1ui64, AsfSecureBootValue);// vulnerability
        if ( (Status & 0x8000000000000000ui64) == 0i64 )
          LODWORD(Status) = x_GetSetVariablePtr();
      }
    }
  }
  CpuNum = *CpuIndex;
  LODWORD(RegisterValue) = Status;
  // WriteSaveState instead of ReadSafeState (to return the result)
  (gSmmCpu_10A0->ReadSaveState)(gSmmCpu_10A0, 4i64, EFI_SMM_SAVE_STATE_REGISTER_RAX, CpuNum, &RegisterValue);
  return 0i64;
}
//The SetVariable() service will be called if two conditions are met:

//g_ReadyToBootRegistered flag not set
//the RBX register contain the value 0x2448324F ($H20) for some CPU
//The handler is registered in the function located at offset 0x5E0.Below is the decompiled code of this function:

__int64 RegisterHandler()
{
  EFI_HANDLE DispatchHandle; // [rsp+20h] [rbp-18h] BYREF
  void *Registration; // [rsp+28h] [rbp-10h] BYREF
  EFI_SMM_SW_REGISTER_CONTEXT RegisterContext; // [rsp+50h] [rbp+18h] BYREF
  EFI_SMM_SW_DISPATCH2_PROTOCOL *EfiSmmSwDispatch2Protocol; // [rsp+58h] [rbp+20h] BYREF

  gSmst_1068->SmmLocateProtocol(&EFI_SMM_CPU_PROTOCOL_GUID_E00, 0i64, &gSmmCpu_10A0);
  gSmst_1068->SmmLocateProtocol(&EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID_DF0, 0i64, &EfiSmmSwDispatch2Protocol);
  RegisterContext.SwSmiInputValue = 0x56i64;
  (EfiSmmSwDispatch2Protocol->Register)(EfiSmmSwDispatch2Protocol, SwSmiHandler_474, &RegisterContext, &DispatchHandle);
  gSmst_1068->SmmRegisterProtocolNotify(
    &EDKII_SMM_READY_TO_BOOT_PROTOCOL_GUID_E10,
    SetReadyToBootRegisteredFlag,
    &Registration);
  return 0i64;
  }
