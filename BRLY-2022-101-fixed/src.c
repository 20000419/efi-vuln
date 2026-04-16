__int64 __fastcall sub_E790()
{
  __int64 result; // rax
  unsigned int v1; // eax
  unsigned __int64 i; // rbx
  unsigned int v3; // edx
  unsigned int v4; // ecx
  char v5; // dl
  bool v6; // cl
  int v7; // edi
  int v8; // esi
  unsigned __int64 v9; // rcx
  __int64 v10[7]; // [rsp+30h] [rbp-38h] BYREF
  int v11; // [rsp+70h] [rbp+8h] BYREF
  unsigned int v12; // [rsp+78h] [rbp+10h] BYREF
  unsigned int v13; // [rsp+80h] [rbp+18h] BYREF
  __int64 v14; // [rsp+88h] [rbp+20h] BYREF

  v10[0] = 5360i64;
  gRT->GetVariable(
    (CHAR16 *)L"CpuSetup",
    &CPU_SETUP_VARIABLE_GUID,
    (UINT32 *)&v14,
    (UINTN *)v10,
    &unk_2E570);
  result = sub_21B94(3i64, -2147483624, (char *)&v13, &v11);
  if (!v11)
  {
    v1 = v13;
    for (i = 0i64; i <= 3; ++i)
    {
      if (i)
      {
        if (i == 1)
        {
          v3 = v1 >> 5;
          v4 = v1 >> 9;
        }
        else if (i == 2)
        {
          v3 = v1 >> 15;
          v4 = v1 >> 19;
        }
        else
        {
          v3 = v1 >> 20;
          v4 = HIBYTE(v1);
        }
      }
      else
      {
        LOBYTE(v3) = v1;
        v4 = v1 >> 4;
      }
      v5 = v3 & 0xF;
      v6 = (v4 & 1) == 0;
      if (*((_BYTE *)&unk_2E570 + i + 1438) == 1 && v6)
      {
        v7 = v5 & 0xF;
        v8 = v7 << 16;
        sub_21B94(3i64, (v7 << 16) | 0x80000118, (char *)&v12, &v11);
        if (!v11)
        {
          v9 = (100000 * ((unsigned __int64)v12 >> 16) + 0x80000) >> 20;
          *((_WORD *)&unk_2E570 + i + 721) = (100000 * (unsigned __int64)(unsigned __int16)v12 + 0x80000) >> 20;
          *((_WORD *)&unk_2E570 + i + 725) = v9;
        }
        sub_21B94(3i64, v8 | 0x80000518, (char *)&v12, &v11);
        if (!v11)
          *((_WORD *)&unk_2E570 + i + 753) = v12;
        sub_21B94(3i64, v8 | 0x80000718, (char *)&v12, &v11);
        if (!v11)
          *((_WORD *)&unk_2E570 + i + 757) = (1000 * v12 + 4096) >> 13;
        sub_21B94(3i64, (v7 << 8) | 0x80000019, (char *)&v12, &v11);
        if (!v11)
          *((_WORD *)&unk_2E570 + i + 761) = v12 & 0x7FFF;
        v1 = v13;
      }
    }
    UINTN correctDataSize = 5360; // Re-initialize DataSize with actual buffer size
    return gRT->SetVariable(
             (CHAR16 *)L"CpuSetup",
             &CPU_SETUP_VARIABLE_GUID,
             v14,
             correctDataSize,
             &unk_2E570);
  }
  return result;
}
