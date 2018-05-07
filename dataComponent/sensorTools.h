#ifndef SENSOR_TOOLS_H
#define SENSOR_TOOLS_H

#include "legato.h"

le_result_t ReadDoubleFromFile(const char *filePath, double *value);
le_result_t ReadIntFromFile(const char *filePath, int *value);
#endif //SENSOR_TOOLS_H
