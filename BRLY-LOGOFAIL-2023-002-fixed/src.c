__int64 __fastcall DecodeRLE8(
        EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltOutput,
        unsigned __int8 *a2,
        __int64 a3,
        BMP_IMAGE *Image)
{
  unsigned __int64 PixelHeight;
  char v5;
  unsigned __int64 i;
  __int64 PixelWidth;
  unsigned __int64 v11;
  char v12;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltEntry;
  __int64 v14;
  unsigned __int8 *v15;
  __int64 v16;
  __int64 v17;
  char v18;
  __int64 v19;

  PixelHeight = Image->BmpHeader.PixelHeight;
  v5 = 0;
  
  // Prevent negative height and off-by-one loop error
  if (PixelHeight == 0)
    return 0i64;

  for (i = 0i64; i < PixelHeight; ++i)  // Changed loop condition from <= to <
  {
    if (v5)
      break;
    PixelWidth = Image->BmpHeader.PixelWidth;
    v11 = 0i64;
    v12 = 0;
    
    // Calculate valid non-negative index
    unsigned __int64 yIndex = PixelHeight - i - 1;
    if (yIndex >= PixelHeight)  // Additional safety check
      continue;
    
    BltEntry = &BltOutput[PixelWidth * yIndex];
    
    do
    {
      if (v12)
        break;
      v14 = *a2;
      v15 = a2 + 1;
      v16 = a2[1];
      a2 += 2;
      
      if ((_BYTE)v14)
      {
        v17 = (unsigned int)v14;
        v11 += v14;
        
        // Validate horizontal write bounds
        if (v11 > PixelWidth)
          return 0x8000000000000002ui64;
        
        do
        {
          BltEntry->Red = *(_BYTE *)(a3 + 4 * v16 + 2);
          BltEntry->Green = *(_BYTE *)(a3 + 4 * v16 + 1);
          BltEntry->Blue = *(_BYTE *)(a3 + 4 * v16);
          ++BltEntry;
          --v17;
        } while (v17);
      }
      else if ((_BYTE)v16)
      {
        if ((_DWORD)v16 == 1)
        {
          v5 = 1;
          v12 = 1;
        }
        else if ((_DWORD)v16 == 2)
        {
          v11 += *a2;
          i += v15[2];  // Risky vertical jump - consider additional bounds checks here
          a2 = v15 + 3;
          
          // Recalculate yIndex after vertical jump to prevent negative values
          yIndex = PixelHeight - i - 1;
          if (yIndex >= PixelHeight)
            return 0x8000000000000002ui64;
          
          BltEntry = &BltOutput[v11 + PixelWidth * yIndex];
        }
        else
        {
          v11 += v16;
          v18 = v16;
          
          if (v11 > PixelWidth)
            return 0x8000000000000002ui64;
          
          do
          {
            v19 = *a2++;
            BltEntry->Red = *(_BYTE *)(a3 + 4 * v19 + 2);
            BltEntry->Green = *(_BYTE *)(a3 + 4 * v19 + 1);
            BltEntry->Blue = *(_BYTE *)(a3 + 4 * v19);
            ++BltEntry;
            --v16;
          } while (v16);
          if ((v18 & 1) != 0)
            ++a2;
        }
      }
      else
      {
        v12 = 1;
      }
      LODWORD(PixelWidth) = Image->BmpHeader.PixelWidth;
    } while (v11 <= (unsigned int)PixelWidth);
    PixelHeight = Image->BmpHeader.PixelHeight;
  }
  return 0i64;
}
