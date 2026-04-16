// local variable allocation has failed, the output may be wrong!
EFI_STATUS __fastcall DbDecodeImage(BUFFER_INDICATOR *Bi, EFI_IMAGE_INPUT *ImageInput)
{
  UINTN BufferSize; // rcx
  BMP_COLOR_PALETTE *Palette; // r15
  EFI_STATUS Status; // rsi
  void *Start; // rax
  void *Current; // rcx
  char *Start_plus_BMP_FILE_HEADER; // rax
  char *Start_plus_BufferSize; // rcx
  size_t ImageSize; // rdi
  __int64 BmpHeaderSize; // r12
  __int64 ColorAmount; // r14
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL *mem; // rax
  UINT16 BitsPerPixel; // cx
  size_t PaletteSize; // r14 MAPDST
  void *Start_plus_BmpHeaderSize; // rax
  void *Start_plus_BufferSize_1; // rcx
  void *ImageBuffer; // rax MAPDST
  void *Start_plus_ImageOffset; // rcx
  UINT32 Height; // er8
  int i; // ebx
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL *PixelPtr; // rdi
  __int64 ImageIndex; // r9
  UINT32 Width; // er11
  UINT32 j; // er10
  unsigned __int64 offset; // rcx
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL v29; // eax
  UINT8 v30; // al
  __int64 index; // rcx
  __int64 v32; // rcx
  unsigned __int64 v33; // rcx
  __int64 v34; // rax
  unsigned __int64 v35; // rcx
  __int64 BitIndex; // r12
  unsigned __int64 PaletteIndex; // rdx
  __int64 v38; // rax
  int v39; // eax
  BMP_FILE_HEADER Bfh; // [rsp+20h] [rbp-40h]
  BMP_INFO_HEADER Bih; // [rsp+30h] [rbp-30h]
  UINT64 ScratchedBufferSize; // [rsp+A0h] [rbp+40h] OVERLAPPED
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL Color; // [rsp+A0h] [rbp+40h] FORCED

  BufferSize = Bi->BufferSize;
  Bfh.ImageOffset = 0;
  Palette = 0i64;
  Bih.BitsPerPixel = 0;
  Status = 0i64;
  Bih.ImageSize = 0;
  *(_QWORD *)&Bih.HeaderSize = 0i64;
  Bih.Height = 0;
  if ( BufferSize <= 0x36 )
    return Status;
  Start = Bi->Start;
  Bi->Current = Bi->Start;
  ScratchedBufferSize = sizeof(BMP_FILE_HEADER);
  if ( (char *)Start + sizeof(BMP_FILE_HEADER) > (char *)Start + BufferSize )
    return Status;
  if ( BiReadBuffer(Bi, &Bfh, &ScratchedBufferSize, (char *)Start + sizeof(BMP_FILE_HEADER)) )
    return Status;
  Current = Bi->Start;
  ScratchedBufferSize = sizeof(BMP_INFO_HEADER);
  Start_plus_BMP_FILE_HEADER = (char *)Current + sizeof(BMP_FILE_HEADER);
  Start_plus_BufferSize = (char *)Current + Bi->BufferSize;
  Bi->Current = Start_plus_BMP_FILE_HEADER;
  if ( Start_plus_BMP_FILE_HEADER + sizeof(BMP_INFO_HEADER) > Start_plus_BufferSize
    || BiReadBuffer(Bi, &Bih, &ScratchedBufferSize, Start_plus_BMP_FILE_HEADER + sizeof(BMP_INFO_HEADER))
    || Bfh.BmpId[0] != 'B'
    || Bfh.BmpId[1] != 'M' )
  {
    return Status;
  }
  ImageSize = Bih.ImageSize;
  BmpHeaderSize = Bih.HeaderSize + sizeof(BMP_FILE_HEADER);
  ColorAmount = 1 << SLOBYTE(Bih.BitsPerPixel);
  ScratchedBufferSize = Bih.ImageSize;
  mem = (EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)malloc(4i64 * Bih.Height * Bih.Width);
  ImageInput->Bitmap = mem;
  if ( !mem )
    return EFI_OUT_OF_RESOURCES;
  BitsPerPixel = Bih.BitsPerPixel;
  ImageInput->Height = Bih.Height;
  ImageInput->Width = Bih.Width;
  if ( !ImageSize )
  {
    ImageSize = Bih.Height * ((((BitsPerPixel * (unsigned __int64)Bih.Width) >> 3) + 3) & 0xFFFFFFFC);
    ScratchedBufferSize = Bih.Height * ((((BitsPerPixel * (unsigned __int64)Bih.Width) >> 3) + 3) & 0xFFFFFFFC);
  }
  if ( (unsigned __int16)(BitsPerPixel - 1) <= 7u )
  {
    PaletteSize = 4 * ColorAmount;
    Palette = (BMP_COLOR_PALETTE *)malloc(PaletteSize);
    if ( !Palette )
      return EFI_OUT_OF_RESOURCES;
    Start_plus_BmpHeaderSize = (char *)Bi->Start + BmpHeaderSize;
    Start_plus_BufferSize_1 = (char *)Bi->Start + Bi->BufferSize;
    Bi->Current = Start_plus_BmpHeaderSize;
    if ( (char *)Start_plus_BmpHeaderSize + PaletteSize <= Start_plus_BufferSize_1 )
      BiReadBuffer(Bi, Palette, &PaletteSize, (char *)Start_plus_BmpHeaderSize + PaletteSize);
  }
  ImageBuffer = malloc(ImageSize);              // Root cause #3: OOB index. Lack of synchronization between ImageSize and ImageIndex.
  if ( ImageBuffer )
  {
    Start_plus_ImageOffset = (char *)Bi->Start + Bfh.ImageOffset;
    Bi->Current = Start_plus_ImageOffset;
    if ( (void *)((unsigned __int64)Start_plus_ImageOffset + ImageSize) <= (char *)Bi->Start + Bi->BufferSize )
      BiReadBuffer(Bi, ImageBuffer, &ScratchedBufferSize, (char *)Start_plus_ImageOffset + ImageSize);
    Height = Bih.Height;
    i = 0;
    PixelPtr = ImageInput->Bitmap;
    ImageIndex = 0i64;
    Color.Reserved = 0;
    if ( !Bih.Height )
      goto exit;
    Width = Bih.Width;
    while ( 1 )
    {
      j = 0;
      if ( Width )
        break;
LABEL_40:
      if ( ImageIndex & 3 )
        v39 = 4 - (ImageIndex & 3);
      else
        v39 = 0;
      ImageIndex = (unsigned int)(v39 + ImageIndex);
      if ( ++i >= Height )
        goto exit;
    }
    while ( 1 )
    {
      if ( Bih.BitsPerPixel == 1 )              // 2 Color Mode
                                                // CRASH area
      {
        BitIndex = 7i64;
        while ( j < Width )
        {
          PaletteIndex = ((unsigned __int64)*((unsigned __int8 *)ImageBuffer + ImageIndex) >> BitIndex) & 1;// OOB read Root Cause #3
          *(_WORD *)&Color.Green = *(_WORD *)&Palette[PaletteIndex].Green;
          Color.Blue = Palette[PaletteIndex].Blue;
          v38 = j++;
          --BitIndex;
          PixelPtr[v38 + Width * (Height - i - 1)] = Color;
          Height = Bih.Height;
          Width = Bih.Width;
        }
        --j;
        ImageIndex = (unsigned int)(ImageIndex + 1);
        goto LABEL_39;
      }
      if ( Bih.BitsPerPixel == 4 )              // 16 Color Mode
        break;
      switch ( Bih.BitsPerPixel )
      {
        case 8u:                                // 256 Color Mode
                                                // CRASH case x2
          v32 = *((unsigned __int8 *)ImageBuffer + ImageIndex);// OOB read Root Cause #3
          ImageIndex = (unsigned int)(ImageIndex + 1);
          *(_WORD *)&Color.Green = *(_WORD *)&Palette[v32].Green;
          v30 = Palette[v32].Blue;
LABEL_30:
          index = Width * (Height - i - 1);
LABEL_33:
          Color.Blue = v30;
          offset = j + index;
          v29 = Color;
          goto LABEL_34;
        case 0x18u:                             // 16M Color Mode
          *(_WORD *)&Color.Green = *(_WORD *)((char *)ImageBuffer + ImageIndex + 1);// OOB read Root Cause #3
          v30 = *((_BYTE *)ImageBuffer + ImageIndex);// OOB read Root Cause #3
          ImageIndex = (unsigned int)(ImageIndex + 3);
          goto LABEL_30;
        case 0x20u:                             // CRASH case
          offset = j + (unsigned __int64)(Width * (Height - i - 1));
          v29 = *(EFI_GRAPHICS_OUTPUT_BLT_PIXEL *)((char *)ImageBuffer + ImageIndex);// OOB read Root Cause #3
          ImageIndex = (unsigned int)(ImageIndex + 4);
LABEL_34:
          PixelPtr[offset] = v29;
          Height = Bih.Height;
          Width = Bih.Width;
          break;
      }
LABEL_39:
      if ( ++j >= Width )
        goto LABEL_40;
    }
    v33 = (unsigned __int64)*((unsigned __int8 *)ImageBuffer + ImageIndex) >> 4;// OOB read Root Cause #3
    *(_WORD *)&Color.Green = *(_WORD *)&Palette[v33].Green;
    Color.Blue = Palette[v33].Blue;
    v34 = j++;
    PixelPtr[v34 + Width * (Height - i - 1)] = Color;
    LOBYTE(v33) = *((_BYTE *)ImageBuffer + ImageIndex);// OOB read Root Cause #3
    ImageIndex = (unsigned int)(ImageIndex + 1);
    v35 = v33 & 0xF;
    *(_WORD *)&Color.Green = *(_WORD *)&Palette[v35].Green;
    v30 = Palette[v35].Blue;
    index = Bih.Width * (Bih.Height - i - 1);
    goto LABEL_33;
  }
  Status = EFI_OUT_OF_RESOURCES;
exit:
  if ( Palette )
    gEfiBootServices->FreePool(Palette);
  if ( ImageBuffer )
    gEfiBootServices->FreePool(ImageBuffer);
  return Status;
}
