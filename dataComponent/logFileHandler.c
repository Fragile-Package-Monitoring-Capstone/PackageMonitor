#include "legato.h"
#include "interfaces.h"

//either integrate code into logDataToFile or create new function to recycle/create new logfiles

#define logDirectoryPath "/var/log/"
#define logFileBaseName "package-monitor-logfile_"

//le_msg_SessionRef_t *SessionRef;

unsigned int logFileCounter = 2;
char buffer[256];
le_result_t logDataToFile(char sensorName[], char sensorValue[], FILE *logFile) {   
    LE_ASSERT(logFile != NULL)

    time_t unixTime = time(NULL);
    struct tm *currentTime = gmtime(&unixTime);

    //My painful way to format the log message with judicrous use of strcat. 
    //If anyone finds a better way to do this please let me know
    char logbuffer[128];
    strftime(logbuffer, sizeof(logbuffer), "%F %T", currentTime);
    strcat(logbuffer, " - ");
    strcat(logbuffer, sensorName);
    strcat(logbuffer, ": ");
    strcat(logbuffer, sensorValue);
    strcat(logbuffer, "\n");

    fprintf(logFile, "%s", logbuffer);
    return LE_OK;
}

char *createFirstLogFile() {
    //returns the path of the first log file. 
    LE_INFO("Creating First Log File");
        
    time_t unixTime = time(NULL);
    struct tm *currentTime = gmtime(&unixTime);
    char timeString[21];
    strftime(timeString, sizeof(timeString), "%F-%T", currentTime);

    strcat(buffer, logDirectoryPath);
    strcat(buffer, logFileBaseName);
    strcat(buffer, "1_");
    strcat(buffer, timeString);
    LE_INFO("First Log File Path set to: %s", buffer);
    FILE *f = fopen(buffer, "w");
    if(!f) {
        LE_ERROR("Failed to open file %s, error %d", buffer, errno);
    }
    fclose(f);
    return buffer;

}

char *recycleLogFile() {
    char logFileNumber[9];  
    LE_INFO("Recycling Log File");

    time_t unixTime = time(NULL);
    struct tm *currentTime = gmtime(&unixTime);
    char timeString[21];
    strftime(timeString, sizeof(timeString), "%F-%T", currentTime);
    sprintf(logFileNumber, "%i", logFileCounter);

    strcat(buffer, logDirectoryPath);
    strcat(buffer, logFileBaseName);
    strcat(buffer, logFileNumber);
    strcat(buffer, "_");
    
    strcat(buffer, timeString);
    strcat(buffer, "");
    LE_INFO("New Log File path set to: %s", buffer);

    logFileCounter++;

    FILE *f = fopen(buffer, "w");
    if(!f) {
        LE_ERROR("Failed to open file %s, error %d", buffer, errno);
    }
    
    fclose(f);
    return buffer;
}
