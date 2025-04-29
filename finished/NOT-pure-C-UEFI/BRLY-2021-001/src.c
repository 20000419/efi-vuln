//SWSMI handler at offset 0x48C (SwSmiHandler_48C) dereferences gRT (EFI_RUNTIME_SERVICES) pointer to call a ResetSystem function, which can result in code execution in SMRAM and escalating privilege from ring 0 to ring -2.

.text:000000000000048C SwSmiHandler_48C proc near              ; DATA XREF: sub_314+FA↑o
...
.text:000000000000048C
.text:000000000000048C                 mov     [rsp-28h+arg_0], rbx
.text:0000000000000491                 mov     [rsp-28h+arg_8], rsi
.text:0000000000000496                 mov     [rsp-28h+arg_10], rdi
.text:000000000000049B                 push    rbp
.text:000000000000049C                 push    r12
.text:000000000000049E                 push    r13
...
...
.text:0000000000000BAC ; ---------------------------------------------------------------------------
.text:0000000000000BAC
.text:0000000000000BAC loc_BAC:                                ; CODE XREF: SwSmiHandler_48C+6C2↑j
.text:0000000000000BAC                 mov     rax, cs:gRT_1B00
.text:0000000000000BB3                 xor     edx, edx        ; ResetStatus
.text:0000000000000BB5                 xor     r9d, r9d        ; ResetData
.text:0000000000000BB8                 lea     ecx, [rdx+2]    ; ResetType
.text:0000000000000BBB                 xor     r8d, r8d        ; DataSize
.text:0000000000000BBE                 call    [rax+EFI_RUNTIME_SERVICES.ResetSystem] ; gRT->ResetSystem()
//SwSmiHandler_48C is installed by the sub_314, which is called from ModuleEntryPoint

.text:0000000000000314 sub_314         proc near               ; CODE XREF: _ModuleEntryPoint+7B↑p
...
.text:0000000000000340                 call    [rax+_EFI_SMM_SYSTEM_TABLE2.SmmLocateProtocol] ; gSmst->SmmLocateProtocol
.text:0000000000000346                 mov     rax, cs:gSmst_1AF8
.text:000000000000034D                 lea     r8, [rsp+28h+EFI_SMM_SW_DISPATCH2_PROTOCOL_IF] ; Interface
.text:0000000000000352                 lea     rcx, EFI_SMM_SW_DISPATCH2_PROTOCOL_GUID_19F0 ; Protocol
.text:0000000000000359                 xor     edx, edx        ; Registration
...
.text:00000000000003F5                 lea     r9, [rsp+28h+DispatchHandle] ; DispatchHandle
.text:00000000000003FA                 mov     rcx, [rax]
.text:00000000000003FD                 mov     rax, [rsp+28h+EFI_SMM_SW_DISPATCH2_PROTOCOL_IF]
.text:0000000000000402                 lea     r8, [rsp+28h+RegisterContext] ; RegisterContext
.text:0000000000000407                 mov     cs:qword_1C28, rcx
.text:000000000000040E                 lea     rdx, SwSmiHandler_48C ; DispatchFunction
.text:0000000000000415                 mov     rcx, rax        ; This
.text:0000000000000418                 mov     [rsp+28h+RegisterContext.SwSmiInputValue], 80h ; '€'
.text:0000000000000421                 call    [rax+EFI_SMM_SW_DISPATCH2_PROTOCOL.Register]
//Passing RAX = 0x5380, RBX = 0x7003 to SwSmiHandler_48C via CPU save state (ReadSaveState) will trigger the following vulnerable code:

__int64 __fastcall SwSmiHandler_48C():

  case 0x7003u:
    gRT_1B00->ResetSystem(EfiResetShutdown, 0i64, 0i64, 0i64);
    goto LABEL_132;
