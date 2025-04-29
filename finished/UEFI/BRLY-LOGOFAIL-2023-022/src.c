__int64 __fastcall GetDimensions(_BYTE *Image)
{
  char v2; // di
  unsigned __int8 HuffmanTablesCounter; // r10
  unsigned __int8 v4; // bl
  unsigned __int8 MarkerType; // cl
  __int64 v6; // rax
  __int64 v8; // rax
  char v9; // al
  _BYTE *v10; // rdx
  _QWORD *v11; // r8
  unsigned __int8 v12; // r9
  __int64 v13; // rdx
  __int64 v14; // r11
  unsigned __int16 Len; // [rsp+30h] [rbp+8h]

  v2 = 0;
  HuffmanTablesCounter = 0;
  v4 = 0;
  if ( *Image != 0xFF || Image[1] != 0xD8 )
    return 0i64;
  while ( 1 )
  {
    MarkerType = Image[1];
    if ( MarkerType != 0xD8 )
      break;
    Image += 2;
LABEL_27:
    if ( *Image != 0xFF )
      return 0i64;
  }
  if ( MarkerType == 0xD9 )
    goto LABEL_30;
  if ( !MarkerType )
    return 0i64;
  if ( (MarkerType & 0xF0) == 0xE0 )
  {
LABEL_26:
    v9 = Image[3];
    v10 = Image + 2;
    LOBYTE(Len) = v9;
    HIBYTE(Len) = *v10;
    Image = &v10[Len];
    goto LABEL_27;
  }
  if ( MarkerType == 0xC0 )
  {
    v2 |= 2u;
    qword_95FC0 = (Image + 2);
    goto LABEL_26;
  }
  if ( MarkerType == 0xC4 )                     // Huffman Table Marker
  {
    v6 = HuffmanTablesCounter++;
    HuffmanTables[v6] = (Image + 4);
    goto LABEL_26;
  }
  if ( (MarkerType & 0xF0) == 0xC0 )
  {
    if ( MarkerType > 0xC0u && MarkerType < 0xD0u )
      return 0i64;
    goto LABEL_26;
  }
  if ( MarkerType != 0xDA )
  {
    if ( MarkerType == 0xDB )
    {
      v8 = v4++;
      qword_95EA0[v8] = (Image + 4);
    }
    else if ( MarkerType == 0xDD )
    {
      LOBYTE(word_95490) = Image[5];
      HIBYTE(word_95490) = Image[4];
    }
    else if ( (MarkerType & 0xF8) != 0xD0
           && (MarkerType == 0xDC || MarkerType == 0xDE || MarkerType == 0xDF || (MarkerType + 16) > 0xEu) )
    {
      return 0i64;
    }
    goto LABEL_26;
  }
  qword_95F10 = (Image + 14);
LABEL_30:
  if ( v4 == 1 )
  {
    v4 = 2;
    qword_95EA8 = qword_95EA0[0] + 65;
  }
  if ( HuffmanTablesCounter == 1 )
  {
    v11 = &unk_96568;
    do
    {
      v12 = 0;
      v13 = 0i64;
      v14 = HuffmanTables[HuffmanTablesCounter - 1];
      do
        v12 += *(v14 + v13++ + 1);
      while ( v13 < 16 );
      ++HuffmanTablesCounter;
      *v11++ = v12 + v14 + 17;
    }
    while ( HuffmanTablesCounter < 4u );
  }
  if ( HuffmanTablesCounter != 4 || v4 != 2 || (v2 & 2) == 0 )
    return 0i64;
  sub_5D26C(2u, 4u);
  return 1i64;
}
