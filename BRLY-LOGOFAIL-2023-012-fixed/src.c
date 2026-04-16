unsigned __int64 __fastcall DecodeTGA(
        targa_header *Image,
        __int64 ImageData,
        __int64 *a3,
        unsigned __int64 *a4,
        _QWORD *a5,
        _QWORD *a6,
        _DWORD *a7,
        _BYTE *a8)
{
  unsigned __int64 v8; // rbx
  char x; // al
  unsigned __int64 Size; // rsi
  __int64 v14; // rcx
  __int64 v15; // rax
  unsigned __int64 v16; // rbp
  __int64 v17; // rcx
  __int64 v18; // rax
  __int64 v20; // rsi
  __int64 *v21; // r12
  int v22; // edx
  __int64 v23; // r11
  int v24; // r8d
  char *v25; // r8
  unsigned __int64 v26; // r11
  _BYTE *v27; // r9
  __int64 v28; // r10
  _BYTE *v29; // rdx
  char v30; // al
  __int16 *v31; // rdx
  char *v32; // r9
  char v33; // al
  __int16 *v34; // r9
  __int16 *v35; // r15
  char v36; // al
  unsigned __int64 v37; // r10
  __int64 v38; // r11
  __int16 *v39; // rdx
  char *v40; // r9
  char v41; // al
  int width; // edx
  __int64 v43; // r14
  char *v44; // r10
  char *v45; // r9
  int v46; // eax
  __int64 v47; // rcx
  char *v48; // r15
  unsigned __int64 v49; // r12
  char *j; // rbp
  char *v51; // r9
  int v52; // eax
  __int64 v53; // rax
  __int64 v54; // rbp
  unsigned __int64 v55; // r12
  __int64 i; // r15
  __int64 v57; // rax
  __int64 v58; // [rsp+60h] [rbp+8h]
  unsigned __int8 v59; // [rsp+68h] [rbp+10h]

  v8 = 0i64;
  if ( !Image || !a5 || !a6 || !a7 || !a8 )
    return 0x8000000000000002ui64;
  if ( ((Image->image_type - 2) & 0xF7) != 0 || Image->map_type > 1u )
    return 0x8000000000000003ui64;
  x = Image->x;
  switch ( x )
  {
    case 16:
      *a7 = 0;
      break;
    case 24:
      *a7 = 1;
      *a8 = 0;
      goto LABEL_15;
    case 32:
      *a7 = 2;
      break;
    default:
      *a7 = 3;
      *a8 = 0;
      return 0x8000000000000003ui64;
  }
  *a8 = 1;
LABEL_15:
  unsigned int height = (unsigned int)Image->height;
  unsigned int width_ = (unsigned int)Image->width;
  Size = 4ull * (height * width_);
  if ( Size >= 0x100000000ull )
    return 0x8000000000000003ui64;
  if ( *a3 )
  {
    v16 = *a4;
    if ( *a4 < Size )
    {
      *a4 = Size;
      return 0x8000000000000005ui64;
    }
  }
  else
  {
    *a4 = Size;
    if ( sub_DD0() )
      v15 = sub_E6C(v14, (Size >> 12) + ((Size & 0xFFF) != 0));
    else
      v15 = sub_EA4(v14, Size);
    *a3 = v15;
    if ( !v15 )
      return 0x8000000000000009ui64;
    v16 = *a4;
  }
  if ( sub_DD0() )
    v18 = sub_E6C(v17, (v16 >> 12) + ((v16 & 0xFFF) != 0));
  else
    v18 = sub_EA4(v17, v16);
  v20 = v18;
  if ( !v18 )
    return 0x8000000000000009ui64;
  *a5 = Image->height;
  *a6 = Image->width;
  v21 = a3;
  v22 = (SHIBYTE(Image->map_first) >> 32) & 7;
  v23 = *a3;
  v24 = SHIBYTE(Image->map_first) / 8;
  v58 = *a3;
  if ( ((v22 + SHIBYTE(Image->map_first)) & 7) != v22 )
    ++v24;
  v25 = &Image->x + Image->map_type * *(&Image->map_first + 1) * v24 + Image->id_length + 2;
  v59 = SLOBYTE(Image->x) / 8;
  if ( Image->image_type != 2 )
  {
    if ( Image->image_type != 10 )
      goto LABEL_85;
    v26 = 0i64;
    if ( !(height * width_) )
      goto LABEL_84;
    while ( 1 )
    {
      v27 = (v20 + 4 * v26);
      v28 = *v25 & 0x7F;
      v29 = v25 + 1;
      if ( v27 && v25 != -1i64 )
      {
        if ( *a7 )
        {
          if ( *a7 == 1 )
          {
            *v27 = *v29;
            v27[1] = v25[2];
            v27[2] = v25[3];
            v27[3] = 0;
            goto LABEL_43;
          }
          if ( *a7 != 2 )
            goto LABEL_43;
          *v27 = *v29;
          v27[1] = v25[2];
          v27[2] = v25[3];
          v30 = v25[4];
        }
        else
        {
          *v27 = 8 * *v29;
          v27[1] = (v25[2] << 6) | (v25[1] >> 2) & 0x38;
          v27[2] = 2 * (v25[2] & 0xFC);
          v30 = v25[2] & 0x80;
        }
        v27[3] = v30;
      }
LABEL_43:
      ++v26;
      if ( *v25 < 0 )
      {
        if ( !v28 )
        {
LABEL_69:
          v25 += v59 + 1;
          goto LABEL_70;
        }
        v34 = (v20 + 4 * v26 + 2);
        v26 += v28;
        while ( 2 )
        {
          v35 = v34 - 1;
          if ( v34 != &word_2 && v25 != -1i64 )
          {
            if ( *a7 )
            {
              if ( *a7 == 1 )
              {
                *v35 = *v29;
                *(v34 - 1) = v25[2];
                *v34 = v25[3];
                *(v34 + 1) = 0;
              }
              else if ( *a7 == 2 )
              {
                *v35 = *v29;
                *(v34 - 1) = v25[2];
                *v34 = v25[3];
                v36 = v25[4];
                goto LABEL_67;
              }
            }
            else
            {
              *v35 = 8 * *v29;
              *(v34 - 1) = (v25[2] << 6) | (v25[1] >> 2) & 0x38;
              *v34 = 2 * (v25[2] & 0xFC);
              v36 = v25[2] & 0x80;
LABEL_67:
              *(v34 + 1) = v36;
            }
          }
          v34 += 2;
          if ( !--v28 )
            goto LABEL_69;
          continue;
        }
      }
      v25 += v59 + 1;
      if ( v28 )
      {
        v31 = (v20 + 4 * v26 + 2);
        v26 += v28;
        while ( 1 )
        {
          v32 = (v31 - 1);
          if ( v31 == &word_2 || !v25 )
            goto LABEL_55;
          if ( !*a7 )
            break;
          if ( *a7 == 1 )
          {
            *v32 = *v25;
            *(v31 - 1) = v25[1];
            *v31 = v25[2];
            *(v31 + 1) = 0;
          }
          else if ( *a7 == 2 )
          {
            *v32 = *v25;
            *(v31 - 1) = v25[1];
            *v31 = v25[2];
            v33 = v25[3];
LABEL_54:
            *(v31 + 1) = v33;
          }
LABEL_55:
          v25 += v59;
          v31 += 2;
          if ( !--v28 )
            goto LABEL_70;
        }
        *v32 = 8 * *v25;
        *(v31 - 1) = (v25[1] << 6) | (*v25 >> 2) & 0x38;
        *v31 = 2 * (v25[1] & 0xFC);
        v33 = v25[1] & 0x80;
        goto LABEL_54;
      }
LABEL_70:
      if ( v26 >= height * width_ )
      {
        v21 = a3;
        goto LABEL_84;
      }
    }
  }
  v37 = 0i64;
  if ( !(height * width_) )
    goto LABEL_85;
  v38 = (SLOBYTE(Image->x) / 8);
  v39 = (v18 + 2);
  do
  {
    v40 = (v39 - 1);
    if ( v39 != &word_2 && v25 )
    {
      if ( *a7 )
      {
        if ( *a7 == 1 )
        {
          *v40 = *v25;
          *(v39 - 1) = v25[1];
          *v39 = v25[2];
          *(v39 + 1) = 0;
          goto LABEL_83;
        }
        if ( *a7 != 2 )
          goto LABEL_83;
        *v40 = *v25;
        *(v39 - 1) = v25[1];
        *v39 = v25[2];
        v41 = v25[3];
      }
      else
      {
        *v40 = 8 * *v25;
        *(v39 - 1) = (v25[1] << 6) | (*v25 >> 2) & 0x38;
        *v39 = 2 * (v25[1] & 0xFC);
        v41 = v25[1] & 0x80;
      }
      *(v39 + 1) = v41;
    }
LABEL_83:
    v25 += v38;
    ++v37;
    v39 += 2;
  }
  while ( v37 < height * width_ );
LABEL_84:
  v23 = v58;
LABEL_85:
  width = (int)width_;
  v43 = 4i64 * width;
  switch ( (BYTE1(Image->x) >> 4) & 3 )
  {
    case 0:
      v54 = v20;
      v55 = 0i64;
      for ( i = v23 + 4i64 * (Image->height - 1) * width; v55 < Image->height; v54 += v57 )
      {
        if ( v43 && i != v54 )
          CopyMem(i, v54, v43);
        ++v55;
        v57 = 4i64 * width;
        i -= v57;
      }
      goto LABEL_109;
    case 1:
      v48 = v20;
      v49 = 0i64;
      for ( j = (v23 + 4i64 * (Image->height - 1) * width); v49 < Image->height; v48 += v53 )
      {
        if ( v43 && j != v48 )
        {
          CopyMem(j, v48, v43);
          LOWORD(width) = width;
        }
        v51 = j;
        v25 = &j[4 * width - 4];
        if ( j < v25 )
        {
          do
          {
            v52 = *v51;
            *v51 = *v25;
            v51 += 4;
            *v25 = v52;
            v25 -= 4;
          }
          while ( v51 < v25 );
          LOWORD(width) = width;
        }
        ++v49;
        v53 = 4i64 * width;
        j -= v53;
      }
LABEL_109:
      v47 = v20;
      goto LABEL_110;
    case 2:
      goto LABEL_94;
    case 3:
      v44 = v20;
      if ( height )
      {
        do
        {
          v45 = v44;
          v25 = &v44[4 * width - 4];
          if ( v44 < v25 )
          {
            do
            {
              v46 = *v45;
              *v45 = *v25;
              v45 += 4;
              *v25 = v46;
              v25 -= 4;
            }
            while ( v45 < v25 );
            LOWORD(width) = width;
          }
          ++v8;
          v44 += 4 * width;
        }
        while ( v8 < height );
      }
LABEL_94:
      *v21 = v20;
      v47 = v23;
LABEL_110:
      sub_E20(v47, *a4, v25);
      break;
  }
  return 0i64;
}
