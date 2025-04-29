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
  if ( Bound )
  {
    HeapArrayEntry = HeapArray;
    // BRLY-LOGOFAIL-2023-004
    do
    {
      HeapArrayEntry->field_2 = Index++;
      HeapArrayEntry->field_0 = -1;
      HeapArrayEntry = (HeapArrayEntry + 4);
    }
    while ( Index < Bound );
    v7 = HeapArray;
  }
  if ( v12 >> 3 <= a2 )
  {
    v21 = a6;
    v22 = qword_1D50;
    do
    {
      v23 = v16 >> 3;
      v24 = v16 & 7;
      v16 += v15;
      v25 = ((1 << v15) - 1) & (*&v10[v23] >> v24);
      if ( v25 == v37 )
        return v16;
      if ( v25 == Bound )
      {
        v14 = v38;
        v15 = v12;
        v35 = v38;
        v13 = Bound;
        v33 = v12;
        v36 = Bound;
        goto LABEL_40;
      }
      if ( v18 == v21 )
        return v16;
      v26 = -1;
      if ( v25 >= v14 )
      {
        if ( v13 == Bound )
          goto LABEL_44;
        v26 = 0;
        v28 = v13;
        if ( v13 != -1 )
        {
          do
          {
            v22[++v26] = *(&v7->field_2 + 4 * v28);
            v28 = *(&v7->field_0 + 2 * v28);
          }
          while ( v28 != 0xFFFF );
          v15 = v33;
          v21 = a6;
        }
        *v22 = v22[v26];
      }
      else
      {
        v27 = v25;
        if ( v25 != 0xFFFF )
        {
          do
          {
            v22[++v26] = *(&v7->field_2 + 4 * v27);
            v27 = *(&v7->field_0 + 2 * v27);
          }
          while ( v27 != 0xFFFF );
          v21 = a6;
        }
        if ( v13 == Bound )
          goto LABEL_23;
      }
      v29 = v14++;
      v35 = v14;
      *(&v7->field_0 + 2 * v29) = v13;
      *(&v7->field_2 + 4 * v29) = v22[v26];
LABEL_23:
      if ( v26 >= 0 )
      {
        do
        {
          v30 = v26--;
          v31 = v22[v30];
          LODWORD(v30) = v17++;
          *(a7 + 4i64 * (v30 + a5 * v18)) = *(a4 + 4 * v31);
          if ( v17 == a5 )
          {
            if ( a3 )
            {
              if ( (v18 & 7) != 0 )
              {
                if ( (v18 & 3) != 0 )
                {
                  if ( (v18 & 1) != 0 )
                  {
                    v18 += 2;
                  }
                  else
                  {
                    v18 += 4;
                    if ( v18 >= v21 )
                      v18 = 1;
                  }
                }
                else
                {
                  v18 += 8;
                  if ( v18 >= v21 )
                    v18 = 2;
                }
              }
              else
              {
                v18 += 8;
                if ( v18 >= v21 )
                  v18 = 4;
              }
            }
            else
            {
              ++v18;
            }
            v17 = 0;
            if ( v18 == v21 )
              break;
          }
        }
        while ( v26 >= 0 );
        Bound = v39;
        v13 = v36;
        v15 = v33;
        v14 = v35;
        v7 = HeapArray;
      }
LABEL_40:
      if ( v14 < 1 << v15 )
        goto LABEL_43;
      if ( v15 < 0xCu )
      {
        v33 = ++v15;
LABEL_43:
        v13 = v25;
        v36 = v25;
      }
LABEL_44:
      v12 = v34;
      v10 = v40;
    }
    while ( (v16 + v15) >> 3 <= a2 );
  }
  return v16;
}
