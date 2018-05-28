#include "legato.h"
#include "interfaces.h"
#include <sys/stat.h>

//either integrate code into logDataToFile or create new function to recycle/create new logfiles

#define logDirectoryPath "/var/log/"
le_result_t logDataToFile(char sensorName[], char sensorValue[], FILE *logFile) {   
    LE_ASSERT(logFile != NULL)

    time_t unixTime = time(NULL);
    struct tm *currentTime = gmtime(&unixTime);

    //My painful way to format the log message with judicrous use of strcat. 
    //If anyone finds a better way to do this please let me know
    char buffer[128];
    strftime(buffer, sizeof(buffer), "%F %T", currentTime);
    strcat(buffer, " - ");
    strcat(buffer, sensorName);
    strcat(buffer, ": ");
    strcat(buffer, sensorValue);
    strcat(buffer, "\n");

    fprintf(logFile, "%s", buffer);
    return LE_OK;
}

char[] createLogFile() {
    //returns the path of the first log file. 
}

char[] recycleLogFile(FILE *logFile) {
    //each time the function is called 368 bytes of data is logged
    LE_INFO("Recycling Log File")
    time_t unixTime = time(NULL);
    struct tm *currentTime = gmtime(&unixTime);

}
