__int64 __fastcall DecodeLZW(
        char *Image,
        unsigned __int64 a2,
        char a3,
        __int64 a4,
        unsigned __int16 a5,
        unsigned __int16 a6,
        __int64 a7)
{
  HeapStruct *v7; // r13
  char Value; // cl
  char *v10; // r11
  unsigned __int16 Bound; // bx
  unsigned __int8 v12; // r9
  __int16 v13; // di
  unsigned __int16 v14; // r12
  unsigned __int8 v15; // si
  unsigned int v16; // r10d
  unsigned __int16 v17; // r15
  unsigned __int16 v18; // r8
  unsigned __int16 Index; // cx
  HeapStruct *HeapArrayEntry; // rax
  unsigned __int16 v21; // bp
  _BYTE *v22; // r14
  unsigned __int64 v23; // rax
  char v24; // cl
  unsigned __int16 v25; // r11
  __int16 v26; // r9
  unsigned __int16 v27; // ax
  unsigned __int16 v28; // ax
  __int64 v29; // rdx
  __int64 v30; // rax
  __int64 v31; // rdx
  char v33; // [rsp+0h] [rbp-68h]
  unsigned __int8 v34; // [rsp+1h] [rbp-67h]
  unsigned __int16 v35; // [rsp+2h] [rbp-66h]
  __int16 v36; // [rsp+4h] [rbp-64h]
  __int16 v37; // [rsp+6h] [rbp-62h]
  unsigned __int16 v38; // [rsp+8h] [rbp-60h]
  unsigned __int16 v39; // [rsp+10h] [rbp-58h]
  char *v40; // [rsp+70h] [rbp+8h]

  v7 = HeapArray;
  Value = *Image;
  v10 = Image + 1;
  
  // Validate Value to prevent excessive Bound calculation
  if (Value > 11)  // 11 is chosen to ensure Bound (2^11 = 2048) fits within HeapArray (4096 elements)
    return 0x8000000000000002ui64;  // Return error code for invalid parameter
  
  Bound = 1 << Value;
  v40 = v10;
  v39 = Bound;
  v12 = Value + 1;
  v36 = -1;
  v37 = (1 << Value) + 1;
  v13 = -1;
  v34 = Value + 1;
  v38 = (1 << Value) + 2;
  v14 = v38;
  v35 = v38;
  v15 = Value + 1;
  v33 = Value + 1;
  v16 = 0;
  v17 = 0;
  v18 = 0;
  Index = 0;
  
  if (Bound)
  {
    HeapArrayEntry = HeapArray;
    
    // Validate Bound against HeapArray size
    if (Bound > 4096)  // HeapArray has 4096 elements
      return 0x8000000000000002ui64;  // Return error code for invalid parameter
    
    // Safe loop with proper bounds check
    do
    {
      if (Index >= 4096)  // Prevent out-of-bounds write
        return 0x8000000000000002ui64;
        
      HeapArrayEntry->field_2 = Index++;
      HeapArrayEntry->field_0 = -1;
      HeapArrayEntry = (HeapArrayEntry + 4);  // Increment by 4 HeapStruct entries (not bytes)
    }
    while (Index < Bound);
    
    v7 = HeapArray;
  }
  
  // ... [remaining function code unchanged] ...
}
