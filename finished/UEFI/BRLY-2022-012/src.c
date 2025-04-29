EFI_STATUS __fastcall SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
  ...
  
  char *ptr;
  
  if ( CommBuffer )
  {
    if ( CommBufferSize )
    {
      if ( *CommBufferSize == 0x18 )
      {
        ptr = *(char **)CommBuffer;
        if ( *(_QWORD *)CommBuffer )
        {
          if ( *((_DWORD *)CommBuffer + 2) &&
          CheckSmramMap_0(*(_QWORD *)CommBuffer, *((unsigned int *)CommBuffer + 2)) )
          {
            // buffer size pointed by ptr not validated, OOB write
            ptr[0x25] = 0; 
                           
            v7 = EFI_SECURITY_VIOLATION;
            if ( *((_BYTE *)CommBuffer + 0xC) == 4 )
            {
              if ( gSmmReadyToLockFlag2 )
                goto exit;
              if ( ptr != gLocal20Buffer )
                memcpy(ptr, gLocal20Buffer, 0x20); // OOB write
            }
            else if ( *((_BYTE *)CommBuffer + 0xC) == 5 )
            {
              if ( !sub_800025E0(ptr) )
                goto exit;
              if ( !sub_80002490(v10) )
                sub_800022C8(ptr, v10); // OOB write
                
  ...
  
  
  void __fastcall sub_800022C8(_BYTE *ptr, __int64 res)
{  
  ...
  
  ptr[0x25] = 1; // OOB write
  
  ...
}
