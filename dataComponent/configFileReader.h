#ifndef CONFIG_FILE_READER_H
#define CONFIG_FILE_READER_H

#include "legato.h"

struct configData readConfigOption(const char *filePath);
struct configData {
    int dataInterval;
    bool isTempLogged;
    bool isPressureLogged;
    bool isAccelerationLogged;
    bool isGyroLogged;
};

#endif //CONFIG_FILE_READER_H
