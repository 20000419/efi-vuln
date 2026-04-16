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
  unsigned __int64 bytes_per_line; // [rsp+20h] [rbp-458h]
  unsigned __int64 v45; // [rsp+30h] [rbp-448h]
  _BYTE v46[1080]; // [rsp+40h] [rbp-438h]
  unsigned __int64 Total; // [rsp+480h] [rbp+8h]

  v6 = 0i64;
  v8 = 0i64;
  Index = 0i64;
  v10 = 0i64;

  // Validate PCX header magic number
  if (*&Image->id != 1290)
    return 0x8000000000000003ui64;
  
  // Validate encoding and bit depth
  if (Image->encoding != 1 || Image->bits_per_px != 8)
    return 0x8000000000000003ui64;

  // New validation for planes and bytes_per_line
  if (Image->planes == 0 || Image->bytes_per_line == 0)
    return 0x8000000000000003ui64;
  if (Image->planes > 4) // Maximum valid planes for PCX (e.g., 1 or 3)
    return 0x8000000000000003ui64;
  if (Image->bytes_per_line > ImageSize / Image->planes) // Prevent overflow and OOB
    return 0x8000000000000003ui64;
  Total = Image->bytes_per_line * Image->planes;

  *a6 = Image->x_max - Image->x_min + 1;
  v11 = Image->y_max - Image->y_min + 1;
  *a5 = v11;
  bytes_per_line = Image->bytes_per_line;
  v12 = Image + ImageSize - 767;

  // Validate color palette access
  if (v12 < Image + sizeof(PCXHeader))
    return 0x8000000000000003ui64;

  for (i = 0i64; i < 0x100; ++i) {
    if (v12 - 2 < Image || v12 >= Image + ImageSize) // Prevent OOB in palette read
      return 0x8000000000000003ui64;
    v46[4 * i + 2] = *(v12 - 1);
    v14 = *v12;
    v12 += 3;
    v46[4 * i + 1] = v14;
    v46[4 * i] = *(v12 - 2);
    v46[4 * i + 3] = 0;
  }

  v15 = 4 * *a6 * v11;
  v45 = v15;
  if (v15 >= 0x100000000i64)
    return 0x8000000000000003ui64;

  // ... (existing memory allocation code) ...

  if (v17) {
    if ((Image->planes - 3) > 1u || Image->bits_per_px != 8) {
      v40 = *a6;
      if (*a5 * *a6) {
        do {
          // Boundary check for Index before buffer access
          if (Index >= ImageSize)
            return 0x8000000000000003ui64;
          
          if (v10 == v40) {
            if (v10 < Total) {
              // Prevent Index from exceeding buffer size
              if (Index + Total - v10 > ImageSize)
                return 0x8000000000000003ui64;
              Index += Total - v10;
            }
            v10 = 0i64;
          }

          // Boundary check before accessing Image->Buffer
          if (Index >= ImageSize)
            return 0x8000000000000003ui64;
          v41 = Image->Buffer[Index];

          if ((v41 & 0xC0) == 0xC0) {
            if (Index + 1 >= ImageSize) // Check for next byte availability
              return 0x8000000000000003ui64;
            v42 = v41 & 0x3F;
            ++Index;
            for (j = 0i64; j < v42; ++j) {
              if (Index >= ImageSize) // Prevent OOB in repeated access
                return 0x8000000000000003ui64;
              ++v10;
              *(v17 + 4 * v8++) = *&v46[4 * Image->Buffer[Index]];
              v40 = *a6;
              if (v10 == *a6)
                break;
            }
          } else {
            *(v17 + 4 * v8++) = *&v46[4 * v41];
            v40 = *a6;
            ++v10;
          }
          ++Index;
        } while (v8 < *a5 * v40);
      }
      // ... (remaining code with similar boundary checks added for other OOB locations) ...
    }
  }
  return 0x8000000000000009ui64;
}
