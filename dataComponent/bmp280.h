#ifndef BMP_280_H
#define BMP_280_H

#include "legato.h"

LE_SHARED le_result_t mangOH_ReadPressureSensor(double *reading);
LE_SHARED le_result_t mangOH_ReadTemperatureSensor(double *reading);
#endif // BMP_280_H