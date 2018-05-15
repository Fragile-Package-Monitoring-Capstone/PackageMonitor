#include "legato.h"
#include "interfaces.h"


le_result_t logDataToFile(char sensorName[], char sensorValue[], const char *filePath) {   
    FILE *f = fopen(filePath, "a");
    if(f == NULL) {
        LE_INFO("Error, File could not be opened.");
        exit(1);
    }
    time_t unixTime = time(NULL);
    struct tm *currentTime = gmtime(&unixTime);

    //My painful way to format the log message with judicrous use of strcat. 
    //If anyone finds a better version please let me know
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%FT", currentTime);
    strcat(buffer, " - ");
    strcat(buffer, sensorName);
    strcat(buffer, ": ");
    strcat(buffer, sensorValue);
    
    fprintf(f, "%s", buffer);
    return LE_OK;
    fclose(f);
}