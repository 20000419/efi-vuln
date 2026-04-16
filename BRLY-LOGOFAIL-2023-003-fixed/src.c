__int64 __fastcall DecodeRLE4(
        EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltOutput,
        unsigned __int8 *a2,
        __int64 a3,
        BMP_IMAGE *Image)
{
  unsigned __int64 PixelHeight;
  char v5;
  __int64 v6;
  __int64 PixelWidth;
  unsigned __int64 v12;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL *BltEntry;
  char v14;
  __int64 v15;
  unsigned __int8 *v16;
  int v17;
  unsigned __int64 v18;
  unsigned __int64 v19;
  __int64 v20;
  __int64 v21;
  __int16 v22;
  __int64 v23;
  unsigned int v24;
  unsigned __int8 v25;
  unsigned __int64 v26;

  PixelHeight = Image->BmpHeader.PixelHeight;
  v5 = 0;
  v6 = 0i64;

  // Validate PixelHeight to prevent negative indices
  if (PixelHeight == 0)
    return 0i64;

  while (!v5)
  {
    PixelWidth = Image->BmpHeader.PixelWidth;
    v12 = 0i64;
    
    // Calculate vertical index safely
    unsigned __int64 verticalIndex = PixelHeight - v6 - 1;
    if (verticalIndex >= PixelHeight)
      break; // Prevent out-of-bounds access
    
    BltEntry = &BltOutput[PixelWidth * verticalIndex];
    v14 = 0;
    
    while (!v14)
    {
      v15 = *a2;
      v16 = a2 + 1;
      v17 = a2[1];
      a2 += 2;
      
      if ((_BYTE)v15)
      {
        v18 = (unsigned int)v15;
        unsigned __int8 highNibble = (unsigned __int8)v17 >> 4;
        v19 = 0i64;
        v12 += v15;
        
        // Validate horizontal write bounds
        if (v12 > PixelWidth)
          return 0x8000000000000002ui64;
        
        do
        {
          v20 = v19++ & 1;
          v21 = (unsigned __int8)(highNibble >> (4 * v20));
          
          // Write pixel data with palette lookup
          BltEntry->Red = *(_BYTE *)(a3 + 4 * v21 + 2);
          BltEntry->Green = *(_BYTE *)(a3 + 4 * v21 + 1);
          BltEntry->Blue = *(_BYTE *)(a3 + 4 * v21);
          ++BltEntry;
        } while (v19 < v18);
      }
      else
      {
        if ((_BYTE)v17)
        {
          if (v17 != 1)
          {
            if (v17 == 2)
            {
              v12 += *a2;
              v6 += v16[2];
              a2 = v16 + 3;
              
              // Recalculate vertical index after jump
              verticalIndex = PixelHeight - v6 - 1;
              if (verticalIndex >= PixelHeight)
                break; // Prevent out-of-bounds after jump
              
              BltEntry = &BltOutput[v12 + PixelWidth * verticalIndex];
            }
            else
            {
              v22 = (v17 - 1) / 4 + 1;
              v23 = (unsigned __int16)(2 * v22);
              
              if (v23)
              {
                do
                {
                  v24 = *a2++;
                  v25 = v24 & 0xF;
                  
                  if ((_BYTE)v17)
                  {
                    ++v12;
                    v26 = (unsigned __int64)v24 >> 4;
                    
                    // Validate horizontal write before palette lookup
                    if (v12 > PixelWidth)
                      return 0x8000000000000002ui64;
                      
                    BltEntry->Red = *(_BYTE *)(a3 + 4 * v26 + 2);
                    BltEntry->Green = *(_BYTE *)(a3 + 4 * v26 + 1);
                    BltEntry->Blue = *(_BYTE *)(a3 + 4 * v26);
                    ++BltEntry;
                    LOBYTE(v17) = v17 - 1;
                    
                    if ((_BYTE)v17)
                    {
                      ++v12;
                      
                      // Validate horizontal write before palette lookup
                      if (v12 > PixelWidth)
                        return 0x8000000000000002ui64;
                        
                      BltEntry->Red = *(_BYTE *)(a3 + 4 * v25 + 2);
                      BltEntry->Green = *(_BYTE *)(a3 + 4 * v25 + 1);
                      BltEntry->Blue = *(_BYTE *)(a3 + 4 * v25);
                      ++BltEntry;
                      LOBYTE(v17) = v17 - 1;
                    }
                  }
                  --v23;
                } while (v23);
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
      if (v12 > PixelWidth)
        break; // Prevent out-of-bounds horizontal access
    }
    
    PixelHeight = Image->BmpHeader.PixelHeight;
    if (++v6 >= PixelHeight) // Fix loop termination condition
      break;
  }
  return 0i64;
}
