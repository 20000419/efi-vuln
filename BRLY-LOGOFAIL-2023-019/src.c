unsigned __int64 __fastcall sub_33FE4(
        __int64 a1,
        unsigned int a2,
        _QWORD *a3,
        UINTN *a4,
        unsigned int *a5,
        unsigned int *a6)
{
  __int64 v8; // rbx
  __int64 height; // rcx
  __int64 width; // rax
  UINTN size; // rcx
  _BYTE *ZeroPool; // rax MAPDST
  unsigned int i; // r8d
  unsigned int j; // r9d
  __int64 v16; // rdx
  _BYTE *v17; // rdx

  dword_973A0 = sub_186A0;
  dword_97330 = 0x7FFFFFFF;
  dword_97334 = 0x7FFFFFFF;
  dword_97338 = 0x7FFFFFFF;
  v8 = 0i64;
  if ( DecodePNG(a1, a2) )
    return 0x8000000000000015ui64;
  height = Height;
  width = Width;
  *a5 = Height;
  *a6 = width;
  size = 4 * width * height;
  *a4 = size;
  ZeroPool = AllocateZeroPool(size);
  *a3 = ZeroPool;
  if ( !ZeroPool )
    return 0x8000000000000009ui64;
  for ( i = 0; i < *a5; ++i )
  {
    for ( j = 0; j < *a6; ZeroPool += 4 )
    {
      if ( j >= Width )
        v16 = 4 * Width * (i + 1) - 4;
      else
        v16 = 4 * (j + i * Width);
      v17 = (DecodedImg + v16);
      ++j;
      *ZeroPool = v17[2];
      ZeroPool[1] = v17[1];
      ZeroPool[2] = *v17;
    }
  }
  return v8;
}
