#define MAX_LZW_BITS 12  // Table size is 2[4096], so max code size is 12

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

  // Validate CodeSize before use (critical fix)
  if (flag && (CodeSize < 0 || CodeSize > MAX_LZW_BITS)) {
    return -1; // Invalid CodeSize, prevent OOB access
  }

  if (flag) {
    set_code_size = CodeSize;
    code_size = CodeSize + 1;
    curbit = 0;
    clear_code = 1 << CodeSize;                 // Safe since CodeSize <= MAX_LZW_BITS
    lastbit = 0;
    done = 0;
    fresh = 1;
    end_code = (1 << CodeSize) + 1;             // Valid range
    max_code_size = 2 * (1 << CodeSize);        // Safe calculation
    max_code = (1 << CodeSize) + 2;             // Valid index boundary

    // Initialize table within valid bounds
    i = 0;
    int max_entry = 1 << CodeSize;
    if (max_entry > 0) {
      ptr = &table_second_raw;
      do {
        *ptr = i++;
        *(ptr - 4096) = 0;
        ++ptr;
      } while (i < max_entry);
    }

    // Clear remaining table entries if needed (defensive programming)
    if (i < 4096) {
      ptr = (int *)((char *)&table_first_raw + 4 * i);
      do {
        table_second_raw = 0;
        *ptr = 0;
        ++ptr;
      } while ((__int64)ptr < (__int64)&table_second_raw);
    }

    result = 0;
    sp_ = (__int64)stack;
    return result;
  }

  // ... (remaining logic unchanged, with existing bounds checks preserved) ...

  return result;
}
