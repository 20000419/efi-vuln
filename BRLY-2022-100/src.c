void __fastcall NotifyFunction(EFI_CAPSULE_HEADER **Event, void *Context)
{
  unsigned __int64 i; // rdi
  __int64 v4; // r8
  __int64 v5; // r8
  __int64 v6; // rax
  unsigned __int64 v7; // [rsp+40h] [rbp-9h] BYREF
  __int64 v8; // [rsp+48h] [rbp-1h] BYREF
  __int64 v9; // [rsp+50h] [rbp+7h] BYREF
  __int64 v10; // [rsp+58h] [rbp+Fh] BYREF
  __int64 v11; // [rsp+60h] [rbp+17h] BYREF
  __int64 v12; // [rsp+68h] [rbp+1Fh] BYREF
  char *v13; // [rsp+70h] [rbp+27h] BYREF
  _BYTE v14[16]; // [rsp+78h] [rbp+2Fh] BYREF
  __int64 v15[3]; // [rsp+88h] [rbp+3Fh] BYREF
  unsigned __int16 v16; // [rsp+C0h] [rbp+77h] BYREF
  int v17; // [rsp+C8h] [rbp+7Fh] BYREF

  v12 = 0i64;
  v8 = 0i64;
  v9 = 0i64;
  v10 = 0i64;
  v11 = 0i64;
  v17 = 0;
  if ( ((__int64 (__fastcall *)(__int64, EFI_GUID *, _QWORD, unsigned __int64 *, __int64 *))gBS->LocateHandleBuffer)(
         2i64,
         &EFI_FIRMWARE_VOLUME2_PROTOCOL_GUID,
         0i64,
         &v7,
         v15) >= 0
    && v7 )
  {
    v9 = 15i64;
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, _QWORD, __int64 *, _BYTE *))gRT->GetVariable)(// <= first call (we can rewrite DataSize here)
      L"MPDTContent",
      &NameGuid,
      0i64,
      &v9,
      v14);
    for ( i = 0i64; i < v7; ++i )
    {
      if ( ((__int64 (__fastcall *)(_QWORD, EFI_GUID *, __int64 *))gBS->HandleProtocol)(
             *(_QWORD *)(v15[0] + 8 * i),
             &EFI_FIRMWARE_VOLUME2_PROTOCOL_GUID,
             &v11) < 0 )
        goto LABEL_18;
      LOBYTE(v4) = 25;
      if ( (*(__int64 (__fastcall **)(__int64, EFI_GUID *, __int64, _QWORD, __int64 *, __int64 *, int *))(v11 + 24))(
             v11,
             &NameGuid,
             v4,
             0i64,
             &v12,
             &v8,
             &v17) >= 0 )
      {
        ((void (__fastcall *)(__int64, __int64, __int64 *))gBS->AllocatePool)(4i64, v8, &v10);
        v10 = v12;
        v13 = 0i64;
        v16 = 0;
        if ( v12 )
        {
          v6 = sub_C58(v14[1], v12, v8, &v16, (unsigned int **)&v13, v12);
          if ( v6 >= 0 )
          {
            if ( v13 )
              v6 = sub_EF8(v13, v16);
            else
              v6 = 0x8000000000000002ui64;
          }
          v5 = v6;
          if ( v6 >= 0 )
            continue;
        }
        else
        {
          v5 = 0x8000000000000015ui64;
        }
        sub_4E0((__int64)v14, 129, v5);
      }
    }
    ((void (__fastcall *)(const __int16 *, EFI_GUID *, __int64, __int64, _BYTE *))gRT->SetVariable)(
      L"MPDTContent",
      &NameGuid,
      7i64,
      v9,
      v14);
    if ( i >= v7 )
      ((void (__fastcall *)(EFI_CAPSULE_HEADER **))gBS->CloseEvent)(Event);
    ((void (__fastcall *)(__int64))gBS->FreePool)(v10);
  }
LABEL_18:
  ((void (__fastcall *)(EFI_CAPSULE_HEADER **))gBS->CloseEvent)(Event);
}
