MACRO_EFI __fastcall ChildSwSmiHandler(
        EFI_HANDLE DispatchHandle,
        const void *Context,
        unsigned int *CommBuffer,
        UINTN *CommBufferSize)
{
  __int64 Command;
  // ... [existing variables] ...

  if ( CommBuffer && CommBufferSize && *CommBufferSize >= 0x18 )
  {
    if ( !ValidateMemoryBuffer(CommBuffer, *CommBufferSize) )
      return 0;
    if ( (*(gPhysicalAddr + 0x78040) & 0xF0000) != 0 )
      return EFI_UNSUPPORTED;
    Command = *CommBuffer;
    if ( *CommBuffer <= 6 )
    {
      if ( *CommBuffer == 6 )
      {
        if ( !ValidateMemoryBuffer(CommBuffer + 4, 8) )
          return 0;
        // Validate CommBuffer[4] before passing to sub_1624
        if (!IsValidUserControlledValue(CommBuffer[4]))
          return EFI_ACCESS_DENIED;
        v11 = sub_1624(CommBuffer[4], CommBuffer[5]);
        goto LABEL_48;
      }
      ...
    }
    ...
  }
  ...
}

unsigned __int64 __fastcall sub_1624(__int64 a1, int a2)
{
  // Validate input before calling sub_ED0
  if (!IsValidUserControlledValue(a1))
    return 0;
    
  __int64 v3;
  // ... [existing variables] ...

  v3 = sub_ED0(a1);
  ...
}

__int64 __fastcall sub_ED0(int Value)
{
  __int64 v1;
  _DWORD *Addr;
  // ... [existing variables] ...

  v1 = 0;
  v9 = 0;

  // Check for integer overflow
  if (Value > INT_MAX - 120)
    return 0;
    
  // Calculate address
  Addr = (DWORD*)(((Value + 120) << 12) + 0xE0000000);
  
  // Validate calculated address
  if (!IsValidSMRAMAddress((UINTN)Addr, 8)) // Check for 8 DWORDs access
    return 0;

  if ( *(((Value + 120) << 12) + 0xE0000002) == 0xFFFF )
  {
    // ... [existing code] ...
  }
  else
  {
    // ... [existing code up to write operation] ...
    
    if ( (Addr[4] & 0xFFFFFFF0) != 0 || v7 )
    {
      // Validate write address
      if (!IsValidSMRAMWriteAddress((UINTN)&Addr[1], 4)) // Check for DWORD write
        return 0;
        
      Addr[1] |= 0x106; // Safe write after validation
      return v8;
    }
    else
    {
      return 0;
    }
  }
}

// New validation functions
BOOLEAN IsValidUserControlledValue(INT32 value)
{
  // Ensure value doesn't cause overflow and is within expected range
  return (value >= 0 && value <= 0x1000);
}

BOOLEAN IsValidSMRAMAddress(UINTN address, UINTN size)
{
  // Check if address is within SMRAM range and size doesn't overflow
  UINTN smramBase = 0xE0000000;
  UINTN smramSize = 0x2000000;
  
  return (address >= smramBase && address + size <= smramBase + smramSize);
}

BOOLEAN IsValidSMRAMWriteAddress(UINTN address, UINTN size)
{
  // Additional checks for writable regions within SMRAM
  UINTN writableBase = 0xE0100000;
  UINTN writableSize = 0x100000;
  
  return (address >= writableBase && address + size <= writableBase + writableSize);
}
