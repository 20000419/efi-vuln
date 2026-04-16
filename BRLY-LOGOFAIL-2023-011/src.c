unsigned __int64 __fastcall DecodePCX(
        PCXHeader *Image,
        __int64 ImageSize,
        __int64 *a3,
        unsigned __int64 *a4,
        _QWORD *a5,
        unsigned __int64 *a6)
{
  __int64 v6; // rbx
  unsigned __int64 v8; // r14
  __int64 Index; // rbp
  unsigned __int64 v10; // rsi
  __int64 v11; // r15
  char *v12; // rdx
  unsigned __int64 i; // rcx
  char v14; // al
  unsigned __int64 v15; // r15
  __int64 v16; // rcx
  __int64 v17; // rax
  __int64 v18; // rdx
  __int64 v19; // rcx
  __int64 v20; // r8
  __int64 v21; // r9
  __int64 v22; // r12
  unsigned __int64 v23; // r14
  __int64 v24; // rcx
  __int64 v25; // rax
  __int64 v26; // rdx
  unsigned __int64 v27; // rcx
  unsigned __int64 v28; // r8
  EFI_PHYSICAL_ADDRESS v29; // rsi
  _QWORD *v30; // rax
  __int64 v31; // r9
  unsigned __int64 v32; // r10
  EFI_PHYSICAL_ADDRESS v34; // r15
  unsigned __int64 v35; // rax
  unsigned __int64 v36; // r11
  EFI_PHYSICAL_ADDRESS v37; // r15
  char v38; // al
  __int64 v40; // rcx
  __int64 v41; // rdx
  unsigned __int64 v42; // rdx
  unsigned __int64 j; // r8
  __int64 bytes_per_line; // [rsp+20h] [rbp-458h]
  unsigned __int64 v45; // [rsp+30h] [rbp-448h]
  _BYTE v46[1080]; // [rsp+40h] [rbp-438h]
  unsigned __int64 Total; // [rsp+480h] [rbp+8h]

  v6 = 0i64;
  v8 = 0i64;
  Index = 0i64;
  v10 = 0i64;
  if ( *&Image->id != 1290 )
    return 0x8000000000000003ui64;
  if ( Image->encoding != 1 )
    return 0x8000000000000003ui64;
  if ( Image->bits_per_px != 8 )
    return 0x8000000000000003ui64;
    
  // Root cause for all vulnerabilities is here:
  // Image->planes and Image->bytes_per_line are not validated
  // => Total is controllable by the attacker
  // It will lead to OOB Reads further

  // BRLY-LOGOFAIL-2023-011: Improper input validation leads to OOB Read vulnerabilities
    
  *a6 = Image->x_max - Image->x_min + 1;
  v11 = Image->y_max - Image->y_min + 1;
  *a5 = v11;
  bytes_per_line = Image->bytes_per_line;
  v12 = Image + ImageSize - 767;
  Total = bytes_per_line * Image->planes;
  for ( i = 0i64; i < 0x100; ++i )
  {
    v46[4 * i + 2] = *(v12 - 1);
    v14 = *v12;
    v12 += 3;
    v46[4 * i + 1] = v14;
    v46[4 * i] = *(v12 - 2);
    v46[4 * i + 3] = 0;
  }
  v15 = 4 * *a6 * v11;
  v45 = v15;
  if ( v15 >= 0x100000000i64 )
    return 0x8000000000000003ui64;
  if ( sub_964(i, v12, a3, a4) )
    v17 = sub_9B4(v16, (v15 >> 12) + ((v15 & 0xFFF) != 0));
  else
    v17 = sub_9EC(v16, v15);
  v22 = v17;
  if ( v17 )
  {
    if ( (Image->planes - 3) > 1u || Image->bits_per_px != 8 )
    {
      v40 = *a6;
      if ( *a5 * *a6 )
      {
        do
        {
          // Vulnerability:
          // if v10 == v40, the Index will be incremented by a controllable
          // number of times since attacker is controlling
          // Total = Image->bytes_per_line * Image->planes;
          // and fields Image->bytes_per_line and Image->planes are unvalidated
          // So, we have OOB Read here: Image->Buffer[Index]
          if ( v10 == v40 )
          {
            if ( v10 < Total )
            {
              v40 = *a6;
              Index += Total - v10;
            }
            v10 = 0i64;
          }
          v41 = Image->Buffer[Index];
          if ( (Image->Buffer[Index] & 0xC0) == 0xC0 )
          {
            v42 = v41 & 0x3F;
            ++Index;
            for ( j = 0i64; j < v42; ++j )
            {
              ++v10;
              *(v17 + 4 * v8++) = *&v46[4 * Image->Buffer[Index]];
              v40 = *a6;
              if ( v10 == *a6 )
                break;
            }
          }
          else
          {
            *(v17 + 4 * v8++) = *&v46[4 * v41];
            v40 = *a6;
            ++v10;
          }
          ++Index;
        }
        while ( v8 < *a5 * v40 );
      }
      *a3 = v17;
      *a4 = v15;
      return 0i64;
    }
    v23 = Total + 50;
    if ( sub_964(v19, v18, v20, v21) )
      v25 = sub_9B4(v24, (v23 >> 12) + ((v23 & 0xFFF) != 0));
    else
      v25 = sub_9EC(v24, v23);
    v29 = v25;
    if ( v25 )
      v29 = sub_310(v25, v23);
    if ( v29 )
    {
      v30 = a5;
      v31 = 0i64;
      if ( *a5 )
      {
        v32 = Total;
        while ( 1 )
        {
          v27 = 0i64;
          if ( v32 )
          {
            do
            {
              // Vulnerability:
              // The Index will be incremented by a controllable
              // number of times since attacker is controlling
              // Total = Image->bytes_per_line * Image->planes;
              // and fields Image->bytes_per_line and Image->planes are unvalidated
              // So, we have OOB Read here: Image->Buffer[Index]
              v28 = Image->Buffer[Index];
              v26 = 1i64;
              if ( (Image->Buffer[Index] & 0xC0) == 0xC0 )
              {
                LOBYTE(v28) = Image->Buffer[Index + 1];
                v26 = Image->Buffer[Index++] & 0x3F;
              }
              while ( v27 < v32 )
              {
                if ( !v26-- )
                  break;
                *(v27 + v29) = v28;
                ++v27;
              }
              ++Index;
            }
            while ( v27 < v32 );
            v30 = a5;
          }
          if ( Image->planes == 3 )
          {
            v28 = 0i64;
            if ( *a6 )
            {
              v34 = v29 + 2 * bytes_per_line;
              do
              {
                v26 = v34 + v28;
                *(v22 + 4 * (v28 + v31 * *a6) + 2) = *(v34 + v28 - 2 * bytes_per_line);
                *(v22 + 4 * (v28 + v31 * *a6) + 1) = *(v34 + v28 - bytes_per_line);
                v27 = v28 + v31 * *a6;
                *(v22 + 4 * v27) = *(v34 + v28);
                v35 = v28 + v31 * *a6;
                ++v28;
                *(v22 + 4 * v35 + 3) = -1;
              }
              while ( v28 < *a6 );
LABEL_37:
              v30 = a5;
              v32 = Total;
            }
          }
          else
          {
            v36 = 0i64;
            if ( *a6 )
            {
              v37 = v29 + 2 * bytes_per_line;
              v28 = -bytes_per_line;
              do
              {
                v26 = v37 + v36;
                *(v22 + 4 * (v36 + v31 * *a6) + 2) = *(v37 + v36 - 2 * bytes_per_line);
                *(v22 + 4 * (v36 + v31 * *a6) + 1) = *(v37 + v36 - bytes_per_line);
                *(v22 + 4 * (v36 + v31 * *a6)) = *(v37 + v36);
                v38 = *(v37 + v36 + bytes_per_line);
                v27 = v36 + v31 * *a6;
                ++v36;
                *(v22 + 4 * v27 + 3) = v38;
              }
              while ( v36 < *a6 );
              goto LABEL_37;
            }
          }
          if ( ++v31 >= *v30 )
          {
            v23 = Total + 50;
            v15 = v45;
            break;
          }
        }
      }
      *a3 = v22;
      *a4 = v15;
      if ( sub_964(v27, v26, v28, v31) )
      {
        LOBYTE(v6) = (v23 & 0xFFF) != 0;
        gBS->FreePages(v29, (v23 >> 12) + v6);
      }
      else
      {
        (gBS->FreePool)(v29);
      }
      return 0i64;
    }
  }
  return 0x8000000000000009ui64;
}
