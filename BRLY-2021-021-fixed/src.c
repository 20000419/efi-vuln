// Fixed GetPrimaryDisplay Function - Prevents Stack Overflow
EFI_STATUS __fastcall GetPrimaryDisplay(_BYTE *res)
{
    EFI_STATUS status;
    UINTN dataSize = 0;
    UINT8 *buffer = NULL;
    UINT8 primaryDisplayValue = 1; // Default value if variable not found
    
    // Validate input parameter
    if (res == NULL) {
        return EFI_INVALID_PARAMETER;
    }
    
    // First call to GetVariable() to determine required buffer size
    status = gRT->GetVariable(
        L"PrimaryDisplay",
        &EFI_GENERIC_VARIABLE_GUID,
        NULL,
        &dataSize,
        NULL
    );
    
    if (status == EFI_BUFFER_TOO_SMALL) {
        // Allocate appropriate buffer in heap
        status = gBS->AllocatePool(EfiBootServicesData, dataSize, (VOID**)&buffer);
        if (status != EFI_SUCCESS) {
            return EFI_OUT_OF_RESOURCES;
        }
        
        // Second call to GetVariable() to retrieve actual value
        status = gRT->GetVariable(
            L"PrimaryDisplay",
            &EFI_GENERIC_VARIABLE_GUID,
            NULL,
            &dataSize,
            buffer
        );
        
        if (status == EFI_SUCCESS && dataSize >= 1) {
            // Safely copy first byte of retrieved data
            primaryDisplayValue = buffer[0];
        }
        
        // Free allocated buffer
        gBS->FreePool(buffer);
    } else if (status == EFI_SUCCESS) {
        // Variable exists and is zero-length (should not happen)
        primaryDisplayValue = 1; // Default value
    }
    
    // Process validated primary display value
    if (status == EFI_SUCCESS || status == EFI_NOT_FOUND) {
        // Security check: validate value against known valid values
        if (primaryDisplayValue == 0) {
            *res = 0; // Internal Display
        } else if (primaryDisplayValue == 1) {
            *res = 1; // External Display
        } else if (primaryDisplayValue == 2) {
            *res = 2; // Both Displays
        } else {
            // Invalid value - set default
            *res = 1;
        }
        return EFI_SUCCESS;
    }
    
    return status;
}
