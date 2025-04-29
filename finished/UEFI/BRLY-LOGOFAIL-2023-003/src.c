__int64 __fastcall DecodeRLE4(
        EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltOutput,
        unsigned __int8 *a2,
        __int64 a3,
        BMP_IMAGE *Image)
{
  unsigned __int64 PixelHeight; // rax
  char v5; // r12
  __int64 v6; // rdi
  __int64 PixelWidth; // rbx
  unsigned __int64 v12; // r11
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltEntry; // r9
  char v14; // r15
  __int64 v15; // rcx
  unsigned __int8 *v16; // r14
  int v17; // r8d
  unsigned __int64 v18; // rdx
  unsigned __int64 v19; // r8
  __int64 v20; // rcx
  __int64 v21; // rcx
  __int16 v22; // ax
  __int64 v23; // rbx
  unsigned int v24; // eax
  unsigned __int8 v25; // dl
  unsigned __int64 v26; // rcx
  char v28; // [rsp+49h] [rbp+21h]

  PixelHeight = Image->BmpHeader.PixelHeight;
  v5 = 0;
  v6 = 0i64;
  while ( !v5 )
  {
    PixelWidth = Image->BmpHeader.PixelWidth;
    v12 = 0i64;
    BltEntry = &BltOutput[PixelWidth * (PixelHeight - v6 - 1)];
    v14 = 0;
    while ( !v14 )
    {
      v15 = *a2;
      v16 = a2 + 1;
      v17 = a2[1];
      a2 += 2;
      if ( (_BYTE)v15 )
      {
        v18 = (unsigned int)v15;
        v28 = (unsigned __int8)v17 >> 4;
        v19 = 0i64;
        v12 += v15;
        do
        {
          v20 = v19++ & 1;
          v21 = (unsigned __int8)*(&v28 - v20);
          BltEntry->Red = *(_BYTE *)(a3 + 4 * v21 + 2);
          BltEntry->Green = *(_BYTE *)(a3 + 4 * v21 + 1);
          BltEntry->Blue = *(_BYTE *)(a3 + 4 * v21);
          ++BltEntry;
        }
        while ( v19 < v18 );
      }
      else
      {
        if ( (_BYTE)v17 )
        {
          if ( v17 != 1 )
          {
            if ( v17 == 2 )
            {
              v12 += *a2;
              v6 += v16[2];
              a2 = v16 + 3;
              // BRLY-LOGOFAIL-2023-003
              BltEntry = &BltOutput[v12 + (unsigned int)PixelWidth * (Image->BmpHeader.PixelHeight - v6 - 1)];
            }
            else
            {
              v22 = (v17 - 1) / 4 + 1;
              v23 = (unsigned __int16)(2 * v22);
              if ( 2 * v22 )
              {
                do
                {
                  v24 = *a2++;
                  v25 = v24 & 0xF;
                  if ( (_BYTE)v17 )
                  {
                    ++v12;
                    v26 = (unsigned __int64)v24 >> 4;
                    BltEntry->Red = *(_BYTE *)(a3 + 4 * v26 + 2); // arbitrary write
                    BltEntry->Green = *(_BYTE *)(a3 + 4 * v26 + 1); // arbitrary write
                    BltEntry->Blue = *(_BYTE *)(a3 + 4 * v26); // arbitrary write
                    ++BltEntry;
                    LOBYTE(v17) = v17 - 1;
                    if ( (_BYTE)v17 )
                    {
                      ++v12;
                      BltEntry->Red = *(_BYTE *)(a3 + 4i64 * v25 + 2);
                      BltEntry->Green = *(_BYTE *)(a3 + 4i64 * v25 + 1);
                      BltEntry->Blue = *(_BYTE *)(a3 + 4i64 * v25);
                      ++BltEntry;
                      LOBYTE(v17) = v17 - 1;
                    }
                  }
                  --v23;
                }
                while ( v23 );
              }
            }
            goto LABEL_21;
          }
          v5 = 1;
        }
        v14 = 1;
      }
LABEL_21:
      LODWORD(PixelWidth) = Image->BmpHeader.PixelWidth;
      if ( v12 > (unsigned int)PixelWidth )
        break;
    }
    PixelHeight = Image->BmpHeader.PixelHeight;
    if ( ++v6 > PixelHeight )
      return 0i64;
  }
  return 0i64;
}
