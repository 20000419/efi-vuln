unsigned __int8 *GetImageSize()
{
  unsigned int ImageSize; // ebx
  unsigned __int8 *result; // rax
  __int64 ImagePtrCursor; // r9
  unsigned __int8 *v3; // rcx
  __int64 v4; // r10
  __int64 v5; // r9
  unsigned __int8 *v6; // rcx
  __int64 v7; // rdx
  unsigned int Length; // r11d
  unsigned __int8 *v9; // [rsp+30h] [rbp+8h] BYREF

  ImageSize = 8;
  GlobalImagePtr += 8i64;
  result = (unsigned __int8 *)AllocateZeroPool(4ui64);
  v9 = result;
  if ( result )
  {
    ImagePtrCursor = GlobalImagePtr;
    do
    {
      v3 = result;
      v4 = 4i64;
      do
      {
        *v3 = v3[ImagePtrCursor - (_QWORD)result];
        ++v3;
        --v4;
      }
      while ( v4 );
      v5 = ImagePtrCursor + 4;
      v6 = result;
      v7 = 4i64;
      // BRLY-LOGOFAIL-2023-014: Chunk length is added without validation to ImagePtrCursor
      Length = result[3] + ((result[2] + ((result[1] + (*result << 8)) << 8)) << 8);
      do
      {
        *v6 = v6[v5 - (_QWORD)result];
        ++v6;
        --v7;
      }
      while ( v7 );
      ImageSize += Length + 12;
      ImagePtrCursor = Length + 8i64 + v5;
    }
    while ( result[3] + ((result[2] + ((result[1] + (*result << 8)) << 8)) << 8) != 1229278788 );
    GlobalImagePtr = ImagePtrCursor;
    sub_4654(&v9);
    return (unsigned __int8 *)ImageSize;
  }
  return result;
}
