#include "legato.h"
#include "interfaces.h"

#define logFilePath ("logfile")

void logDataToFile(char sensorName[], char sensorValue[], const char *filePath[]) {   
    FILE *f = fopen(filePath, "a");
    if(f == NULL) {
        printf("Error, File could not be opened.\n");
        exit(1);
    }
    
}