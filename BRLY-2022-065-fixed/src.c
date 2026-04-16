void *__fastcall sub_105AC(void *a1)
{
  char v2; // di
  unsigned int v3; // esi
  void *result; // rax
  void *v5; // r12
  __int64 v6; // rdx
  __int64 v7; // rdx
  __int64 v8; // rdx
  unsigned int v9; // ebx
  char *v10; // rsi
  __int64 v11; // r14
  char v12; // al
  char *v13; // rbx
  const __int16 *v14; // rax
  __int64 v15; // rbx
  UINTN v16; // rbx
  bool v17; // zf
  __int64 v18; // rdi
  const __int16 *v19; // rax
  __int16 *v20; // rdx
  const __int16 *v21; // rax
  UINTN v22; // rdi
  __int64 v23; // rdi
  const __int16 *v24; // rax
  __int16 *v25; // rdx
  const __int16 *v26; // rax
  UINTN v27; // rdi
  __int64 v28; // rdi
  const __int16 *v29; // rax
  __int16 *v30; // rdx
  const __int16 *v31; // rax
  UINTN v32; // rdi
  __int64 v33; // r8
  __int16 *v34; // rax
  __int16 *v35; // rdx
  __int16 *v36; // rax
  char v37; // al
  char *v38; // rbx
  char v39; // cl
  const __int16 *v40; // rax
  __int64 v41; // rbx
  UINTN v42; // rbx
  __int64 v43; // rdi
  const __int16 *v44; // rax
  __int16 *v45; // rdx
  const __int16 *v46; // rax
  UINTN v47; // rdi
  __int64 v48; // rdi
  const __int16 *v49; // rax
  __int16 *v50; // rdx
  const __int16 *v51; // rax
  UINTN v52; // rdi
  __int64 v53; // rdi
  const __int16 *v54; // rax
  __int16 *v55; // rdx
  const __int16 *v56; // rax
  UINTN v57; // rdi
  __int64 v58; // r8
  __int16 *v59; // rax
  __int16 *v60; // rdx
  __int16 *v61; // rax
  unsigned int v62; // ebx
  char *p_Destination; // rdi
  __int64 v64; // rsi
  __int64 v65; // [rsp+20h] [rbp-E0h]
  __int64 v66; // [rsp+20h] [rbp-E0h]
  char v67[4]; // [rsp+30h] [rbp-D0h] BYREF
  char v68; // [rsp+34h] [rbp-CCh]
  unsigned int v69; // [rsp+3Ch] [rbp-C4h]
  unsigned int v70; // [rsp+40h] [rbp-C0h]
  EFI_GUID VendorGuid; // [rsp+48h] [rbp-B8h] BYREF
  UINTN v72; // [rsp+60h] [rbp-A0h] BYREF
  UINT32 Attributes; // [rsp+68h] [rbp-98h] BYREF
  UINTN DataSize; // [rsp+70h] [rbp-90h] BYREF
  void *v75; // [rsp+78h] [rbp-88h]
  char Buffer[6]; // [rsp+80h] [rbp-80h] BYREF
  char Destination; // [rsp+86h] [rbp-7Ah] BYREF
  char Data[2784]; // [rsp+180h] [rbp+80h] BYREF
  __int16 Source; // [rsp+C80h] [rbp+B80h] BYREF
  UINT32 v80; // [rsp+C88h] [rbp+B88h] BYREF

  v72 = 20i64;
  v80 = 0;
  DataSize = 2736i64;
  VendorGuid.Data1 = -326642109;
  *&VendorGuid.Data2 = 1270213540;
  *VendorGuid.Data4 = 1044374945;
  v2 = 0;
  *&VendorGuid.Data4[4] = -1458720202;
  v3 = 0;
  result = gRT_0->GetVariable(L"Setup", &VendorGuid, &Attributes, &DataSize, Data);
  if ( result >= 0 )
  {
    if ( gEfiHiiStringProtocol_1
      || (result = gBS_0->LocateProtocol(&EFI_HII_STRING_PROTOCOL_GUID, 0i64, &gEfiHiiStringProtocol_1), result >= 0) )
    {
      result = sub_10348(a1);
      v75 = result;
      v5 = result;
      if ( result )
      {
        if ( !Data[21] && !Data[17] )
        {
          v6 = 7417i64;
          if ( Data[11] )
            v6 = 7418i64;
          sub_10408(a1, v6, 7430i64, result);
          v7 = 7436i64;
          if ( Data[12] != 1 )
            v7 = 7435i64;
          sub_10408(a1, v7, 7431i64, v5);
          v8 = 7441i64;
          if ( Data[13] != 1 )
            v8 = 7442i64;
          sub_10408(a1, v8, 7432i64, v5);
          if ( (gRT_0->GetVariable(L"Tpm12VersionInfo", &PEI_TCG_INTERNAL_FLAGS_GUID, &v80, &v72, v67) & 0x8000000000000000ui64) == 0i64 )
          {
            gBS_0->SetMem(Buffer, 0x80ui64, 0);
            LODWORD(v65) = v69;
            sub_6DC(a1, 7493i64, L"%d.%d", BYTE1(v69), v65);
            gBS_0->SetMem(Buffer, 0x80ui64, 0);
            v9 = v70;
            v10 = Buffer;
            v11 = 4i64;
            do
            {
              Source = v9;
              if ( v9 )
                gBS_0->CopyMem(v10, &Source, 2ui64);
              v10 += 2;
              v9 >>= 8;
              --v11;
            }
            while ( v11 );
            sub_6DC(a1, 7492i64, aS, Buffer);
            v3 = 4;
          }
        }
        // Re-initialize DataSize to correct buffer size before second GetVariable
        v72 = sizeof(v67); // Explicitly set to 4 (size of v67[4])
        result = gRT_0->GetVariable(
                   L"PCRBitmap",
                   &PEI_TCG_INTERNAL_FLAGS_GUID,
                   &v80,
                   &v72,
                   v67);
        if ( result >= 0 )
        {
          gBS_0->SetMem(Buffer, 0x80ui64, 0);
          v12 = v67[0];
          v13 = Buffer;
          if ( (v67[0] & 1) != 0 )
          {
            v14 = L"SHA-1";
            v15 = 0i64;
            do
            {
              ++v14;
              ++v15;
            }
            while ( *v14 );
            v16 = 2 * v15;
            gBS_0->CopyMem(Buffer, L"SHA-1", v16);
            v12 = v67[0];
            v13 = &Buffer[v16];
            v2 = 1;
          }
          // ... (remaining code unchanged) ...
        }
      }
    }
  }
  return result;
}
