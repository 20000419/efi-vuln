int __thiscall sub_FFAE2B82(void *this)
{
  ...
  const EFI_PEI_SERVICES **PeiServices;
  char CpuSetupData[1072];
  UINTN DataSize;
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *Ppi;

  ...
  DataSize = 1072;
  Ppi->GetVariable(Ppi, L"SaSetup", &gSaSetupGuid, 0, &DataSize, CpuSetupData);
  Ppi->GetVariable(Ppi, L"CpuSetup", &gCpuSetupGuid, 0, &DataSize, CpuSetupData);
  ...
  return 0;
}
