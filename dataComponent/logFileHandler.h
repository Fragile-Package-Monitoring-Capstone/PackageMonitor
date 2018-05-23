#ifndef LOG_FILE_HANDLER_H
#define LOG_FILE_HANDLER_H

#include "legato.h"

LE_SHARED le_result_t logDataToFile(char sensorName[], char sensorValue[], const char *filePath);

#endif //LOG_FILE_HANDLER_H
