FI_STATUS __fastcall SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
	...
	
  if ( CommBuffer && CommBufferSize && *CommBufferSize == 0x18 )
  {
    if ( !*(_QWORD *)CommBuffer )
      goto LABEL_18;
    size_ptr = (unsigned int *)((char *)CommBuffer + 8);
    
    if ( !*((_DWORD *)CommBuffer + 2) )
      goto LABEL_18;
    
    // Buffer is validated here, but the size is not used further
    v6 = CheckSmramMap_0(*(_QWORD *)CommBuffer, *size_ptr);
    v7 = -(__int64)(v6 == 0) & EFI_SECURITY_VIOLATION;
    if ( v6 )
    {
      v8 = 0;
      if ( size_ptr )
        v8 = CheckSmramMap_0(size_ptr, 4);
      v7 = -(__int64)(v8 == 0) & EFI_SECURITY_VIOLATION;
    }
    
    if ( !v7 )
    {
LABEL_18:
      if ( CommBuffer_1[3] )
        v9 = EFI_UNSUPPORTED;
      else
	      // Buffer size is not passed inside
        v9 = sub_800024D0(*(_BYTE **)CommBuffer);
      *((_QWORD *)CommBuffer + 2) = v9;
    }
  }
  
  return 0;
}
