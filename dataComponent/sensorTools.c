#include "legato.h"
#include "interfaces.h"

le_result_t readDoubleFromFile(const char *filePath, double *value) {
    le_result_t result = LE_OK;
    
    FILE *f = fopen(filePath, "r");
    if(f == NULL)
    { 
        LE_WARN("File '%s' could not be opened", filePath);
        result = LE_IO_ERROR;
    }
    
    int scannedNumber = fscanf(f, "%lf", value);
    if(scannedNumber != 1)
    {
        result = LE_FORMAT_ERROR;
    }
    
    fclose(f);
    return result;
}

le_result_t readIntFromFile(const char *filePath, int *value) {
    le_result_t r = LE_OK;
    FILE *f = fopen(filePath, "r");
    if (f == NULL)
    {
        LE_WARN("File '%s' could not be opened", filePath);
        r = LE_IO_ERROR;
    }

    int scannedNumber = fscanf(f, "%d", value);
    if (scannedNumber != 1)
    {
        r = LE_FORMAT_ERROR;
    }

    fclose(f);
    return r;
}
