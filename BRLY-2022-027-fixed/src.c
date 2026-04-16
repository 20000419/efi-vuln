int __thiscall sub_FFAE2B82(void *this)
{
  // [Collapsed local declarations]
  const EFI_PEI_SERVICES **PeiServices;
  char CpuSetupData[1072];
  UINTN saSetupSize = sizeof(CpuSetupData);  // Dedicated size for SaSetup
  UINTN cpuSetupSize = sizeof(CpuSetupData); // Dedicated size for CpuSetup
  EFI_PEI_READ_ONLY_VARIABLE2_PPI *Ppi;
  EFI_STATUS status;

  // [Existing code to initialize PeiServices and Ppi]

  // Get SaSetup variable with dedicated size
  status = Ppi->GetVariable(Ppi, L"SaSetup", &gSaSetupGuid, NULL, &saSetupSize, CpuSetupData);
  if (status == EFI_BUFFER_TOO_SMALL) {
    // Handle oversized variable (truncate or error)
    saSetupSize = sizeof(CpuSetupData);
    status = Ppi->GetVariable(Ppi, L"SaSetup", &gSaSetupGuid, NULL, &saSetupSize, CpuSetupData);
  }
  if (EFI_ERROR(status)) {
    // Handle error (log, return, etc.)
    return status;
  }

  // Reset size for CpuSetup and read with dedicated size
  cpuSetupSize = sizeof(CpuSetupData);
  status = Ppi->GetVariable(Ppi, L"CpuSetup", &gCpuSetupGuid, NULL, &cpuSetupSize, CpuSetupData);
  if (status == EFI_BUFFER_TOO_SMALL) {
    // Handle oversized variable
    cpuSetupSize = sizeof(CpuSetupData);
    status = Ppi->GetVariable(Ppi, L"CpuSetup", &gCpuSetupGuid, NULL, &cpuSetupSize, CpuSetupData);
  }
  if (EFI_ERROR(status)) {
    // Handle error
    return status;
  }

  // [Existing code to process data]

  return 0;
}
