#include "legato.h"
#include "interfaces.h"


le_result_t logDataToFile(char sensorName[], char sensorValue[], FILE *logFile) {   
    LE_ASSERT(logFile != NULL)
    LE_INFO("Logging data...");
    time_t unixTime = time(NULL);
    struct tm *currentTime = gmtime(&unixTime);

    //My painful way to format the log message with judicrous use of strcat. 
    //If anyone finds a better way to do this please let me know
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%FT", currentTime);
    strcat(buffer, " - ");
    strcat(buffer, sensorName);
    strcat(buffer, ": ");
    strcat(buffer, sensorValue);
    
    fprintf(logFile, "%s", buffer);
    return LE_OK;
}