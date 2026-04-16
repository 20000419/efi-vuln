EFI_STATUS __fastcall DbDecodeImage(BUFFER_INDICATOR *Bi, EFI_IMAGE_INPUT *ImageInput)
{
  // ... (existing variable declarations and initializations) ...

  ImageBuffer = malloc(ImageSize);             
  if (ImageBuffer)
  {
    Start_plus_ImageOffset = (char *)Bi->Start + Bfh.ImageOffset;
    Bi->Current = Start_plus_ImageOffset;
    
    // Validate image data size before reading
    if ((void *)((unsigned __int64)Start_plus_ImageOffset + ImageSize) <= (char *)Bi->Start + Bi->BufferSize)
      BiReadBuffer(Bi, ImageBuffer, &ScratchedBufferSize, Start_plus_ImageOffset);

    Height = Bih.Height;
    i = 0;
    PixelPtr = ImageInput->Bitmap;
    ImageIndex = 0i64;
    Color.Reserved = 0;

    if (!Bih.Height)
      goto exit;

    Width = Bih.Width;

    // Validate image dimensions are positive
    if (Width == 0 || Height == 0)
      return EFI_INVALID_PARAMETER;

    while (1)
    {
      j = 0;
      if (Width)
        break;
LABEL_40:
      if (ImageIndex & 3)
        v39 = 4 - (ImageIndex & 3);
      else
        v39 = 0;
      
      // Prevent ImageIndex from exceeding ImageSize during alignment
      if (ImageIndex + v39 >= ImageSize)
        return EFI_INVALID_PARAMETER;
        
      ImageIndex += v39;
      if (++i >= Height)
        goto exit;
    }

    while (1)
    {
      if (Bih.BitsPerPixel == 1)              // 2 Color Mode
      {
        BitIndex = 7i64;
        while (j < Width)
        {
          // Bound check for ImageIndex before buffer access
          if (ImageIndex >= ImageSize)
            return EFI_INVALID_PARAMETER;
            
          PaletteIndex = ((unsigned __int64)*((unsigned __int8 *)ImageBuffer + ImageIndex) >> BitIndex) & 1;
          *(_WORD *)&Color.Green = *(_WORD *)&Palette[PaletteIndex].Green;
          Color.Blue = Palette[PaletteIndex].Blue;
          v38 = j++;
          --BitIndex;
          PixelPtr[v38 + Width * (Height - i - 1)] = Color;
        }
        --j;
        
        // Bound check before incrementing ImageIndex
        if (ImageIndex + 1 >= ImageSize)
          return EFI_INVALID_PARAMETER;
          
        ImageIndex++;
        goto LABEL_39;
      }

      if (Bih.BitsPerPixel == 4)              // 16 Color Mode
        break;

      switch (Bih.BitsPerPixel)
      {
        case 8u:                                // 256 Color Mode
          // Bound check before accessing ImageBuffer
          if (ImageIndex >= ImageSize)
            return EFI_INVALID_PARAMETER;
            
          v32 = *((unsigned __int8 *)ImageBuffer + ImageIndex);
          ImageIndex++;
          
          // Additional check after increment (if needed for next access)
          if (ImageIndex > ImageSize)
            return EFI_INVALID_PARAMETER;
            
          *(_WORD *)&Color.Green = *(_WORD *)&Palette[v32].Green;
          v30 = Palette[v32].Blue;
          // ... (remaining pixel processing) ...
          break;

        case 0x18u:                             // 16M Color Mode
          // Check for triple-byte access bounds
          if (ImageIndex + 3 >= ImageSize)
            return EFI_INVALID_PARAMETER;
            
          *(_WORD *)&Color.Green = *(_WORD *)((char *)ImageBuffer + ImageIndex + 1);
          v30 = *((_BYTE *)ImageBuffer + ImageIndex);
          ImageIndex += 3;
          // ... (remaining pixel processing) ...
          break;

        case 0x20u:                             // 32-bit Color Mode
          // Check for 4-byte access bounds
          if (ImageIndex + 4 > ImageSize)
            return EFI_INVALID_PARAMETER;
            
          v29 = *(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)((char *)ImageBuffer + ImageIndex);
          ImageIndex += 4;
          // ... (remaining pixel processing) ...
          break;
      }

LABEL_39:
      if (++j >= Width)
        goto LABEL_40;
    }

    // Handle 4-bit color mode nibble accesses with bounds checks
    if (ImageIndex >= ImageSize)
      return EFI_INVALID_PARAMETER;
      
    v33 = (unsigned __int64)*((unsigned __int8 *)ImageBuffer + ImageIndex) >> 4;
    LOBYTE(v33) = *((_BYTE *)ImageBuffer + ImageIndex);
    
    // Additional check after initial access
    if (ImageIndex + 1 >= ImageSize)
      return EFI_INVALID_PARAMETER;
      
    ImageIndex++;
    v35 = v33 & 0xF;
    // ... (remaining pixel processing) ...
  }

  // ... (existing cleanup and return) ...
}
