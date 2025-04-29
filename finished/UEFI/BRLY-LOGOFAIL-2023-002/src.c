__int64 __fastcall DecodeRLE8(
        EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltOutput,
        unsigned __int8 *a2,
        __int64 a3,
        BMP_IMAGE *Image)
{
  unsigned __int64 PixelHeight; // rax
  char v5; // r15
  unsigned __int64 i; // r11
  __int64 PixelWidth; // rbx
  unsigned __int64 v11; // r9
  char v12; // bp
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltEntry; // r8
  __int64 v14; // rax
  unsigned __int8 *v15; // rsi
  __int64 v16; // r10
  __int64 v17; // rcx
  char v18; // si
  __int64 v19; // rax

  PixelHeight = Image->BmpHeader.PixelHeight;
  v5 = 0;
  for ( i = 0i64; i <= PixelHeight; ++i )
  {
    if ( v5 )
      break;
    PixelWidth = Image->BmpHeader.PixelWidth;
    v11 = 0i64;
    v12 = 0;
    // BRLY-LOGOFAIL-2023-002
    BltEntry = &BltOutput[PixelWidth * (PixelHeight - i - 1)];
    do
    {
      if ( v12 )
        break;
      v14 = *a2;
      v15 = a2 + 1;
      v16 = a2[1];
      a2 += 2;
      if ( (_BYTE)v14 )
      {
        v17 = (unsigned int)v14;
        v11 += v14;
        do
        {
          BltEntry->Red = *(_BYTE *)(a3 + 4 * v16 + 2);// arbitrary write
          BltEntry->Green = *(_BYTE *)(a3 + 4 * v16 + 1);// arbitrary write
          BltEntry->Blue = *(_BYTE *)(a3 + 4 * v16);// arbitrary write
          ++BltEntry;
          --v17;
        }
        while ( v17 );
      }
      else if ( (_BYTE)v16 )
      {
        if ( (_DWORD)v16 == 1 )
        {
          v5 = 1;
          v12 = 1;
        }
        else if ( (_DWORD)v16 == 2 )
        {
          v11 += *a2;
          i += v15[2];
          a2 = v15 + 3;
          BltEntry = &BltOutput[v11 + (unsigned int)PixelWidth * (Image->BmpHeader.PixelHeight - i - 1)];
        }
        else
        {
          v11 += v16;
          v18 = v16;
          do
          {
            v19 = *a2++;
            BltEntry->Red = *(_BYTE *)(a3 + 4 * v19 + 2);
            BltEntry->Green = *(_BYTE *)(a3 + 4i64 * (unsigned int)v19 + 1);
            BltEntry->Blue = *(_BYTE *)(a3 + 4i64 * (unsigned int)v19);
            ++BltEntry;
            --v16;
          }
          while ( v16 );
          if ( (v18 & 1) != 0 )
            ++a2;
        }
      }
      else
      {
        v12 = 1;
      }
      LODWORD(PixelWidth) = Image->BmpHeader.PixelWidth;
    }
    while ( v11 <= (unsigned int)PixelWidth );
    PixelHeight = Image->BmpHeader.PixelHeight;
  }
  return 0i64;
}
Where DecodeRLE8 function will be called from the DecodeBMP function:
if ( Image->BmpHeader.CompressionType == 1 )
{
    if ( v18 )
      sub_330(*a3, v18, 0i64);
    DecodeRLE8(v22, v17, &Image->field_36, Image);
    return 0i64;
}
}
