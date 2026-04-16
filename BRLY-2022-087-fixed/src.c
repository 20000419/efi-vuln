char __fastcall sub_9338(__int64 a1, unsigned __int64 a2)
{
  char *v2; // rax
  unsigned int *v3; // rbx
  int v4; // ecx
  unsigned __int64 v5; // rax
  char *v6; // r9
  unsigned __int64 v7; // rax
  unsigned __int64 v8; // rax
  unsigned __int8 v9; // r14
  __int64 v10; // rdx
  __int64 v11; // rcx
  unsigned __int16 v12; // ax
  __int64 v13; // r9
  unsigned __int16 v14; // dx
  char v15; // al
  unsigned __int64 v16; // rsi
  int v17; // eax
  char *v18; // rbx
  char v19; // al
  char *v20; // rax
  char *v21; // r8
  char *v22; // r8
  __int64 v23; // r15
  unsigned __int64 v24; // rdi
  __int16 v25; // ax
  char v26; // dl
  unsigned __int64 v27; // rbx
  char v28; // dl
  char v29; // dl
  unsigned int v30; // ebx
  char v31; // dl
  unsigned int v32; // ebx
  char v33; // dl
  char v34; // dl
  char v35; // dl
  unsigned int v36; // ebx
  char v37; // dl
  unsigned __int64 v38; // rax
  char v39; // bl
  unsigned __int64 v40; // rax
  unsigned __int8 *v41; // r8
  __int64 v42; // rax
  UINT32 v43; // ebx
  __int64 v44; // rax
  bool v45; // zf
  _BYTE *v46; // rax
  int v47; // ebx
  unsigned int v48; // r8d
  unsigned __int64 v49; // rax
  unsigned __int64 v50; // rbx
  unsigned __int64 v51; // r14
  char v52; // al
  unsigned __int64 v53; // rbx
  unsigned __int8 v54; // di
  __int64 v55; // rax
  unsigned __int64 i; // rdi
  __int64 v57; // rcx
  unsigned __int8 v58; // r8
  unsigned __int8 v59; // dl
  __int64 v60; // rax
  unsigned __int8 v61; // cl
  unsigned __int8 v62; // al
  unsigned __int8 v63; // di
  unsigned __int8 v64; // dl
  __int64 v65; // rax
  unsigned __int8 v66; // cl
  unsigned __int8 v67; // al
  char *v68; // r8
  __int64 v70; // [rsp+20h] [rbp-89h]
  __int64 v71; // [rsp+20h] [rbp-89h]
  __int64 v72; // [rsp+20h] [rbp-89h]
  __int64 v73; // [rsp+20h] [rbp-89h]
  __int64 v74; // [rsp+20h] [rbp-89h]
  __int64 v75; // [rsp+20h] [rbp-89h]
  __int64 v76; // [rsp+20h] [rbp-89h]
  __int64 v77; // [rsp+20h] [rbp-89h]
  __int64 v78; // [rsp+20h] [rbp-89h]
  __int64 v79; // [rsp+28h] [rbp-81h]
  __int64 v80; // [rsp+30h] [rbp-79h]
  UINTN DataSize; // [rsp+40h] [rbp-69h] BYREF
  char *v82; // [rsp+48h] [rbp-61h] BYREF
  char *v83; // [rsp+50h] [rbp-59h]
  int v84; // [rsp+58h] [rbp-51h] BYREF
  UINT32 Attributes; // [rsp+5Ch] [rbp-4Dh] BYREF
  UINT32 v86; // [rsp+60h] [rbp-49h] BYREF
  char v87[6]; // [rsp+68h] [rbp-41h] BYREF
  char v88; // [rsp+6Eh] [rbp-3Bh]
  void *DxeCpuInfoProtocol; // [rsp+70h] [rbp-39h] BYREF
  _BYTE v90[16]; // [rsp+78h] [rbp-31h] BYREF
  __int64 v91; // [rsp+88h] [rbp-21h] BYREF
  char Data[20]; // [rsp+90h] [rbp-19h] BYREF
  char v93; // [rsp+A4h] [rbp-5h]
  char v94; // [rsp+110h] [rbp+67h] BYREF
  unsigned __int64 v95; // [rsp+118h] [rbp+6Fh] BYREF
  int v96; // [rsp+120h] [rbp+77h] BYREF
  UINT32 v97; // [rsp+128h] [rbp+7Fh] BYREF

  v95 = a2;
  DataSize = 176i64;
  LOBYTE(v95) = 0;
  v96 = 0;
  qword_A4188 = 0i64;
  v2 = (gRT->GetVariable)(L"SetupVolatileData", &EFI_SETUP_VARIABLE_GUID, 0i64, &DataSize, byte_A4600);
  if ( v2 < 0 )
    return v2;
  v2 = (gBS->LocateProtocol)(&DXE_CPU_INFO_PROTOCOL_GUID, 0i64, &DxeCpuInfoProtocol);
  if ( v2 < 0 )
    return v2;
  sub_EBFC(&v95, &v94);
  v3 = *(DxeCpuInfoProtocol + 2);
  *(v3 + 3) = *(v3 + 3);
  *(v3 + 9) = *(*(DxeCpuInfoProtocol + 2) + 36i64);
  v4 = 100 * v95;
  v3[8] = 0;
  v3[6] = v4;
  sub_2A0(1u, 0i64, 0i64, &v84, 0i64);
  if ( (v84 & 0x800) != 0 )
    v5 = __readmsr(0xC80u);
  else
    LODWORD(v5) = v95;
  v6 = aEnabled;
  if ( (v5 & 0x80000000) == 0i64 )
    v6 = aDisabled;
  sub_6FC(qword_A4168, 0x464u, aA, v6);
  sub_6FC(qword_A4168, 0x1F7u, aA, *(v3 + 3));
  sub_6FC(qword_A4168, 0x1FCu, L"%d MHz", v3[6]);
  sub_6FC(qword_A4168, 0x1F9u, a0xX, *v3);
  sub_6FC(qword_A4168, 0xFCBu, aA, aNotImplemented);
  v7 = __readmsr(0x8Bu);
  v8 = ((HIDWORD(v7) << 32) | v7) >> 32;
  if ( v8 )
    sub_6FC(qword_A4168, 0xFCEu, asc_A2980, v8);
  sub_6FC(qword_A4168, 0xFD1u, L"%dCore(s) / %dThread(s)");
  v9 = 0;
  do
  {
    v10 = *(v3 + 9);
    v11 = 9i64 * v9;
    switch ( *(v11 + v10 + 1) )
    {
      case 1:
        v15 = *(v11 + v10 + 2);
        if ( v15 == 1 )
        {
          v13 = *(v11 + v10 + 3);
          v14 = 511;
        }
        else
        {
          if ( v15 != 2 )
            goto LABEL_26;
          v13 = *(v11 + v10 + 3);
          v14 = 514;
        }
        goto LABEL_19;
      case 2:
        v13 = *(v11 + v10 + 3);
        v14 = 517;
LABEL_19:
        if ( *(v3 + 22) == 1 )
        {
          sub_6FC(qword_A4168, v14, L"%d KB");
        }
        else
        {
          LODWORD(v70) = *(v3 + 22);
          sub_6FC(qword_A4168, v14, L"%d KB x %d", v13, v70);
        }
        goto LABEL_26;
      case 3:
        v12 = 520;
        break;
      case 4:
        v12 = 523;
        break;
      default:
        goto LABEL_26;
    }
    sub_6FC(qword_A4168, v12, L"%d MB");
LABEL_26:
    ++v9;
  }
  while ( v9 <= *(v3 + 44) );
  v16 = 0i64;
  v17 = sub_EB10() - &unk_806C0;
  if ( !v17 || (v18 = 0i64, v17 == 16) )
    v18 = aTigerlake;
  v19 = sub_EB3C();
  if ( v19 )
  {
    switch ( v19 )
    {
      case 1:
        v20 = aDt;
        break;
      case 2:
        v20 = aUlx;
        break;
      case 3:
        v20 = aHalo;
        break;
      default:
        v20 = 0i64;
        break;
    }
  }
  else
  {
    v20 = aUlt;
  }
  if ( v18 && v20 )
    sub_6FC(qword_A4168, 0xFC5u, L"%a %a", v18, v20);
  else
    sub_6FC(qword_A4168, 0xFC5u, aA, aUnknown);
  DataSize = 47i64;
  v2 = (gRT->GetVariable)(L"SetupCpuFeatures", &EFI_SETUP_VARIABLE_GUID, &Attributes, &DataSize, Data);
  if ( v2 >= 0 )
  {
    v21 = aSupported_1;
    if ( !Data[6] )
      v21 = aNotSupported_1;
    sub_D2F0(v90, 0xFui64, v21);
    sub_6FC(qword_A4168, 0x20Fu, aA, v90);
    v22 = aSupported_1;
    if ( !Data[8] )
      v22 = aNotSupported_1;
    sub_D2F0(v90, 0xFui64, v22);
    sub_6FC(qword_A4168, 0x212u, aA, v90);
    v2 = __readmsr(0x606u);
    v23 = 2i64 << ((v2 & 0xFu) - 1);
    if ( v23 )
    {
      v24 = __readmsr(0x614u);
      v25 = WORD2(v24) & 0x7FFF;
      if ( (v24 & 0x7FFF00000000i64) == 0 )
        v25 = 0x7FFF;
      LODWORD(v71) = (1000 * (v25 % v23) / v23);
      sub_6FC(qword_A4168, 0x320u, L"%d.%d", (v25 / v23), v71);
      LODWORD(v72) = (1000 * ((WORD1(v24) & 0x7FFFui64) % v23) / v23);
      sub_6FC(qword_A4168, 0x323u, L"%d.%d", (WORD1(v24) & 0x7FFFui64) / v23, v72);
      LODWORD(v73) = (1000 * ((v24 & 0x7FFF) % v23) / v23);
      sub_6FC(qword_A4168, 0x32Cu, L"%d.%d", ((v24 & 0x7FFF) / v23), v73);
      v95 = __readmsr(0x610u);
      LODWORD(v74) = (1000 * ((v95 & 0x7FFF) % v23) / v23);
      sub_6FC(qword_A4168, 0x326u, L"%d.%d", ((v95 & 0x7FFF) / v23), v74);
      LODWORD(v75) = (1000 * ((WORD2(v95) & 0x7FFF) % v23) / v23);
      sub_6FC(qword_A4168, 0x329u, L"%d.%d", ((WORD2(v95) & 0x7FFF) / v23), v75);
      v26 = byte_A3FC8;
      v27 = __readmsr(0x1ADu);
      v95 = v27;
      if ( !byte_A3FC8 )
        v26 = v27;
      byte_A3FC8 = v26;
      sub_6FC(qword_A4168, 0x397u, aD, v27);
      v28 = byte_A3FCD;
      if ( !byte_A3FCD )
        v28 = BYTE1(v27);
      byte_A3FCD = v28;
      sub_6FC(qword_A4168, 0x39Au, aD, BYTE1(v27));
      v29 = byte_A3FCF;
      if ( !byte_A3FCF )
        v29 = BYTE2(v27);
      byte_A3FCF = v29;
      sub_6FC(qword_A4168, 0x39Du, aD, BYTE2(v27));
      v30 = BYTE3(v27);
      v31 = byte_A3FC9;
      if ( !byte_A3FC9 )
        v31 = v30;
      byte_A3FC9 = v31;
      sub_6FC(qword_A4168, 0x3A0u, aD, v30);
      v32 = HIDWORD(v95);
      v33 = byte_A3FCC;
      if ( !byte_A3FCC )
        v33 = BYTE4(v95);
      byte_A3FCC = v33;
      sub_6FC(qword_A4168, 0x3A3u, aD, BYTE4(v95));
      v34 = byte_A3FCB;
      if ( !byte_A3FCB )
        v34 = BYTE1(v32);
      byte_A3FCB = v34;
      sub_6FC(qword_A4168, 0x3A6u, aD, BYTE1(v32));
      v35 = byte_A3FD0;
      if ( !byte_A3FD0 )
        v35 = BYTE2(v32);
      byte_A3FD0 = v35;
      sub_6FC(qword_A4168, 0x3A9u, aD, BYTE2(v32));
      v36 = HIBYTE(v32);
      v37 = byte_A3FCE;
      if ( !byte_A3FCE )
        v37 = v36;
      byte_A3FCE = v37;
      sub_6FC(qword_A4168, 0x3ACu, aD, v36);
      v38 = __readmsr(0xCEu);
      v39 = (HIDWORD(v38) >> 1) & 3;
      sub_6FC(qword_A4168, 0x266u, aD, ((HIDWORD(v38) >> 1) & 3) + 1);
      if ( v39 )
      {
        __readmsr(0x648u);
        sub_6FC(qword_A4168, 0x269u, L"Ratio:%d TAR:%d PL1:%d.%dW");
        __readmsr(0x649u);
        sub_6FC(qword_A4168, 0x26Cu, L"Ratio:%d TAR:%d PL1:%d.%dW");
        __readmsr(0x64Au);
        sub_6FC(qword_A4168, 0x26Fu, L"Ratio:%d TAR:%d PL1:%d.%dW");
        v95 = __readmsr(0x610u);
        LODWORD(v76) = (1000 * ((MEMORY[0xFEDC59A0] & 0x7FFF) % v23) / v23);
        sub_6FC(
          qword_A4168,
          0x278u,
          L"%d.%dW (MSR:%d.%d)",
          ((MEMORY[0xFEDC59A0] & 0x7FFF) / v23),
          v76,
          (v95 & 0x7FFF) / v23,
          (1000 * ((v95 & 0x7FFF) % v23) / v23));
        LODWORD(v80) = (1000 * ((WORD2(v95) & 0x7FFF) % v23) / v23);
        LODWORD(v79) = ((WORD2(v95) & 0x7FFF) / v23);
        LODWORD(v77) = (1000 * ((MEMORY[0xFEDC59A4] & 0x7FFF) % v23) / v23);
        sub_6FC(qword_A4168, 0x27Bu, L"%d.%dW (MSR:%d.%d)", ((MEMORY[0xFEDC59A4] & 0x7FFF) / v23), v77, v79, v80);
        v40 = __readmsr(0x64Cu);
        v41 = L"%d (Locked)";
        if ( (v40 & 0x80000000) == 0i64 )
          v41 = L"%d (Unlocked)";
        sub_6FC(qword_A4168, 0x275u, v41, v40);
      }
      DataSize = 8i64;
      v42 = (gRT->GetVariable)(L"CpuSetupVolatileData", &CPU_SETUP_VARIABLE_GUID, &v97, &DataSize, v87);
      v43 = v97;
      if ( v42 < 0 )
        v43 = 6;
      v97 = v43;
      v44 = sub_F470(&CPU_DATA_HOB_GUID);
      v45 = v44 == -24;
      v46 = (v44 + 24);
      qword_A4188 = v46;
      v88 = v45 ? 0 : ~*v46;
      (gRT->SetVariable)(L"CpuSetupVolatileData", &CPU_SETUP_VARIABLE_GUID, v43, 8i64, v87);
      v47 = *(&loc_5A10 + (MEMORY[0xC0000048] & 0xFFFFFFFE)) & 0xFFE;
      sub_2A0(0x15u, 0i64, 0i64, &v96, 0i64);
      if ( v96 == 38400000 )
        v48 = 300 * v47;
      else
        v48 = v96 == 24000000 ? (375 * v47) >> 1 : 0;
      LODWORD(v78) = v48 % 0x3E8;
      sub_6FC(qword_A4168, 0x1E0u, L"%d.%dMHz", (v48 / 0x3E8), v78);
      LOBYTE(v2) = sub_EB3C();
      if ( v2 == 3 )
      {
        v2 = (gBS->LocateProtocol)(&EFI_PI_MP_SERVICES_PROTOCOL_GUID, 0i64, &gEfiPiMpServicesProtocol);
        if ( v2 >= 0 )
        {
          v49 = __readmsr(0x35u);
          v50 = v49;
          v51 = v49;
          v52 = byte_A3FCA;
          v53 = v50 >> 16;
          if ( v53 < v51 )
            v52 = 1;
          byte_A3FCA = v52;
          v82 = sub_EC68(4 * v53);
          v2 = sub_EC68(8 * v53);
          v83 = v2;
          if ( v82 )
          {
            if ( v2 )
            {
              (*(gEfiPiMpServicesProtocol + 6))(gEfiPiMpServicesProtocol, &v91);
              v54 = 0;
              if ( v51 )
              {
                v55 = 0i64;
                do
                {
                  if ( v55 == v91 )
                    sub_8C94(&v82);
                  else
                    (*(gEfiPiMpServicesProtocol + 3))(gEfiPiMpServicesProtocol, sub_8C94, v55, 0i64, 0i64, &v82, 0i64);
                  v55 = ++v54;
                }
                while ( v54 < v51 );
              }
              for ( i = 0i64; i < v53; ++i )
                sub_6FC(qword_A4168, word_A2AB0[i], aD, v82[4 * i]);
              v57 = 1i64;
              v93 = 0;
              if ( v53 > 1 )
              {
                while ( BYTE1(*v82) == BYTE1(*&v82[4 * v57]) )
                {
                  if ( ++v57 >= v53 )
                    goto LABEL_100;
                }
                v93 = 1;
              }
LABEL_100:
              (gRT->SetVariable)(L"SetupCpuFeatures", &EFI_SETUP_VARIABLE_GUID, Attributes, 47i64, Data);
              if ( *(*(DxeCpuInfoProtocol + 2) + 66i64) )
              {
                v58 = -1;
                v59 = 0;
                if ( v53 )
                {
                  v60 = 0i64;
                  do
                  {
                    v61 = v82[4 * v60 + 1];
                    v62 = v58;
                    if ( v58 > v61 )
                      v62 = v61;
                    ++v59;
                    v58 = v62;
                    v60 = v59;
                  }
                  while ( v59 < v53 );
                }
                v63 = 0;
                v64 = 0;
                if ( v53 )
                {
                  v65 = 0i64;
                  do
                  {
                    v66 = v82[4 * v65];
                    v67 = v63;
                    if ( v63 < v66 )
                      v67 = v66;
                    ++v64;
                    v63 = v67;
                    v65 = v64;
                  }
                  while ( v64 < v53 );
                }
                DataSize = 654i64;
                (gRT->GetVariable)(             // <= first call (we can rewrite DataSize here)
                  L"CpuSetup",
                  &CPU_SETUP_VARIABLE_GUID,
                  &v86,
                  &DataSize,
                  &unk_A4760);
                byte_A4897 = v63;
                if ( v53 )
                {
                  v68 = v82;
                  do
                  {
                    *(&unk_A4760 + v16 + 545) = v68[4 * v16];
                    ++v16;
                  }
                  while ( v16 < v53 );
                }
              DataSize = 654i64;  // Re-initialize DataSize with the correct size before SetVariable
                (gRT->SetVariable)(
                  L"CpuSetup",
                  &CPU_SETUP_VARIABLE_GUID,
                  v86,
                  DataSize,  // Use the re-initialized correct size
                  &unk_A4760
                );
              }
              (gBS->FreePool)(v82);
              LOBYTE(v2) = (gBS->FreePool)(v83);
            }
          }
        }
      }
    }
  }
  return v2;
}
