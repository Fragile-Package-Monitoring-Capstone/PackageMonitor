#ifndef BMI_160_H
#define BMI_160_H

#include "legato.h"

LE_SHARED le_result_t mangOH_ReadAccelerometer(double *xAcc, double *yAcc, double *zAcc);
LE_SHARED le_result_t mangOH_ReadGyro(double *x, double *y, double *z);

#endif // BMI_160_H
