int sub_FFEBFB2C()
{
  // [COLLAPSED LOCAL DECLARATIONS. PRESS KEYPAD CTRL-"+" TO EXPAND]

  DataSize = 4;
  S3PerformanceTablePointer = 0;
  Status = sub_FFEC0607(&EFI_PEI_READ_ONLY_VARIABLE2_PPI_GUID, &This);
  if ( Status >= 0 )
  {
    Status = This->GetVariable(
               This,
               L"FPDT_Variable_NV",
               &AMI_GLOBAL_VARIABLE_GUID,
               0,
               &DataSize,
               &S3PerformanceTablePointer);
    if ( Status >= 0 )
    {
      Status = S3PerformanceTablePointer;
      // Extracted from memory pointed by FPDT_Variable_NV variable value
      AcpiS3PerformanceTable = S3PerformanceTablePointer->AcpiS3PerformanceTable;
      if ( *S3PerformanceTablePointer->AcpiS3PerformanceTable == 'TP3S' )
      {
        if ( *&S3PerformanceTablePointer->ResumeCount )
        {
          if ( !AcpiS3PerformanceTable->S3Resume.Header.Type )
          {
            S3ResumeTotal = MultU64x32(__rdtsc(), *&S3PerformanceTablePointer->ResumeCount);
            LODWORD(v3) = S3ResumeTotal;
            HIDWORD(v3) = HIDWORD(S3ResumeTotal) % 0xF4240;
            FullResumeLo = v3 / 0xF4240;
            FullResumeHi = HIDWORD(S3ResumeTotal) / 0xF4240;
            v6 = __PAIR64__(HIDWORD(S3ResumeTotal) / 0xF4240, FullResumeLo)
               + AcpiS3PerformanceTable->S3Resume.AverageResume * AcpiS3PerformanceTable->S3Resume.ResumeCount;
            ResumeCount = AcpiS3PerformanceTable->S3Resume.ResumeCount + 1;
            LODWORD(v3) = v6;
            HIDWORD(v3) = HIDWORD(v6) % ResumeCount;
            Status = v3 / ResumeCount;
            AcpiS3PerformanceTable->S3Resume.ResumeCount = ResumeCount;
            LODWORD(AcpiS3PerformanceTable->S3Resume.AverageResume) = Status;
            HIDWORD(AcpiS3PerformanceTable->S3Resume.AverageResume) = HIDWORD(v6) / ResumeCount;
            LODWORD(AcpiS3PerformanceTable->S3Resume.FullResume) = FullResumeLo;
            HIDWORD(AcpiS3PerformanceTable->S3Resume.FullResume) = FullResumeHi;
          }
        }
      }
    }
  }
  return Status;
}


AcpiS3PerformanceTable->S3Resume.ResumeCount = ResumeCount;
LODWORD(AcpiS3PerformanceTable->S3Resume.AverageResume) = Status;
HIDWORD(AcpiS3PerformanceTable->S3Resume.AverageResume) = HIDWORD(v6) / ResumeCount;
LODWORD(AcpiS3PerformanceTable->S3Resume.FullResume) = FullResumeLo;
HIDWORD(AcpiS3PerformanceTable->S3Resume.FullResume) = FullResumeHi;
