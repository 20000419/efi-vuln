unsigned __int64 __fastcall HuffmanTablesDecoder(
        unsigned int *a1,
        _DWORD *a2,
        _DWORD *a3,
        __int64 **a4,
        _QWORD *a5,
        _QWORD *a6,
        _QWORD *a7,
        __int64 *ArrayPtr,
        __int64 a9,
        __int64 a10,
        __int64 a11,
        __int64 a12)
{
  _DWORD *v14; // rbx
  unsigned int v15; // esi
  __int64 v16; // rdx
  __int64 v17; // rcx
  __int64 v18; // r8
  __int64 v19; // rdx
  __int64 v20; // rcx
  __int64 v21; // r8
  int Bits; // eax
  unsigned int v23; // eax
  __int64 *v24; // rbx
  __int64 v25; // rdi
  int v26; // eax
  __int64 v27; // rcx
  __int64 v28; // rdx
  __int64 v29; // rdi
  int v31; // r14d
  unsigned int v32; // r14d
  __int64 v33; // rdx
  __int64 v34; // r8
  int *v35; // r11
  int v36; // ecx
  __int64 v37; // rax
  int i; // eax
  __int64 v39; // r8
  int v40; // ecx
  int j; // eax
  __int64 v42; // rcx
  int k; // eax
  __int64 v44; // rcx
  __int64 v45[9]; // [rsp+20h] [rbp-E0h] BYREF
  int v46; // [rsp+68h] [rbp-98h]
  int v47[20]; // [rsp+70h] [rbp-90h] BYREF
  char v48[128]; // [rsp+C0h] [rbp-40h] BYREF
  int v51; // [rsp+190h] [rbp+90h]

  *a2 = 0;
  v14 = a2;
  *a3 = 0;
  v15 = 0;
  *a1 = 0;
  v45[0] = 0x1100000010i64;
  v45[1] = 18i64;
  v45[2] = 0x700000008i64;
  v45[3] = 0x600000009i64;
  v45[4] = 0x50000000Ai64;
  v45[5] = 0x40000000Bi64;
  v45[6] = 0x30000000Ci64;
  v45[7] = 0x20000000Di64;
  v45[8] = 0x10000000Ei64;
  v46 = 15;
  *a1 = ReadBits(a10, a11, a12, 5u);
  *v14 = ReadBits(v17, v16, v18, 5u);
  Bits = ReadBits(v20, v19, v21, 4u);
  *a3 = Bits;
  LODWORD(v14) = Bits;
  sub_7D1D0(v47, 0i64, 76i64);
  v23 = v14 + 4;
  if ( v14 != -4 )
  {
    v24 = v45;
    v25 = v23;
    do
    {
      v26 = ReadBits(a10, a11, a12, 3u);
      v27 = *v24;
      v24 = (v24 + 4);
      v47[v27] = v26;
      --v25;
    }
    while ( v25 );
  }
  sub_5BC44(v48, v45, 19i64, v47);
  v28 = *a1;
  *a4 = ArrayPtr;
  *a5 = a9;
  *a6 = ArrayPtr + 4 * v28 + 1028;
  *a7 = a9 + 1028 + 4 * v28;
  v29 = sub_5C150(19i64, v48, v45);
  if ( !v29 )
    return 0x8000000000000015ui64;
  v31 = *a1;
  v51 = v31;
  if ( v31 + *a2 + 258 )
  {
    v32 = v31 + *a2 + 258;
    do
    {
      if ( sub_5BBD8(a10, a11, a12) )
      {
        if ( *(v35 + 2) )
          v35 = *(v35 + 2);
      }
      else if ( *(v35 + 1) )
      {
        v35 = *(v35 + 1);
      }
      if ( !*(v35 + 1) && !*(v35 + 2) )
      {
        v36 = *v35;
        if ( *v35 > 0xF )
        {
          switch ( v36 )
          {
            case 16:
              for ( i = ReadBits(a10, v33, v34, 2u) + 3; i; --i )
              {
                v39 = v15;
                v40 = *(ArrayPtr + v15++ - 1);
                *(ArrayPtr + v39) = v40;
              }
              break;
            case 17:
              for ( j = ReadBits(a10, v33, v34, 3u) + 3; j; --j )
              {
                v42 = v15++;
                *(ArrayPtr + v42) = 0;
              }
              break;
            case 18:
              for ( k = ReadBits(a10, v33, v34, 7u) + 11; k; --k )
              {
                // BRLY-LOGOFAIL-2023-017: v15 could grow bigger than 322, thus writing OOB on the heap
                v44 = v15++;
                *(ArrayPtr + v44) = 0;
              }
              break;
          }
        }
        else
        {
          v37 = v15++;
          *(ArrayPtr + v37) = v36;
        }
      }
    }
    while ( v15 < v32 );
    v31 = v51;
  }
  sub_5BC44(*a4, *a5, (v31 + 257), *a4);
  sub_5BC44(*a6, *a7, (*a2 + 1), *a6);
  sub_5C208(v29);
  return 0i64;
}
