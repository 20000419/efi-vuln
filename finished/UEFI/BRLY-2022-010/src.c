EFI_STATUS __fastcall SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
  ...
  
  // CommBuffer size not validated
  ptr = SmmAllocateWrite(*CommBufferSize, CommBuffer);
  
  if ( ptr )
  {
      ...
      
      nested_ptr = (void *)*((_QWORD *)ptr + 5);
      ptr_plus40_ptr = (char *)ptr + 0x40;
      
      if ( nested_ptr )
        // Data pointer calculation
        dest = (char *)ptr + *((_QWORD *)ptr + 6) + 0x40;
        
      ptr_plus18_ptr = (char *)ptr + 0x18;
      
      if ( *(_BYTE *)ptr )
	      // Read variable
        v15 = sub_800016FC(                     
                (__int64)&v22,
                ptr_plus40_ptr, // Name
                ptr_plus18_ptr, // Guid
                (char *)ptr + 0x38,
                (size_t *)ptr + 5, // Size
                dest); // Data
      else
	      // Write variable
        v15 = sub_800018A8(
                (__int64)&v22,
				        ptr_plus40_ptr, // Name
				        ptr_plus18_ptr, // Guid
				        *((_DWORD *)ptr + 0xE),
				        nested_ptr, // Size
				        dest); // Data
				        
    ...
    
unsigned __fastcall sub_800016FC(__int64 a1, void *ptr_plus40_ptr, void *ptr_plus18_ptr, void *ptr_plus38_ptr, size_t *size_ptr, void *dest)
{
  ...
  
  Status = GetVar(ptr_plus40_ptr, ptr_plus18_ptr, &Buffer, (UINTN *)v15);
  
  ...
  
    memcpy(dest, Buffer, BufferSize);
  
  ...
}


Status = gSmst->SmmRegisterProtocolNotify(&gUnknownProtocol296EB418Guid, UnknownProtocol296EB418Notifier, &Registration);

EFI_STATUS __fastcall UnknownSmmProtocol2Notifier(const EFI_GUID *Protocol, void *Interface, EFI_HANDLE Handle)
{
  if ( gSmiHandlerDispatchHandle )
  {
    gSmst->SmiHandlerUnRegister(gSmiHandlerDispatchHandle);
    gSmiHandlerDispatchHandle = 0;
  }
  return 0;
}
