EFI_STATUS __fastcall sub_44F4(__int64 a1, char **LogoData, _QWORD *LogoDataSize)
{
...
  v11 = gRT->GetVariable("LBLDESPFN", &VendorGuid, 0i64, &DataSize, Data);
  v14 = "EFI\\lenovo\\logo\\"
  ImagePathSize = 2 * (strlen(v14) + strlen(Data+4)) + 4;
  ImagePath = Alloc(ImagePathSize);

  if ( ImagePath )
  {
    snprintf(ImagePath, v16, "%s%s", "EFI\\lenovo\\logo\\", Data + 4);
    ReadsLogo(ImagePath, &v21, &v22); // sub_419C
    v20 = ChecksCRC32(v21); // sub_43E8
    if ( v20 >= 0 )
    {
      *LogoDataSize = v22;
      *LogoData = v21;
      *(a1 + 16) = *Data; // Setting the logo format (0=BMP, 1=JPEG..)
    }
    return v20;
  }
  
 EFI_STATUS sub_1A689C(
  unsigned int *LogoImage, unsigned __int64 LogoImageSize,
  char* DecodedLogoImage, unsigned int *DecodedLogoImageSize,
  int *LogoWidth, int *LogoHeight
  )
