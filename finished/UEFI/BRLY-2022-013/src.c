gSmst->SmiHandlerRegister(SmiHandler, &gSmiHandlerGuid, &SmiHandlerDispatchHandle);
//The SMI handler itself is located at offset 0x1D90 in the driver:

EFI_STATUS __fastcall SmiHandler(EFI_HANDLE DispatchHandle, const void *Context, void *CommBuffer, UINTN *CommBufferSize)
{
  ...
  
  if ( CommBuffer )
  {
    if ( CommBufferSize )
    {
      if ( !(-(__int64)(*CommBufferSize != 0x288) & EFI_INVALID_PARAMETER) )
      {
//As we can see the specified size of input Communication Buffer should be equal to 0x288 bytes. Hence, its validated part (validation routine is in PiSmmCommunicationSmm SMM module) is 0x288 bytes.

        SmmAllocateZeroWrapper((char **)&gCommBufferCopy, *CommBufferSize);
        CommBufferCopy = gCommBufferCopy;
        if ( gCommBufferCopy )
        {
          if ( *CommBufferSize_1 && gCommBufferCopy != CommBuffer )
          {
            memcpy(gCommBufferCopy, CommBuffer, *CommBufferSize);
            CommBufferCopy = gCommBufferCopy;
          }
//So 0x288 bytes allocated in SMRAM allow to copy entire CommBuffer contents.The code below will process WStrings (Unicode strings) in original CommBuffer, with CommBufferCopy[0x282] = iterations (WStrings) count, 0 to 0xFF:

          counter = 0;                       
          if ( CommBufferCopy[0x282] )           
          {
            offset = 0;
            do
            {
//Here a pointer to a WString inside the original CommBuffer (not to its copy) is retrieved, then wstrlen() invoked on the pointed WString. The limit is 1000000 WORDs!The string processed inside the original CommBuffer, which should be 0x288 bytes only! Iterations count is controllable! So, we have multiple OOB reads:

              str_ptr = *(_WORD **)&CommBuffer[offset + 0x18];
              if ( str_ptr )                    
              {                                 
                strlen_inwords = GetWStringLengthInWords(str_ptr, 1000000);
                *(_QWORD *)(offset + v11 + 0x18) = 0;
                CommBufferCopy = gCommBufferCopy;
                strlen_inbytes = 2 * strlen_inwords + 2;
                buffer = (char **)((char *)gCommBufferCopy + offset + 0x18);
                if ( buffer )
                {
                  status = SmmAllocateZeroWrapper(buffer, 2 * strlen_inwords + 2); // pointless allocation of a buffer (not used further)
                  CommBufferCopy = gCommBufferCopy;
                }
                else
                {
                  status = EFI_INVALID_PARAMETER;
                }
//Below wstrcopy() is invoked to copy the pointed WString from CommBuffer and the limit is the same = 1000000 WORDs! WString is copied into an SMRAM-copy of CommBuffer! Allocation size was 0x288 bytes! So, we have multiple OOB writes:

                if ( !status )
                {                               
                  WStringCopy(                  
                    *(_QWORD *)&CommBufferCopy[offset + 0x18], // dest
                    2 * strlen_inbytes,                        // size
                    *(_WORD **)&CommBuffer[offset + 0x18]);    // src
                  CommBufferCopy = gCommBufferCopy;
                }
              }
              
              ++counter;
              offset += 0x20;
            }
            while ( counter < CommBufferCopy[0x282] );
          }
        }
      }
    }
  }
  return 0;
}
//The implementation of wstrlen():

unsigned __int64 __fastcall GetWStringLengthInWords(_WORD *a1, unsigned __int64 a2)
{
  unsigned __int64 result; // rax

  if ( !a1 || !a2 )
    return 0;
  result = 0;
  if ( *a1 )
  {
    while ( result < a2 - 1 )
    {
      if ( !a1[++result] )
        return result;
    }
    result = a2;
  }
  
  return result;
}
//The implementation of wstrcopy():

MACRO_EFI __fastcall WStringCopy(__int64 ptr1, unsigned __int64 size, _WORD *ptr2)
{
  unsigned __int64 strlen_inwords; // rax
  unsigned __int64 size_1; // rdx
  char *ptr1_1; // r10 mov     r10, rcx
  char *ptr2_1; // r11 mov     r11, r8
  __int16 val; // ax
  signed __int64 v9; // r11

  if ( !ptr1 || !ptr2 || size > 1000000 || !size )
    return EFI_INVALID_PARAMETER;
  strlen_inwords = GetWStringLengthInWords(ptr2, size);
  if ( size_1 <= strlen_inwords )
    return EFI_BUFFER_TOO_SMALL;
  if ( ptr2_1 > ptr1_1 )
    goto LABEL_19;
  if ( ptr1_1 < &ptr2_1[2 * strlen_inwords + 2] )
    return EFI_ACCESS_DENIED;
  if ( ptr2_1 >= ptr1_1 )
  {
LABEL_19:
    if ( ptr2_1 < &ptr1_1[2 * size_1] )
      return EFI_ACCESS_DENIED;
  }
  val = *(_WORD *)ptr2_1;
  if ( *(_WORD *)ptr2_1 )
  {
    v9 = ptr2_1 - ptr1_1;
    do
    {
      *(_WORD *)ptr1_1 = val;
      ptr1_1 += 2;
      val = *(_WORD *)&ptr1_1[v9];
    }
    while ( val );
  }
  *(_WORD *)ptr1_1 = 0;
  return 0i64;
}
//So a possible attacker could overflow the heap buffer allocated for the copy of Communication Buffer with the strings data (arbitrary data with a controllable end - 0x0000 and iterations count in CommBufferCopy[0x282]). This could lead to corrupting heap structures and data/code stored next to it with a potential gaining arbitrary code execution.

//This leads to corrupting memory in SMRAM at a controllable address with a predictable data and size. It could be used for example to change SMI handler's code or modify SMRAM Map structures to break input pointers validation for other SMI handlers, hence to completely make this mitigation inefficient. This could lead to gaining arbitrary code execution in SMM.

//To exploit this vulnerability it is enough to specify in a CommBuffer:1. Set CommBuffer to contain these values: *(QWORD *)CommBuffer = SMRAM_BASE - 1 and *size_ptr = 1.2. Call SW SMI (SwSmi number is specified in the UEFI ACPI table) via 0xB2 IO port, prior to it SMI handler GUID 67511ba8-5a25-4bba-ac59-f00feb85dffa and Communication Buffer size should be specified in Communication Buffer.

//It should be noted that this SMI handler will be unregistered in a callback-notifier for SMM protocol EDKII_SMM_READY_TO_BOOT_PROTOCOL:

Smst->SmmRegisterProtocolNotify(
           &EDKII_SMM_READY_TO_BOOT_PROTOCOL_GUID,
           EfiSmmReadyToBootProtocolNotifier,
           &Handle);

EFI_STATUS __fastcall EdkIISmmReadyToBootProtocolNotifier(const EFI_GUID *Protocol, void *Interface, EFI_HANDLE Handle)
{
  if ( gSmiHandlerDispatchHandle )
  {
    gSmst->SmiHandlerUnRegister(gSmiHandlerDispatchHandle);
    gSmiHandlerDispatchHandle = 0;
  }
  return 0;
}
