AcpiS3ResumeRecord->ResumeCount++;
AcpiS3ResumeRecord->AverageResume = DivU64x32 (S3ResumeTotal + AcpiS3ResumeRecord->FullResume, AcpiS3ResumeRecord->ResumeCount);
