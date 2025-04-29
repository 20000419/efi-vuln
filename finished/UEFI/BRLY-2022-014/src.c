int __cdecl EfiPeiEndOfPeiPhaseNotifier(EFI_PEI_SERVICES **PeiServices)
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  if ( ((*PeiServices)->GetBootMode(PeiServices, &BootMode) & 0x80000000) == 0
    && BootMode == BOOT_ON_S3_RESUME
    && ((*PeiServices)->LocatePpi(PeiServices, &EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID, 0, 0, &Ppi) & 0x80000000) == 0 )
  {
    DataSize = 4;
    if ( (Ppi->GetVariable(Ppi, L"AmiCspGlobalNvsPtrVar", &gVariableGuid, 0, &DataSize, &Data) & 0x80000000) == 0 )
    {
      Ptr = Data;
      PcdPpi = LocatePcdPpi();
      *Ptr = PcdPpi->Get8(0xF2);
    }
  }
  __outbyte(0x43, 0x54);
  __outbyte(0x41, 0x12);
  return 0;
}
