unsigned __int64 __fastcall DecodeBMP(
        BMP_IMAGE_HEADER *Image,
        __int64 ImageSize,
        __int64 *a3,
        unsigned __int64 *a4,
        unsigned __int64 *a5,
        unsigned __int64 *a6)
{
  CHAR8 *v8; // rdi
  unsigned __int64 v9; // rcx
  unsigned __int64 v10; // rax
  __int64 v11; // rax
  unsigned __int64 v13; // r11
  unsigned __int64 PixelWidth; // rdx
  unsigned __int64 PixelHeight; // rcx
  unsigned __int64 v16; // r10
  __int64 v17; // rsi
  unsigned __int64 v18; // r9
  CHAR8 *v19; // r8
  CHAR8 v20; // al
  CHAR8 v21; // al
  unsigned __int64 v22; // rcx
  __int64 v23; // rcx
  __int64 v24; // rcx
  CHAR8 CharB; // al
  UINT32 ImageOffset; // eax

  if ( *(_WORD *)&Image->CharB != 'MB' )
    return 0x8000000000000003ui64;
  if ( Image->CompressionType )
    return 0x8000000000000003ui64;
  
  // Validate ImageOffset to prevent out-of-bounds access
  if (Image->ImageOffset >= (unsigned __int64)ImageSize || 
      Image->ImageOffset < sizeof(BMP_IMAGE_HEADER))
    return 0x8000000000000003ui64;

  v8 = &Image->CharB + Image->ImageOffset;
  v9 = Image->PixelWidth * (unsigned __int64)Image->PixelHeight;
  if ( v9 >= 0x40000000 )
    return 0x8000000000000003ui64;
  v10 = 4 * v9;
  if ( *a3 )
  {
    if ( *a4 < v10 )
    {
      *a4 = v10;
      return 0x8000000000000005ui64;
    }
  }
  else
  {
    *a4 = v10;
    v11 = sub_500C(4 * v9);
    *a3 = v11;
    if ( !v11 )
      return 0x8000000000000009ui64;
  }
  v13 = 0i64;
  PixelWidth = Image->PixelWidth;
  PixelHeight = Image->PixelHeight;
  v16 = PixelWidth;
  v17 = *a3;
  *a6 = PixelWidth;
  *a5 = PixelHeight;
  if ( (_DWORD)PixelHeight )
  {
    do
    {
      v18 = 0i64;
      v19 = (CHAR8 *)(v17 + 4 * v16 * (PixelHeight - v13 - 1));
      if ( (_DWORD)PixelWidth )
      {
        do
        {
          switch ( Image->BitPerPixel )
          {
            case 1u:
              v24 = 8i64;
              do
              {
                if ( ((unsigned __int8)(1 << --v24) & (unsigned __int8)*v8) != 0 )
                {
                  v19[2] = Image[1].Reserved[0];
                  v19[1] = HIBYTE(Image[1].Size);
                  CharB = BYTE2(Image[1].Size);
                }
                else
                {
                  v19[2] = Image[1].Size;
                  v19[1] = Image[1].CharM;
                  CharB = Image[1].CharB;
                }
                *v19 = CharB;
                if ( v18 < Image->PixelWidth )
                {
                  v19 += 4;
                  ++v18;
                }
              }
              while ( v24 );
              v19 -= 4;
              --v18;
              break;
            case 4u:
              v22 = (unsigned __int64)(unsigned __int8)*v8 >> 4;
              v19[2] = *((_BYTE *)&Image[1].Size + 4 * v22);
              v19[1] = *(&Image[1].CharM + 4 * v22);
              *v19 = *(&Image[1].CharB + 4 * v22);
              if ( v18 < Image->PixelWidth - 1 )
              {
                v19 += 4;
                ++v18;
                v23 = *v8 & 0xF;
                v19[2] = *((_BYTE *)&Image[1].Size + 4 * v23);
                v19[1] = *(&Image[1].CharM + 4 * v23);
                *v19 = *(&Image[1].CharB + 4 * v23);
              }
              break;
            case 8u:
              v19[2] = *((_BYTE *)&Image[1].Size + 4 * (unsigned __int8)*v8);
              v19[1] = *(&Image[1].CharM + 4 * (unsigned __int8)*v8);
              *v19 = *(&Image[1].CharB + 4 * (unsigned __int8)*v8);
              break;
            case 0x18u:
              *v19 = *v8;
              v21 = v8[1];
              v8 += 2;
              v19[1] = v21;
              v19[2] = *v8;
              break;
            default:
              if ( Image->BitPerPixel != 32 || Image->CompressionType )
                return 0x8000000000000003ui64;
              *v19 = *v8;
              v19[1] = v8[1];
              v20 = v8[2];
              v8 += 3;
              v19[2] = v20;
              break;
          }
          PixelWidth = Image->PixelWidth;
          ++v18;
          ++v8;
          v19 += 4;
          v16 = PixelWidth;
        }
        while ( v18 < PixelWidth );
      }
      ImageOffset = Image->ImageOffset;
      if ( (((_BYTE)v8 - (_BYTE)ImageOffset) & 3) != 0 )
        v8 += 4i64 - (((_BYTE)v8 - (_BYTE)ImageOffset) & 3);
      PixelHeight = Image->PixelHeight;
      ++v13;
    }
    while ( v13 < PixelHeight );
  }
  return 0i64;
}
