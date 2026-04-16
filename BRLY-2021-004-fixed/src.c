__int64 __fastcall SwSmiHandler(void *a1)
{
  __int64 result; // rax
  int v3; // [rsp+30h] [rbp-48h] BYREF
  __int64 (__fastcall **EfiSmmVariableProtocol)(__int16 *, EFI_GUID *, int *, __int64 *, _QWORD *); // [rsp+38h] [rbp-40h] BYREF
  __int64 v5; // [rsp+40h] [rbp-38h] BYREF
  EFI_SMM_SW_DISPATCH2_PROTOCOL *EfiSmmSwDispatch2Protocol; // [rsp+48h] [rbp-30h] BYREF
  _QWORD v7[5]; // [rsp+50h] [rbp-28h] BYREF

  EfiSmmVariableProtocol = 0i64;
  v5 = 32i64;
  v3 = 6;
  gSmst->SmmLocateProtocol(&EFI_SMM_VARIABLE_PROTOCOL_GUID, 0i64, (void **)&EfiSmmVariableProtocol);
  if ( EfiSmmVariableProtocol && (*EfiSmmVariableProtocol)(aAmdmemcontextd, &VendorGuid, &v3, &v5, v7) >= 0 )
    sub_1610(v7);
  result = gSmst->SmmLocateProtocol(&EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID, 0i64, (void **)&EfiSmmSwDispatch2Protocol);
  if ( result >= 0 )
    return EfiSmmSwDispatch2Protocol->UnRegister(EfiSmmSwDispatch2Protocol, a1);
  return result;
}
