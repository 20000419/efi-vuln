unsigned __int64 __fastcall DecodeBMP(
        BMP_IMAGE *Image,
        unsigned __int64 ImageSize,
        __int64 *a3,
        unsigned __int64 *a4,
        _QWORD *a5,
        _QWORD *a6)
{
  __int64 PixelWidth;
  __int64 BitPerPixel;
  __int64 PixelHeight;
  unsigned __int64 v12;
  __int64 ImageOffset;
  unsigned int v14;
  int v15;
  UINT32 NumberOfColors;
  CHAR8 *v17;
  unsigned __int64 v18;
  __int64 v19;
  __int64 v20;
  __int64 v22;
  unsigned __int64 v23;
  unsigned __int64 v24;
  __int64 v25;
  unsigned __int64 v26;
  CHAR8 *v27;
  __int64 v28;
  CHAR8 v29;
  CHAR8 v30;
  __int64 v31;
  unsigned __int64 v32;
  __int64 v33;
  unsigned __int64 v34;
  char v35;
  unsigned __int64 v36;
  __int64 v37;
  char v38;
  char v39;

  if (ImageSize < 0x36)
    return 0x8000000000000002ui64;
  if (Image->BmpHeader.CharB != 66 || Image->BmpHeader.CharM != 77 || 
      Image->BmpHeader.CompressionType > 2 || Image->BmpHeader.HeaderSize != 40)
  {
    return 0x8000000000000003ui64;
  }
  PixelWidth = Image->BmpHeader.PixelWidth;
  BitPerPixel = Image->BmpHeader.BitPerPixel;
  PixelHeight = Image->BmpHeader.PixelHeight;
  v12 = PixelHeight * (((unsigned int)(BitPerPixel * Image->BmpHeader.PixelWidth + 31) >> 3) & 0x1FFFFFFC);
  if (v12 > 0xFFFFFFFF)
    return 0x8000000000000002ui64;

  ImageOffset = Image->BmpHeader.ImageOffset;
  if (ImageOffset >= ImageSize)
    return 0x8000000000000002ui64;

  if ((unsigned int)ImageOffset < 0x36)
    return 0x8000000000000002ui64;

  v14 = 0;
  if ((unsigned int)ImageOffset > 0x36)
  {
    BitPerPixel = (unsigned int)(BitPerPixel - 1);
    if ((_DWORD)BitPerPixel)
    {
      BitPerPixel = (unsigned int)(BitPerPixel - 3);
      if ((_DWORD)BitPerPixel)
      {
        if ((_DWORD)BitPerPixel == 4)
          v15 = 256;
        else
          v15 = 0;
      }
      else
      {
        v15 = 16;
      }
    }
    else
    {
      v15 = 2;
    }
    NumberOfColors = Image->BmpHeader.NumberOfColors;
    if (!NumberOfColors)
      NumberOfColors = v15;
    v14 = NumberOfColors;
    v12 = 4i64 * NumberOfColors;
    if (ImageOffset - 54 < v12)
      return 0x8000000000000002ui64;
  }

  v17 = (CHAR8 *)Image + ImageOffset;
  v38 = (_BYTE)Image + ImageOffset;

  if ((unsigned __int64)(PixelHeight * PixelWidth) > 0x3FFFFFFFFFFFFFFFi64)
    return 0x8000000000000003ui64;
  v18 = 4 * PixelHeight * PixelWidth;
  if (v18 >= 0x100000000i64)
    return 0x8000000000000003ui64;
  v39 = 0;
  if (*a3)
  {
    if (*a4 < v18)
    {
      *a4 = v18;
      return 0x8000000000000005ui64;
    }
  }
  else
  {
    *a4 = v18;
    if ((unsigned __int8)sub_D5C(v12, BitPerPixel, ImageOffset, PixelWidth))
      v20 = sub_DAC(v19, (v18 >> 12) + ((v18 & 0xFFF) != 0));
    else
      v20 = sub_DE4(v19, v18);
    *a3 = v20;
    v39 = 1;
    if (!v20)
      return 0x8000000000000009ui64;
    LODWORD(PixelWidth) = Image->BmpHeader.PixelWidth;
  }

  *a6 = (unsigned int)PixelWidth;
  *a5 = Image->BmpHeader.PixelHeight;
  v22 = *a3;

  if (Image->BmpHeader.CompressionType == 1)
  {
    if (v18)
      sub_330(*a3, v18, 0i64);
    sub_740(v22, v17, &Image->field_36, Image);
    return 0i64;
  }
  if (Image->BmpHeader.CompressionType == 2)
  {
    if (v18)
      sub_330(*a3, v18, 0i64);
    sub_540(v22, v17, &Image->field_36, Image);
    return 0i64;
  }

  v23 = Image->BmpHeader.PixelHeight;
  v24 = 0i64;
  if (!(_DWORD)v23)
    return 0i64;

  while (1)
  {
    v25 = Image->BmpHeader.PixelWidth;
    v26 = 0i64;
    v27 = (CHAR8 *)(v22 + 4 * v25 * ((unsigned int)v23 - v24 - 1));
    if ((_DWORD)v25)
      break;
    if ((((unsigned __int8)v17 - (unsigned __int8)Image) & 3) != 0)
      v17 += 4i64 - ((((unsigned __int8)v17 - (unsigned __int8)Image) & 3));
    ++v24;
    v23 = Image->BmpHeader.PixelHeight;
    if (v24 >= v23)
      return 0i64;
  }

  while (1)
  {
    switch (Image->BmpHeader.BitPerPixel)
    {
      case 1u:
        v34 = 0i64;
        do
        {
          if (v26 >= Image->BmpHeader.PixelWidth)
            break;
          v23 = ((unsigned __int8)*v17 >> (7 - v34)) & 1;
          if ((unsigned int)v23 >= v14)
            return 0x8000000000000002ui64;
          ++v26;
          v35 = 7 - v34++;
          v27[2] = *((_BYTE *)&Image->field_36 + 4 * (((unsigned __int64)(unsigned __int8)*v17 >> v35) & 1) + 2);
          v27[1] = *((_BYTE *)&Image->field_36 + 4 * (((unsigned __int64)(unsigned __int8)*v17 >> v35) & 1) + 1);
          *v27 = *((_BYTE *)&Image->field_36 + 4 * (((unsigned __int64)(unsigned __int8)*v17 >> v35) & 1));
          v27 += 4;
        } while (v34 < 8);
        v27 -= 4;
        --v26;
        goto LABEL_61;
      case 4u:
        v32 = (unsigned __int64)(unsigned __int8)*v17 >> 4;
        if ((unsigned int)v32 >= v14)
          return 0x8000000000000002ui64;
        v27[2] = *((_BYTE *)&Image->field_36 + 4 * v32 + 2);
        v27[1] = *((_BYTE *)&Image->field_36 + 4 * v32 + 1);
        *v27 = *((_BYTE *)&Image->field_36 + 4 * v32);
        if (v26 < Image->BmpHeader.PixelWidth - 1)
        {
          v27 += 4;
          v33 = *v17 & 0xF;
          ++v26;
          if ((unsigned int)v33 >= v14)
            return 0x8000000000000002ui64;
          v27[2] = *((_BYTE *)&Image->field_36 + 4 * v33 + 2);
          v27[1] = *((_BYTE *)&Image->field_36 + 4 * v33 + 1);
          *v27 = *((_BYTE *)&Image->field_36 + 4 * v33);
        }
        goto LABEL_61;
      case 8u:
        v31 = (unsigned __int8)*v17;
        if ((unsigned int)v31 >= v14)
          return 0x8000000000000002ui64;
        v27[2] = *((_BYTE *)&Image->field_36 + 4 * v31 + 2);
        v27[1] = *((_BYTE *)&Image->field_36 + 4 * (unsigned __int8)*v17 + 1);
        *v27 = *((_BYTE *)&Image->field_36 + 4 * (unsigned __int8)*v17);
        goto LABEL_61;
      case 0x10u:
        *v27 = (8 * *v17) | ((unsigned __int8)*v17 >> 2) & 7;
        v27[1] = (8 * (*(_WORD *)v17 >> 5)) | (*(_WORD *)v17 >> 7) & 7;
        v27[2] = (8 * (*(_WORD *)v17 >> 10)) | (*(_WORD *)v17 >> 12) & 7;
        ++v17;
        goto LABEL_61;
    }
    v28 = (unsigned int)Image->BmpHeader.BitPerPixel - 24;
    if (Image->BmpHeader.BitPerPixel == 24)
    {
      *v27 = *v17;
      v30 = v17[1];
      v17 += 2;
      v27[1] = v30;
      v27[2] = *v17;
      goto LABEL_61;
    }
    if (Image->BmpHeader.BitPerPixel != 32)
      break;
    *v27 = *v17;
    v27[1] = v17[1];
    v29 = v17[2];
    v17 += 3;
    v27[2] = v29;
LABEL_61:
    ++v26;
    ++v17;
    v27 += 4;
    if (v26 >= Image->BmpHeader.PixelWidth)
      goto LABEL_62;
  }

  if (v39)
  {
    v36 = *a4;
    v37 = *a3;
    if ((unsigned __int8)sub_D5C(v28, v23, v27, v26))
      (*(void (__fastcall **)(__int64, unsigned __int64))(qword_EA0 + 48))(v37, (v36 >> 12) + ((v36 & 0xFFF) != 0));
    else
      (*(void (__fastcall **)(__int64))(qword_EA0 + 72))(v37);
    *a3 = 0i64;
  }

  return 0x8000000000000003ui64;
}
