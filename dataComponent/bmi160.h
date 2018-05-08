#ifndef bmi160.h
#define bmi160.h

#include "legato.h"

LE_SHARED le_result_t mangOHReadAccelerometer(double *xAcc, double *yAcc, double *zAcc);
LE_SHARED le_result_t mangOHReadGyro(double *x, double *y, double *z);

#endif // bmi160.h
