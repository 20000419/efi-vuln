char sub_B68()
{
  unsigned __int8 v0; // bl
  char result; // al
  __int64 v2; // r9
  char *v3; // rdx
  char *v4; // r10
  __int64 v5; // r11
  unsigned __int8 i; // r8
  char v7; // r14
  __int64 v8; // rbp
  _WORD *v9; // rsi
  unsigned __int8 v10; // di
  __int64 v11; // rcx

  v0 = 0;
  // SOSPtr[2] -- Invalid read
  // due to unchecked SOSPtr, which may remain uninitialised in InitJfifData() function

  // BRLY-LOGOFAIL-2023-008:  Usage of uninitialised SOSPtr pointer leads to null pointer dereference
  // (in case when JPEG_SOS is not covered during the parsing)
  
  Decoder[0] = &SOSPtr[256 * SOSPtr[2] + 2 + SOSPtr[3]];
  byte_2108 = *Decoder[0]++;
  result = byte_2220;
  byte_2109 = 7;
  if ( byte_2220 )
  {
    v2 = 0i64;
    v3 = &unk_2229;
    v4 = (SOSPtr + 6);
    v5 = byte_2220;
    do
    {
      for ( i = 0; i < *(v3 - 2); ++i )
      {
        if ( *(v3 - 3) )
        {
          v7 = *v3;
          v8 = *(v3 - 3);
          v9 = &Decoder[1] + v2 + 2;
          v10 = i;
          do
          {
            result = *v4;
            v11 = v0++;
            v11 *= 2i64;
            BYTE2(Decoder[v11 + 3]) = v10;
            v10 += 16;
            LOBYTE(Decoder[v11 + 3]) = result;
            BYTE1(Decoder[v11 + 3]) = v7;
            *v9 = 0;
            Decoder[v11 + 4] = v9;
            --v8;
          }
          while ( v8 );
        }
      }
      ++v2;
      v3 += 4;
      v4 += 2;
      --v5;
    }
    while ( v5 );
  }
  byte_210A = v0;
  return result;
}

__int64 __fastcall InitJfif(UINT8 *Image, UINTN ImageSize)
{
...
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
 ...
