unsigned __int64 sub_59844()
{
  unsigned int length; // ebx
  bool v1; // zf
  int width; // ecx
  int height; // eax
  void *ZeroPool; // rax
  unsigned __int64 result; // rax
  void *OutputBufferVar; // rax
  __int64 v7; // rcx

  // Validate PngWidth and PngHeight to prevent overflow and invalid dimensions
  if (PngWidth == 0 || PngHeight == 0 || PngWidth > 0x7FFFFFFF || PngHeight > 0x7FFFFFFF)
    return 0x8000000000000003ui64;

  length = 0;
  if (ColorType)
  {
    switch (ColorType)
    {
      case 2:
        v1 = ((BitDepth - 8) & 0xFFFFFFF7) == 0;
        break;
      case 3:
        v1 = ((BitDepth - 4) & 0xFFFFFFFB) == 0;
        break;
      case 4:
      case 6:
        v1 = BitDepth == 8;
        break;
      default:
        return 0x8000000000000003ui64;
    }
    if (v1)
      goto LABEL_8;
    return 0x8000000000000003ui64;
  }
  if (BitDepth != 1 && BitDepth != 8)
    return 0x8000000000000003ui64;
LABEL_8:
  width = PngWidth;
  height = PngHeight;
  dword_9733C = width;
  dword_97340 = height;
  if (dword_97350 == 1 && qword_97348)
  {
    sub_4654(&qword_97348);
    height = dword_97340;
    width = dword_9733C;
    qword_97348 = 0i64;
  }

  // Validate dimensions before allocation
  const unsigned int MAX_DIMENSION = 0x7FFFFFFF; // Adjust based on system limits
  if (width > MAX_DIMENSION || height > MAX_DIMENSION)
    return 0x8000000000000003ui64;

  ZeroPool = AllocateZeroPool(4 * (unsigned int)width * (unsigned int)height);
  if (!ZeroPool)
    return 0x8000000000000009ui64;

  dword_97358 = -1;
  qword_97348 = (__int64)ZeroPool;
  dword_9735C = 0;
  dword_97354 = 0;
  qword_97364 = 0i64;
  dword_97360 = 1;
  dword_9737C = 0;
  dword_97380 = 1;
  if (OutputBuffer)
    sub_4654(&OutputBuffer);

  switch (ColorType)
  {
    case 0:
      if (BitDepth != 1)
      {
        if (BitDepth != 2)
        {
          if (BitDepth != 4)
          {
            if (BitDepth != 8)
            {
              if (BitDepth != 16)
                goto LABEL_47;
              // Check for overflow in 6 * width (BitDepth 16 for case 0 is not standard, but add check)
              if (width > MAX_DIMENSION / 6)
                return 0x8000000000000003ui64;
              length = 6 * (unsigned int)width;
            }
            else
            {
              // BitDepth 8
              if (width > MAX_DIMENSION / 3) // 3 * width for BitDepth 8
                return 0x8000000000000003ui64;
              length = 3 * (unsigned int)width;
            }
          }
          else
          {
            // BitDepth 4
            if (width > MAX_DIMENSION / 2 - 1) // (width + 1) >> 1
              return 0x8000000000000003ui64;
            length = (unsigned int)(width + 1) >> 1;
          }
        }
        else
        {
          // BitDepth 2
          if (width > MAX_DIMENSION / 4 - 3) // (width + 3) >> 2
            return 0x8000000000000003ui64;
          length = (unsigned int)(width + 3) >> 2;
        }
      }
      else
      {
        // BitDepth 1
        if (width > MAX_DIMENSION * 8) // (width + 7) >> 3 is width/8 rounded up
          return 0x8000000000000003ui64;
        length = (unsigned int)(width + 7) >> 3;
      }
      goto LABEL_47;
    case 2:
      if (BitDepth == 8)
      {
        if (width > MAX_DIMENSION / 3) // 3 * width
          return 0x8000000000000003ui64;
        length = 3 * (unsigned int)width;
      }
      else if (BitDepth == 16)
      {
        if (width > MAX_DIMENSION / 6) // 6 * width
          return 0x8000000000000003ui64;
        length = 6 * (unsigned int)width;
      }
      goto LABEL_47;
    case 3:
      if (BitDepth != 1)
      {
        if (BitDepth != 2)
        {
          if (BitDepth != 4)
          {
            if (BitDepth != 8)
              goto LABEL_47;
            // Same as case 0 BitDepth 8
            if (width > MAX_DIMENSION / 3)
              return 0x8000000000000003ui64;
            length = 3 * (unsigned int)width;
          }
          else
          {
            // BitDepth 4
            if (width > MAX_DIMENSION / 2 - 1)
              return 0x8000000000000003ui64;
            length = (unsigned int)(width + 1) >> 1;
          }
        }
        else
        {
          // BitDepth 2
          if (width > MAX_DIMENSION / 4 - 3)
            return 0x8000000000000003ui64;
          length = (unsigned int)(width + 3) >> 2;
        }
      }
      else
      {
        // BitDepth 1
        if (width > MAX_DIMENSION * 8)
          return 0x8000000000000003ui64;
        length = (unsigned int)(width + 7) >> 3;
      }
      goto LABEL_47;
  }
  if (ColorType != 4)
  {
    if (ColorType == 6)
    {
      if (BitDepth != 8)
      {
        if (BitDepth == 16)
        {
          if (width > MAX_DIMENSION / 8) // 8 * width
            return 0x8000000000000003ui64;
          length = 8 * (unsigned int)width;
        }
        goto LABEL_47;
      }
      else
      {
        // BitDepth 8 for ColorType 6
        if (width > MAX_DIMENSION / 4) // 4 * width (RGBA)
          return 0x8000000000000003ui64;
        length = 4 * (unsigned int)width;
      }
    }
    goto LABEL_47;
  }
  else
  {
    // ColorType 4 (grayscale with alpha)
    if (BitDepth == 8)
    {
      if (width > MAX_DIMENSION / 2) // 2 * width
        return 0x8000000000000003ui64;
        length = 2 * (unsigned int)width;
    }
    else if (BitDepth == 16)
    {
      if (width > MAX_DIMENSION / 4) // 4 * width
        return 0x8000000000000003ui64;
      length = 4 * (unsigned int)width;
    }
  }
LABEL_47:
  // Validate length and prevent overflow in 2 * length
  const unsigned int MAX_ALLOCATION = 0x7FFFFFFF; // Adjust based on system's max allocation size
  if (length == 0 || 2 * length > MAX_ALLOCATION)
    return 0x8000000000000003ui64;

  OutputBufferVar = AllocateZeroPool(2 * length);
  if (!OutputBufferVar)
    return 0x8000000000000009ui64;

  v7 = (__int64)OutputBufferVar + length;
  OutputBuffer = (__int64)OutputBufferVar;
  qword_97390 = (__int64)OutputBufferVar;
  result = 0i64;
  qword_97398 = v7;
  return result;
}
