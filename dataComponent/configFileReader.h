#ifndef CONFIG_FILE_READER_H
#define CONFIG_FILE_READER_H

#include "legato.h"


static int dataInterval;
static int isTempLogged;
static int isPressureLogged;
static int isGyroLogged;
static int isAccelerationLogged;

LE_SHARED le_result_t readConfigOption(const char *filePath);

#endif //CONFIG_FILE_READER_H
