__int64 __fastcall GetDimensions(_BYTE *Image, size_t ImageSize) // Added ImageSize parameter for buffer bounds
{
  char v2; // di
  unsigned __int8 v3; // r10
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
  _BYTE *ImageStart = Image; // Save initial buffer pointer

  v2 = 0;
  v3 = 0;
  v4 = 0;
  if (ImageSize < 2 || *Image != 0xFF || Image[1] != 0xD8) // Initial buffer size check
    return 0i64;

  while (1)
  {
    MarkerType = Image[1];
    if (MarkerType != 0xD8)
      break;
    Image += 2;
LABEL_27:
    if (Image >= ImageStart + ImageSize || *Image != 0xFF) // Check buffer bounds before reading marker
      return 0i64;
  }

  if (MarkerType == 0xD9)
    goto LABEL_30;
  if (!MarkerType)
    return 0i64;

  while (Image <= ImageStart + ImageSize - 2) // Ensure we have at least 2 bytes for marker/length
  {
    if ((MarkerType & 0xF0) == 0xE0)
    {
LABEL_26:
      if (Image + 4 > ImageStart + ImageSize) // Check for length field bounds
        return 0i64;
      
      v9 = Image[3];
      v10 = Image + 2;
      LOBYTE(Len) = v9;
      HIBYTE(Len) = *v10;

      // Validate length and ensure new position is within buffer bounds
      if (Len < 2 || Image + Len > ImageStart + ImageSize) // Minimum segment size (marker + length) is 2 bytes
        return 0i64;
      
      Image = Image + Len; // Safe pointer update with bounds check
      goto LABEL_27;
    }
    // ... (other marker type handling remains the same, add similar bounds checks where pointers are updated)
    // For example, in MarkerType == 0xC0, 0xC4, etc., ensure pointer updates don't exceed buffer
    
    // Common validation for all markers that update Image pointer
    if (Image + 2 > ImageStart + ImageSize) // Ensure we can read marker length
      return 0i64;
      
    v10 = Image + 2;
    LOBYTE(Len) = Image[3];
    HIBYTE(Len) = *v10;
    
    if (Len < 2 || Image + Len > ImageStart + ImageSize) // Standard length validation
      return 0i64;
      
    Image = Image + Len;
    goto LABEL_27;
  }

  // ... (remaining logic unchanged, ensure final operations don't access OOB memory)

  if (v3 != 4 || v4 != 2 || (v2 & 2) == 0)
    return 0i64;
  sub_5D26C(2u, 4u);
  return 1i64;
}
