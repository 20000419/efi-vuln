MACRO_EFI SwSmiHandler()
{
  unsigned __int8 *Struct;

  Struct = *(gUsbData + 22080);
  if ( Struct )
    *(gUsbData + 22080) = 0;
  else
    Struct = *(16 * MEMORY[0x40E] + 0x104);
  if ( !Struct )
    return EFI_OUT_OF_RESOURCES;
  CallApiFunction(Struct);
  return 0;
}

void __fastcall CallApiFunction(unsigned __int8 *Struct)
{
  unsigned __int8 Index;

  if ( Struct )
  {
    Index = *Struct;
    if ( *Struct )
    {
      if ( Index < 0x20 || Index > 0x38 )
      {
        Struct[2] = 0xF0; // Arbitrary SMRAM write
        return;
      }
      Index -= 31;
    }
    gUsbApiTable[Index]();
  }
}
