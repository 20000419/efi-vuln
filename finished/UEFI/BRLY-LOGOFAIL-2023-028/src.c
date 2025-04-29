INT32 __fastcall DecodeLzwBytes(BUFFER_INDICATOR *Bi, BOOLEAN flag, INT32 CodeSize)
{
  int i; // eax
  int *ptr; // rcx MAPDST
  INT32 result; // eax
  int Code; // er8
  int v9; // er9
  __int64 v10; // r10
  int v11; // er14
  int v12; // er11
  int *v13; // rdx
  int v14; // ecx
  _DWORD *v15; // rdx
  int v16; // eax
  INT32 v17; // eax
  int v18; // eax
  int *v19; // rcx
  _DWORD *v20; // rax
  UINT8 Buffer[272]; // [rsp+20h] [rbp-118h]

  if ( flag )
  {
    set_code_size = CodeSize;
    code_size = CodeSize + 1;
    curbit = 0;
    clear_code = 1 << CodeSize;                 // Root Cause: OOB index.
    lastbit = 0;                                // Firstly, there is INT32 table [2][(1<< MAX_LZW_BITS)], where MAX_LZW_BITS is 12.
    done = 0;                                   // Hence, table [2][4096] is allocated.
    fresh = 1;                                  // CodeSize isn't validated to be between 0 to MAX_LZW_BITS range.
    end_code = (1 << CodeSize) + 1;             // In this case CodeSize determines an index value, which is used to navigate across the table.
    max_code_size = 2 * (1 << CodeSize);        // Secondly, CodeSize influences on size of data returned by GetCode().
    max_code = (1 << CodeSize) + 2;             // In this case the data is used to navigate across the table.
    i = 0;
    if ( 1 << CodeSize > 0 )
    {
      ptr = &table_second_raw;
      do
      {
        *ptr = i++;                             // CRASH location: OOB write
        *(ptr - 4096) = 0;
        ++ptr;
      }
      while ( i < 1 << CodeSize );
    }
    if ( i < 0x1000i64 )
    {
      ptr = (int *)((char *)&table_first_raw + 4 * i);
      do
      {
        table_second_raw = 0;
        *ptr = 0;
        ++ptr;
      }
      while ( (__int64)ptr < (__int64)&table_second_raw );
    }
    result = 0;
    sp_ = (__int64)stack;
    return result;
  }
  if ( fresh )
  {
    fresh = 0;
    do
    {
      result = GetCode(Bi, code_size, 0);
      oldcode = result;
      firstcode = result;
    }
    while ( result == clear_code );
    return result;
  }
  if ( sp_ > (unsigned __int64)stack )
  {
    sp_ -= 4i64;
    return *(_DWORD *)sp_;
  }
  Code = GetCode(Bi, code_size, 0);
  if ( Code < 0 )
    return Code;
  while ( 2 )
  {
    v9 = clear_code;
    if ( Code == clear_code )
    {
      v18 = 0;
      if ( clear_code > 0 )
      {
        v19 = &table_second_raw;
        do
        {
          *v19 = v18++;
          *(v19 - 4096) = 0;
          ++v19;
        }
        while ( v18 < v9 );
      }
      if ( v18 < 4096i64 )
      {
        v20 = (_DWORD *)((char *)&table_first_raw + 4 * v18);
        do
        {
          v20[4096] = 0;
          *v20 = 0;
          ++v20;
        }
        while ( (__int64)v20 < (__int64)&table_second_raw );
      }
      max_code_size = 2 * v9;
      code_size = set_code_size + 1;
      max_code = v9 + 2;
      sp_ = (__int64)stack;
      result = GetCode(Bi, set_code_size + 1, 0);
      oldcode = result;
      firstcode = result;
    }
    else
    {
      if ( Code != end_code )
      {
        v10 = max_code;
        v11 = Code;
        v12 = oldcode;
        v13 = (int *)sp_;
        if ( Code >= max_code )
        {
          Code = oldcode;
          *(_DWORD *)sp_ = firstcode;
          ++v13;
        }
        while ( Code >= v9 )
        {
          *v13 = *((_DWORD *)&table_first_raw + Code + 0x1000);
          ++v13;
          sp_ = (__int64)v13;
          if ( Code == *((_DWORD *)&table_first_raw + Code) )
            return -3;
          Code = *((_DWORD *)&table_first_raw + Code);
        }
        v14 = *((_DWORD *)&table_first_raw + Code + 0x1000);
        *v13 = v14;
        v15 = v13 + 1;
        firstcode = v14;
        sp_ = (__int64)v15;
        if ( (int)v10 >= 0x1000
          || (v16 = max_code_size,
              *((_DWORD *)&table_first_raw + v10) = v12,
              *((_DWORD *)&table_first_raw + v10 + 0x1000) = v14,
              max_code = v10 + 1,
              (int)v10 + 1 < v16)
          || v16 >= 0x1000 )
        {
          v17 = code_size;
        }
        else
        {
          max_code_size = 2 * v16;
          v17 = ++code_size;
        }
        oldcode = v11;
        if ( v15 > stack )
        {
          sp_ = (__int64)(v15 - 1);
          return *(v15 - 1);
        }
        Code = GetCode(Bi, v17, 0);
        if ( Code >= 0 )
          continue;
        return Code;
      }
      if ( !gZeroDataBlock )
      {
        while ( GetDataBlock(Bi, Buffer) > 0 )
          ;
      }
      result = -2;
    }
    break;
  }
  return result;
}
