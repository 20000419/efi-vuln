unsigned __int64 sub_59844()
{
  unsigned int length; // ebx
  bool v1; // zf
  int width; // ecx
  int heigth; // eax
  void *ZeroPool; // rax
  unsigned __int64 result; // rax
  void *OutputBufferVar; // rax
  __int64 v7; // rcx

  length = 0;
  if ( ColorType )
  {
    switch ( ColorType )
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
    if ( v1 )
      goto LABEL_8;
    return 0x8000000000000003ui64;
  }
  if ( BitDepth != 1 && BitDepth != 8 )
    return 0x8000000000000003ui64;
LABEL_8:
  width = PngWidth;
  heigth = PngHeight;
  dword_9733C = PngWidth;
  dword_97340 = PngHeight;
  if ( dword_97350 == 1 && qword_97348 )
  {
    sub_4654(&qword_97348);
    heigth = dword_97340;
    width = dword_9733C;
    qword_97348 = 0i64;
  }
  ZeroPool = AllocateZeroPool(4 * width * heigth);
  dword_97358 = -1;
  qword_97348 = (__int64)ZeroPool;
  dword_9735C = 0;
  dword_97354 = 0;
  qword_97364 = 0i64;
  dword_97360 = 1;
  dword_9737C = 0;
  dword_97380 = 1;
  if ( OutputBuffer )
    sub_4654(&OutputBuffer);
  switch ( ColorType )
  {
    case 0:
      if ( BitDepth != 1 )
      {
        if ( BitDepth != 2 )
        {
          if ( BitDepth != 4 )
          {
            if ( BitDepth != 8 )
            {
              if ( BitDepth != 16 )
                goto LABEL_47;
              goto LABEL_43;
            }
LABEL_33:
            length = PngWidth;
            goto LABEL_47;
          }
LABEL_44:
          length = (unsigned int)(PngWidth + 1) >> 1;
          goto LABEL_47;
        }
LABEL_45:
        length = (unsigned int)(PngWidth + 3) >> 2;
        goto LABEL_47;
      }
LABEL_46:
      length = (unsigned int)(PngWidth + 7) >> 3;
      goto LABEL_47;
    case 2:
      if ( BitDepth == 8 )
      {
        length = 3 * PngWidth;
      }
      else if ( BitDepth == 16 )
      {
        length = 6 * PngWidth;
      }
      goto LABEL_47;
    case 3:
      if ( BitDepth != 1 )
      {
        if ( BitDepth != 2 )
        {
          if ( BitDepth != 4 )
          {
            if ( BitDepth != 8 )
              goto LABEL_47;
            goto LABEL_33;
          }
          goto LABEL_44;
        }
        goto LABEL_45;
      }
      goto LABEL_46;
  }
  if ( ColorType != 4 )
  {
    if ( ColorType == 6 )
    {
      if ( BitDepth != 8 )
      {
        if ( BitDepth == 16 )
          length = 8 * PngWidth;
        goto LABEL_47;
      }
      goto LABEL_28;
    }
    goto LABEL_47;
  }
  if ( BitDepth == 8 )
  {
LABEL_43:
    length = 2 * PngWidth;
    goto LABEL_47;
  }
  if ( BitDepth == 16 )
LABEL_28:
    length = 4 * PngWidth;
LABEL_47:
  // BRLY-LOGOFAIL-2023-016: Integer overflow on the argument of EfiLibAllocateZeroPool  
  OutputBufferVar = AllocateZeroPool(2 * length);
  v7 = (__int64)OutputBufferVar + length;
  OutputBuffer = (__int64)OutputBufferVar;
  qword_97390 = (__int64)OutputBufferVar;
  result = 0i64;
  qword_97398 = v7;
  return result;
}
