unsigned __int64 __fastcall GetChunk(_DWORD *Length, _QWORD *ChunkPtr, _DWORD *ChunkType, _DWORD *a4)
{
  unsigned __int64 v5; // rbx
  unsigned __int8 *ZeroPool; // rax
  unsigned __int8 *v10; // rdi
  __int64 v11; // rdx
  unsigned __int8 *v12; // rcx
  __int64 v13; // r9
  __int64 v14; // r8
  __int64 v15; // rdx
  __int64 v16; // r8
  unsigned __int8 *v17; // rcx
  __int64 v18; // rdx
  int v19; // ecx
  UINTN Length1; // rcx
  _BYTE *v21; // rax
  __int64 v22; // r8
  __int64 v23; // r10
  __int64 v24; // r9
  __int64 v25; // rdx
  unsigned __int8 *v26; // rcx
  int v27; // ecx
  int v28; // eax
  unsigned __int8 *v30; // [rsp+20h] [rbp-28h] BYREF

  v5 = 0i64;
  ZeroPool = (unsigned __int8 *)AllocateZeroPool(4ui64);
  v30 = ZeroPool;
  v10 = ZeroPool;
  if (ZeroPool)
  {
    v11 = GlobalImagePtr;
    v12 = ZeroPool;
    v13 = 4i64;
    v14 = GlobalImagePtr - (_QWORD)ZeroPool;
    do
    {
      *v12 = v12[v14];
      ++v12;
      --v13;
    } while (v13);
    v15 = v11 + 4;
    v16 = 4i64;
    *Length = ZeroPool[3] + ((ZeroPool[2] + ((ZeroPool[1] + (*ZeroPool << 8)) << 8)) << 8);
    v17 = ZeroPool;
    do
    {
      *v17 = v17[v15 - (_QWORD)ZeroPool];
      ++v17;
      --v16;
    } while (v16);
    v18 = v15 + 4;
    v19 = ZeroPool[1] + (*ZeroPool << 8);
    GlobalImagePtr = v18;
    *ChunkType = ZeroPool[3] + ((ZeroPool[2] + (v19 << 8)) << 8);
    Length1 = (unsigned int)*Length;

    // Validate chunk length to prevent overflow and out-of-bounds access
    const UINTN MAX_CHUNK_SIZE = 0x1000000; // Reasonable maximum chunk size
    if (Length1 > MAX_CHUNK_SIZE || (UINT64)v18 + Length1 < (UINT64)v18) // Check overflow and size
    {
      v5 = 0x8000000000000003ui64; // Error code for invalid length
      goto LABEL_18;
    }

    if ((_DWORD)Length1)
    {
      v21 = AllocateZeroPool(Length1);
      *ChunkPtr = v21;
      if (!v21)
      {
        v5 = 0x8000000000000009ui64;
        goto LABEL_18;
      }
      LODWORD(Length1) = *Length;
      v18 = GlobalImagePtr;
      if (*Length)
      {
        v22 = 0i64;
        v23 = (unsigned int)Length1;
        do
        {
          v21[v22] = *(_BYTE *)(v22 + v18);
          ++v22;
          --v23;
        } while (v23);
      }
    }
    else
    {
      *ChunkPtr = 0i64;
    }
    v24 = 4i64;
    // Safely calculate new GlobalImagePtr with validated length
    v25 = v18 + Length1; // Now Length1 is validated
    if ((UINT64)v25 + 4 < (UINT64)v25) // Check overflow when adding 4
    {
      v5 = 0x8000000000000003ui64;
      goto LABEL_18;
    }
    v26 = v10;
    do
    {
      *v26 = v26[v25 - (_QWORD)v10];
      ++v26;
      --v24;
    } while (v24);
    v27 = v10[2];
    v28 = v10[1];
    GlobalImagePtr = v25 + 4;
    *a4 = v10[3] + ((v27 + ((v28 + (*v10 << 8)) << 8)) << 8);
LABEL_18:
    sub_4654(&v30);
    return v5;
  }
  return 0x8000000000000009ui64;
}
