__int64 __fastcall ParseImage(
        _BYTE *LogoData,
        __int64 LogoSize_1,
        int a3,
        __int64 a4,
        __int64 a5,
        char a6,
        unsigned __int64 *Vertical,
        unsigned __int64 *Horizontal)
{
  unsigned __int64 *Width; // rsi
  unsigned __int64 *Height; // rbx
  __int64 result; // rax
  __int64 LogoSize; // rdx
  unsigned __int64 v15; // rdi
  unsigned __int64 DecodedSize[2]; // [rsp+40h] [rbp-10h] BYREF
  void *DecodedLogo; // [rsp+78h] [rbp+28h] BYREF

  Width = Vertical;
  Height = Horizontal;
  DecodedSize[0] = 0i64;
  DecodedLogo = 0i64;
  *Vertical = 0i64;
  *Height = 0i64;
  sub_75F8();
  if ( !gEfiGraphicsOutputProtocol )
    return 0x8000000000000003ui64;
  result = GetResolution(&Horizontal, &Vertical);
  if ( result >= 0 )
  {
    result = *LogoData == 'B' && LogoData[1] == 'M'
           ? ParseBMP(LogoData, LogoSize, &DecodedLogo, DecodedSize, Height, Width)
           : ParseOthers(LogoData, LogoSize, &DecodedLogo, DecodedSize, Height, Width);
    v15 = *Width;
    if ( result >= 0 )
    {
      if ( a6 && (v15 > Horizontal || *Height > Vertical) )
      {
        sub_BD3C(Width, Height);
        if ( gEfiGraphicsOutputProtocol )
          GetResolution(&Horizontal, &Vertical);
      }
      sub_C014(DecodedLogo, a3, *Width, *Height, a4, a5, v15);
      MemFreePointer(&DecodedLogo);
      return 0i64;
    }
  }
  return result;
}
