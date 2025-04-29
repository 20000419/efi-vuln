__int64 __fastcall InitJfif(_BYTE *Image, __int64 ImageSize)
{
  UINT8 *ImagePtr; // rbx
  UINT8 *EndPtr; // rdi
  int v6; // eax
  _BYTE *v7; // r8
  unsigned int v8; // r9d
  int v9; // edx
  unsigned __int8 v10; // al
  __int64 v11; // rcx
  __int64 v12; // rdx
  int v13; // edx
  UINT8 v14; // r8
  __int64 result; // rax
  unsigned __int64 Skip; // rax

  sub_310(SOIPtr, 3064i64, 0i64);
  if ( *Image != 0xD8FF )
    return 1i64;
  ImagePtr = Image + 2;
  SOIPtr[0] = Image;
  EndPtr = &Image[ImageSize];
  
  // Vulnerability here: while (ImagePtr < (Image + ImageSize)
  // It is possible that *(ImagePtr + 2)/*(ImagePtr + 3) will exceed the buffer boundary
  // (when ImagePtr = Image + ImageSize - 3)
  // So we will have OOB read access here:

  // if ( ImagePtr[2] == 0xFF )
  //   Skip = 2i64;
  // else
  //   Skip = (ImagePtr[2] << 8) + ImagePtr[3] + 2i64;  
  if ( ImagePtr >= EndPtr )
    return 0i64;
  while ( 1 )
  {
    if ( *ImagePtr == 0xFF )
    {
      v6 = ImagePtr[1];
      if ( v6 )
        break;
    }
    Skip = 1i64;
LABEL_40:
    ImagePtr += Skip;
    if ( ImagePtr >= EndPtr )
      return 0i64;
  }
  if ( v6 > 0xC0u && v6 != 0xC4 && v6 <= 0xCFu )
    return 6i64;
  switch ( v6 )
  {
    case 0xC0:
      qword_2218 = ImagePtr;
      result = sub_62C(ImagePtr);
LABEL_35:
      if ( result )
        return result;
      goto LABEL_36;
    case 0xC4:
      result = sub_71C(ImagePtr);
      goto LABEL_35;
    case 0xDA:                                  // JPEG_SOS
      SOSPtr = ImagePtr;
      v12 = ImagePtr[3] + (ImagePtr[2] << 8);
      if ( ((ImagePtr[4] - 1) & 0xFD) != 0 || ImagePtr[(v12 - 1)] || ImagePtr[v12] != 63 || ImagePtr[(v12 + 1)] )
        return 5i64;
      v13 = 0;
      if ( ImagePtr[4] )
      {
        while ( ImagePtr[2 * v13 + 5] <= 3u )
        {
          v14 = ImagePtr[2 * v13 + 6];
          if ( (v14 & 0xF0u) > 0x10 || (v14 & 0xFu) > 1 )
            break;
          if ( ++v13 >= ImagePtr[4] )
            goto LABEL_36;
        }
        return 5i64;
      }
      goto LABEL_36;
  }
  if ( v6 != 219 )
  {
    switch ( v6 )
    {
      case 221:
        word_21E8 = ImagePtr[5] + (ImagePtr[4] << 8);
        break;
      case 224:
        qword_21C8 = ImagePtr;
        break;
      case 254:
        qword_21D8 = ImagePtr;
        break;
    }
    goto LABEL_36;
  }
  v7 = ImagePtr + 4;
  v8 = 0;
  v9 = (ImagePtr[3] - 2 + (ImagePtr[2] << 8)) / 65;
  if ( !v9 )
  {
LABEL_36:
    if ( ImagePtr[2] == 0xFF )
      Skip = 2i64;
    else
      Skip = (ImagePtr[2] << 8) + ImagePtr[3] + 2i64;
    goto LABEL_40;
  }
  while ( 1 )
  {
    v10 = *v7 & 0xF;
    if ( v10 > 3u || (*v7 & 0xF0) != 0 )
      return 3i64;
    v11 = (v7 + 1);
    v7 += 65;
    ++v8;
    SOIPtr[v10 + 6] = v11;
    if ( v8 >= v9 )
      goto LABEL_36;
  }
}
