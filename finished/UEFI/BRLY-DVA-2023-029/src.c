MACRO_EFI __fastcall ChildSwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        unsigned int *CommBuffer,
        UINTN *CommBufferSize)
{
  __int64 Command; // rax
  __int64 v7; // rax
  __int64 v8; // rax
  __int64 v9; // rax
  __int64 v10; // rax
  __int64 v11; // rax
  __int64 v12; // rdx
  __int64 v13; // r8
  int v14; // r9d
  unsigned int v15; // ebp
  __int64 v16; // rbx
  __int64 v17; // rax
  __int64 v18; // rax
  __int64 v19; // rax
  __int64 v20; // rax
  __int64 v21; // r8
  __int64 v22; // r9
  __int64 v23; // rdx
  char v24; // [rsp+28h] [rbp-40h]
  EFI_HANDLE Handle; // [rsp+30h] [rbp-38h] BYREF
  __int64 v26; // [rsp+38h] [rbp-30h] BYREF
  EFI_SMM_SW_REGISTER_CONTEXT RegisterContext; // [rsp+40h] [rbp-28h] BYREF
  EFI_SMM_SW_DISPATCH2_PROTOCOL *EfiSmmSwDispatch2Protocol; // [rsp+48h] [rbp-20h] BYREF
  EFI_HANDLE DispatchHandlea[2]; // [rsp+50h] [rbp-18h] BYREF
  char v30; // [rsp+80h] [rbp+18h] BYREF

  if ( CommBuffer && CommBufferSize && *CommBufferSize >= 0x18 )
  {
    if ( !ValidateMemoryBuffer(CommBuffer, *CommBufferSize) )
      return 0;
    if ( (*(gPhysicalAddr + 0x78040) & 0xF0000) != 0 )
      return EFI_UNSUPPORTED;
    Command = *CommBuffer;
    if ( *CommBuffer <= 6 )
    {
      if ( *CommBuffer == 6 )
      {
        if ( !ValidateMemoryBuffer(CommBuffer + 4, 8) )
          return 0;
        v11 = sub_1624(CommBuffer[4], CommBuffer[5]);
        goto LABEL_48;
      }
      ...
    }
    ...
  }
  ...
}

unsigned __int64 __fastcall sub_1624(__int64 a1, int a2)
{
  __int64 v3; // rax
  unsigned int v4; // r10d
  unsigned int v5; // ebx
  __int64 v6; // r11

  v3 = sub_ED0(a1);
  ...
}

__int64 __fastcall sub_ED0(int Value)
{
  __int64 v1; // rbx
  _DWORD *Addr; // rdx
  __int64 (**v3)(void); // rax
  __int64 v4; // r11
  int v6; // eax
  int v7; // ecx
  __int64 v8; // [rsp+38h] [rbp+10h]
  __int64 (**v9)(void); // [rsp+40h] [rbp+18h] BYREF

  v1 = 0;
  v9 = 0;

  // Controllable Value + integer overflow:
  // * Value is controllable by the attacker(CommBuffer[4])
  // * Due to the integer overflow, Address can take
  //    any value in 32-bit address space
  //    that is a multiple of the page size (0x1000)
  Addr = (((Value + 120) << 12) + 0xE0000000);
  if ( *(((Value + 120) << 12) + 0xE0000002) == 0xFFFF )
  {
    if ( Value == 1 )
    {
      v3 = gEfiHeci2PmProtocol;
      if ( gEfiHeci2PmProtocol )
      {
        v4 = 0;
      }
      else
      {
        v4 = sub_1B3C(&v9);
        v3 = v9;
      }
      if ( v4 >= 0 )
      {
        if ( v3 )
          return v3[3]();
      }
    }
    return v1;
  }
  else
  {
    v6 = *(((Value + 120) << 12) + 0xE0000010);
    v7 = 0;
    v8 = Addr[4] & 0xFFFFFFF0;
    if ( (v6 & 6) == 4 )
    {
      v7 = Addr[5];
      HIDWORD(v8) = v7;
    }
    if ( (Addr[4] & 0xFFFFFFF0) != 0 || v7 )
    {
      Addr[1] |= 0x106; // unchecked write (SMRAM corruption)
      return v8;
    }
    else
    {
      return 0;
    }
  }
}
