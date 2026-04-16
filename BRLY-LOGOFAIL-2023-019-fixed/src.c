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
  _BYTE *ZeroPoolBase; // r12
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
  
  // Validate width and height to prevent integer overflow
  if (width <= 0 || height <= 0)
    return 0x8000000000000003ui64;
  
  size = 4 * (UINTN)width * (UINTN)height;
  if (size < 4 || size / 4 != (UINTN)width * (UINTN)height)
    return 0x8000000000000003ui64;
  
  *a5 = height;
  *a6 = width;
  *a4 = size;
  
  ZeroPool = AllocateZeroPool(size);
  ZeroPoolBase = ZeroPool;
  *a3 = ZeroPool;
  
  if ( !ZeroPool )
    return 0x8000000000000009ui64;
  
  for ( i = 0; i < *a5; ++i )
  {
    for ( j = 0; j < *a6; ++j )
    {
      if ( j >= width )
        v16 = 4 * width * (i + 1) - 4;
      else
        v16 = 4 * (j + i * width);
      
      v17 = (DecodedImg + v16);
      
      // Ensure we don't write beyond the allocated buffer
      if ((UINTN)(ZeroPool - ZeroPoolBase) + 3 >= size)
        return 0x800000000000000Bui64;
      
      *ZeroPool = v17[2];
      ZeroPool[1] = v17[1];
      ZeroPool[2] = *v17;
      ZeroPool += 4;
    }
  }
  return v8;
}
