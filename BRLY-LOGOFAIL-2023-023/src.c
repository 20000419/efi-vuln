__int64 __fastcall EmitPixel(unsigned __int8 PixelValue)
{
  int v1; // r9d
  __int64 v2; // rdx
  __int64 v3; // rcx
  _BYTE *v4; // r8
  unsigned int v5; // r9d
  unsigned int v6; // ecx
  __int64 result; // rax
  unsigned int v8; // r9d

  v1 = Mult;
  if ( PixelValue != dword_7FC20 )
  {
    v2 = PixelValue;
    v3 = GIFColorMap;
    // BRLY-LOGOFAIL-2023-023 
    v4 = (Buffer + (4 * Mult));
    *v4 = *(GIFColorMap + 4 * v2);
    v4[1] = *(v3 + 4 * v2 + 1);
    v4[2] = *(v3 + 4 * v2 + 2);
    v4[3] = 0;
  }
  v5 = v1 + 1;
  Mult = v5;
  if ( ++dword_8CB80 > dword_94FF8 )
  {
    dword_8CB80 = dword_95480;
    if ( dword_94FE0 )
    {
      v6 = *(&dword_86C48 + &_ImageBase[2 * dword_95000]) + dword_8CB84;
      dword_8CB84 = v6;
      if ( v6 <= dword_94FEC )
      {
LABEL_9:
        v5 = dword_95480 + dword_94BB0 + dword_7FC24 * (v6 + dword_95470);
        Mult = v5;
        goto LABEL_10;
      }
      v6 = dword_94FE4 + *(&dword_86C30 + &_ImageBase[2 * ++dword_95000]);
    }
    else
    {
      v6 = dword_8CB84 + 1;
    }
    dword_8CB84 = v6;
    goto LABEL_9;
  }
LABEL_10:
  result = dword_94BC8;
  v8 = HIWORD(v5);
  if ( dword_94BC8 != v8 )
    result = v8;
  dword_94BC8 = result;
  return result;
}
