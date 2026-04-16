EFI_STATUS __fastcall DbDecodeImage(BUFFER_INDICATOR *Bi, EFI_IMAGE_INPUT *ImageInput)
{
  // ... (existing variable declarations and initializations) ...

  if ( (unsigned __int16)(BitsPerPixel - 1) <= 7u )
  {
    PaletteSize = 4 * ColorAmount;
    Palette = (BMP_COLOR_PALETTE *)malloc(PaletteSize);
    if ( !Palette )
      return EFI_OUT_OF_RESOURCES;

    Start_plus_BmpHeaderSize = (char *)Bi->Start + BmpHeaderSize;
    Start_plus_BufferSize_1 = (char *)Bi->Start + Bi->BufferSize;
    Bi->Current = Start_plus_BmpHeaderSize;
    
    // Validate palette data size before reading
    if ( (char *)Start_plus_BmpHeaderSize + PaletteSize <= Start_plus_BufferSize_1 )
      BiReadBuffer(Bi, Palette, &PaletteSize, (char *)Start_plus_BmpHeaderSize);
  }

  // ... (existing buffer allocation and initialization) ...

  while ( 1 )
  {
    if ( Bih.BitsPerPixel == 1 )              // 2 Color Mode
    {
      BitIndex = 7i64;
      while ( j < Width )
      {
        PaletteIndex = ((unsigned __int64)*((unsigned __int8 *)ImageBuffer + ImageIndex) >> BitIndex) & 1;
        
        // Validate palette index for 1-bit mode (0 or 1)
        if (PaletteIndex >= ColorAmount)
          return EFI_INVALID_PARAMETER;
        
        *(_WORD *)&Color.Green = *(_WORD *)&Palette[PaletteIndex].Green;
        Color.Blue = Palette[PaletteIndex].Blue;
        // ... (remaining pixel processing) ...
      }
      // ... (remaining loop logic) ...
    }

    if ( Bih.BitsPerPixel == 4 )              // 16 Color Mode
      break;

    switch ( Bih.BitsPerPixel )
    {
      case 8u:                                // 256 Color Mode
        v32 = *((unsigned __int8 *)ImageBuffer + ImageIndex);
        ImageIndex = (unsigned int)(ImageIndex + 1);
        
        // Validate palette index for 8-bit mode (0-255)
        if (v32 >= ColorAmount)
          return EFI_INVALID_PARAMETER;
        
        *(_WORD *)&Color.Green = *(_WORD *)&Palette[v32].Green;
        v30 = Palette[v32].Blue;
        // ... (remaining pixel processing) ...
        break;

      // ... (other color modes unchanged) ...
    }

    // ... (additional 4-bit mode processing with nibble indices) ...
    v33 = (unsigned __int64)*((unsigned __int8 *)ImageBuffer + ImageIndex) >> 4;
    v35 = v33 & 0xF;

    // Validate palette indices for 4-bit mode (0-15)
    if (v33 >= ColorAmount || v35 >= ColorAmount)
      return EFI_INVALID_PARAMETER;

    *(_WORD *)&Color.Green = *(_WORD *)&Palette[v33].Green;
    Color.Blue = Palette[v33].Blue;
    // ... (remaining pixel processing) ...
  }

  // ... (existing cleanup and return) ...
}
