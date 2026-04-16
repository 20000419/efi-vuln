__int64 __fastcall CreateHuffmanTable(WORD *a1, BYTE *a2)
{
  int v2; // ebx
  WORD v3; // r10
  __int64 index; // r8
  BYTE *v5; // rdx
  unsigned __int8 v6; // r11
  BYTE *v7; // rdi
  int v8; // r9d
  __int64 index_plus_1; // r8
  WORD v10; // ax
  __int64 result; // rax
  const __int64 MAX_HUFFMAN_ENTRIES = 1024; // Define maximum entries based on static buffer size

  v2 = 0;
  v3 = 0;
  index = 0i64;
  v5 = a2 + 1;
  v6 = 1;
  v7 = v5;
  
  do
  {
    v8 = *v5;
    if ( *v5 )
    {
      v2 += v8 + 2 * v8;
      
      // Validate total entries before processing
      if (index + 3 * v8 > MAX_HUFFMAN_ENTRIES - 1)
        return -1; // Error: Exceeds maximum entries
      
      do
      {
        // Check bounds before each write
        if (index >= MAX_HUFFMAN_ENTRIES)
          return -1; // Error: OOB write
        
        a1[index] = v6;
        
        index_plus_1 = index + 1;
        if (index_plus_1 >= MAX_HUFFMAN_ENTRIES)
          return -1; // Error: OOB write
        
        a1[index_plus_1++] = v3;
        
        v10 = v7[16];
        ++v3;
        ++v7;
        
        if (index_plus_1 >= MAX_HUFFMAN_ENTRIES)
          return -1; // Error: OOB write
        
        a1[index_plus_1] = v10;
        index = index_plus_1 + 1;
      }
      while ( v8 > 0 );
    }
    v3 *= 2;
    ++v5;
    ++v6;
  }
  while ( v6 <= 0x10u );
  
  // Final check before writing terminator
  if (v2 >= MAX_HUFFMAN_ENTRIES)
    return -1; // Error: OOB write
  
  result = v2;
  a1[v2] = 17;
  return result;
}
