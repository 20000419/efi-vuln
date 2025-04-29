//Bootguard defines several ways of protecting the UEFI modules and verifying their integrity/authenticity during the boot process, such as Initial Boot Block (IBB) segments and Vendor Hash File protected ranges. The products by Lenovo mentioned above do not properly include several FFS volumes with SMM/DXE executables into those ranges.As an example, Lenovo V310-14ISK only defines 3 IBB segments (Address: FFE10000h Size: 00020000h, Address: FFEE0000h Size: 00100000h, Address: FFFE0000h Size: 00020000h), which cover 3 FFS volumes, leaving other FFS volumes with executable files unprotected from malicious tampering. UEFITool output:

BootGuard ACM found at base 6D8318h
...
------------------------------------------------------------------------

Intel BootGuard Key manifest found at base 6D5318h
...
------------------------------------------------------------------------

...

IBB Segments:
Flags: 0000h Address: FFE10000h Size: 00020000h
Flags: 0000h Address: FFEE0000h Size: 00100000h
Flags: 0000h Address: FFFE0000h Size: 00020000h

//Details of protected and unprotected FFS volumes and executable files from UEFITool:

  Type  |      Subtype  |   Base   |   Size   |   Name 
 ...
 Image      | UEFI          | 00000050 | 0088DD00 | - UEFI image
 ...                                                         Unprotected FFS volume ↓
 Volume     | FFSv2         |   N/A    | 00058000 | -------- B92CF322-8AFA-4AA4-B946-005DF1D69778 
 ...                                                          Unprotected modules below↓
 File       | SMM module    |   N/A    | 00002D02 | ---------CDC11AE9-01E7-42CB-88EB-FDFFD8819893
       | TcgLegacy
 Section    | MM dependency |   N/A    | 0000005E | ---------- MM dependency section
 Section    | PE32 image    |   N/A    | 00002C64 | ---------- PE32 image section
 Section    | UI            |   N/A    | 00000018 | ---------- UI section
 Section    | Version       |   N/A    | 0000000E | ---------- Version section
 ...
 Free space |               |   N/A    | 00000620 | --------- Volume free space
 Free space |               | 000F86D0 | 000C7C48 | ----- Volume free space
 Volume     | FFSv2         | 001C0318 | 00450000 | ---- EfiFirmwareFileSystem2Guid
 File       | Volume image  | 001C0360 | 001FDEC4 | ----- 9E21FD93-9C72-4C15-8C4B-E77F1DB2D792
 Section    | GUID defined  | 001C0378 | 001FDEAC | ------ LzmaCustomDecompressGuid
 Section    | Raw           |   N/A    | 0000000C | ------- Raw section
 Section    | Volume image  |   N/A    | 00834004 | ------- Volume image section
 ...                                                         Unprotected FFS volume ↓
 Volume     | FFSv2         |   N/A    | 00834000 | -------- A881D567-6CB0-4EEE-8435-2E72D33E45B5
 ...                                                          Unprotected modules below↓
 File       | Freeform      |   N/A    | 0000005C | --------- AprioriDxe | DXE apriori file
 Section    | Raw           |   N/A    | 00000044 | ---------- Raw section
 ...
 File       | Freeform      | 003BE228 | 00002DFF | ----- DAB78572-E8D1-4C3F-9A1E-F27E9CAF686D
 Section    | Raw           | 003BE240 | 00002DE7 | ------ Raw section
 Free space |               | 003C1028 | 0024F2F0 | ----- Volume free space
 ...                                                     Protected FFS volume ↓
 Volume     | FFSv2         | 00610318 | 00020000 | ---- 8579D1CA-45E8-4F1C-A789-FFA770672099
 File       | PEI module    | 00610390 | 000044A4 | ----- PlatformInit | PlatformInit
 Section    | PEI dependency| 006103A8 | 00000028 | ------ PEI dependency section
 Section    | GUID defined  | 006103D0 | 00004464 | ------ LzmaCustomDecompressGuid
 Section    | PE32 image    |   N/A    | 00015CA4 | ------- PE32 image section
 Section    | UI            |   N/A    | 0000001E | ------- UI section
 Section    | Version       |   N/A    | 0000000E | ------- Version section
 ...
 Free space |               | 0062D6C0 | 00002C58 | ----- Volume free space
 ...                                                     Protected FFS volume ↓
 Volume     | FFSv2         | 006E0318 | 00100000 | ---- B73FE497-B92E-416E-8326-45AD0D270091
 ...
 Free space |               | 007B16F8 | 0002EC20 | ----- Volume free space
 ...                                                     Protected FFS volume ↓
 Volume     | FFSv2         | 007E0318 | 00020000 | ---- BA34AA5B-110E-4B10-B729-E559EFD075D3
 File       | Pad           | 007E0390 | 00000070 | ----- Pad-file
 File       | PEI core      | 007E0400 | 000054DA | ----- PeiCore | PeiCore
 Section    | Raw           | 007E0418 | 0000001C | ------ Raw section
 Section    | PE32 image    | 007E0434 | 00005484 | ------ PE32 image section
 Section    | UI            | 007E58B8 | 00000014 | ------ UI section
 Section    | Version       | 007E58CC | 0000000E | ------ Version section
