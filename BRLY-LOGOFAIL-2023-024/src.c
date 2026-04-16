__int64 sub_5B970()
{
  int v0; // ecx
  int v1; // r14d
  int v2; // ebx
  int v3; // r15d
  int v4; // r12d
  int v5; // edi
  int v6; // ebp
  __int64 v7; // rcx
  int v8; // r10d
  int v9; // esi
  __int64 v10; // rdi
  char v11; // r13
  void *v12; // rdx
  int v13; // eax
  int v14; // r11d
  unsigned __int8 v15; // cl
  unsigned int v17; // [rsp+60h] [rbp+8h]
  int v18; // [rsp+68h] [rbp+10h]

  if ( dword_94FF4 )
  {
    --dword_94FF4;
    v0 = *qword_8CB68++;
    if ( (v0 - 2) > 7 )
      return 4294967293i64;
    dword_8CB88 = 0;
    dword_95018 = 0;
    v1 = v0 + 1;
    v17 = v0 + 1;
    dword_94BA0 = v0 + 1;
    v2 = 1 << (v0 + 1);
    v3 = 1 << v0;
    v18 = 1 << v0;
    dword_8CB78 = 1 << v0;
    v4 = (1 << v0) + 2;
    dword_95024 = v2;
    v5 = (1 << v0) + 1;
    dword_94BA8 = v4;
    dword_8CB90 = v5;
    v6 = v4;
    dword_95014 = v4;
    dword_94BA4 = 512;
    dword_95020 = (sub_5B7E8)();
    v8 = dword_95020;
    if ( dword_95020 == v5 )
      return 0i64;
    v9 = dword_9501C;
    v10 = 0i64;
    v11 = dword_94BB4;
    while ( 1 )
    {
      v12 = &GifCodes;
      if ( dword_8CB8C )
        break;
      if ( v8 == v3 )
      {
        v3 = v18;
        v1 = v17;
        v2 = 1 << v17;
        dword_94BA0 = v17;
        v4 = v18 + 2;
        dword_8CB78 = v18;
        dword_94BA8 = v18 + 2;
        dword_8CB90 = v18 + 1;
        v6 = v18 + 2;
        dword_95014 = v18 + 2;
        dword_95024 = 1 << v17;
        v13 = sub_5B7E8(v17, &GifCodes);
        v9 = v13;
        dword_95020 = v13;
        if ( dword_8CB8C )
          return 4294967292i64;
        dword_9501C = v13;
        dword_94FF0 = v13;
        v11 = v13;
        dword_94BB4 = v13;
        EmitPixel(v13);
      }
      else
      {
        dword_8CB74 = v8;
        v14 = v8;
        if ( v8 >= v6 )
        {
          v8 = v9;
          *(&GifCodes + 8 * v10 + 5) = v11;
          goto LABEL_12;
        }
        while ( v8 >= v4 )
        {
          v7 = v8;
          // BRLY-LOGOFAIL-2023-024
          *(&GifCodes + 8 * v10 + 5) = *(&GifCodes + 8 * v8 + 4);
          v8 = *(&GifCodes + 2 * v8);
LABEL_12:
          ++v10;
        }
        *(&GifCodes + 8 * v10 + 5) = v8;
        v11 = v8;
        ++v10;
        dword_94BB4 = v8;
        dword_94FF0 = v8;
        if ( v10 > 0 )
        {
          do
          {
            v15 = *(&GifCodes + 8 * v10-- - 3);
            EmitPixel(v15);
          }
          while ( v10 > 0 );
          v12 = &GifCodes;
        }
        if ( v6 <= 4095 )
        {
          *(&GifCodes + 8 * v6 + 4) = v8;
          *(&GifCodes + 2 * v6) = v9;
        }
        ++v6;
        dword_9501C = v14;
        dword_95014 = v6;
        v9 = v14;
        if ( v6 >= v2 && v1 < 12 )
        {
          ++v1;
          v2 *= 2;
          dword_94BA0 = v1;
          dword_95024 = v2;
        }
      }
      v8 = sub_5B7E8(v7, v12);
      dword_95020 = v8;
      if ( v8 == v3 + 1 )
        return 0i64;
    }
  }
  return 4294967292i64;
}
