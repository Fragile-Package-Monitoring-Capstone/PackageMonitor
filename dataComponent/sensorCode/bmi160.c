#include "legato.h"
#include "interfaces.h"

#include "bmi160.h"
#include "sensorTools.h"

static const char FormatStr[] = "/sys/devices/i2c-0/0-0068/iio:device0/in_%s_%s";
static const char AccType[]   = "accel";
static const char GyroType[]  = "anglvel";
static const char CompX[]     = "x_raw";
static const char CompY[]     = "y_raw";
static const char CompZ[]     = "z_raw";
static const char CompScale[] = "scale";


le_result_t mangOH_ReadAccelerometer (double *xAcc, double *yAcc, double *zAcc) {
    le_result_t r;
    char path[256];

    double scaling = 0.0;
    int pathLen = snprintf(path, sizeof(path), FormatStr, AccType, CompScale);
    LE_ASSERT(pathLen < sizeof(path));
    r = readDoubleFromFile(path, &scaling);
    if (r != LE_OK)
    {
        goto done;
    }

    pathLen = snprintf(path, sizeof(path), FormatStr, AccType, CompX);
    LE_ASSERT(pathLen < sizeof(path));
    r = readDoubleFromFile(path, xAcc);
    if (r != LE_OK)
    {
        goto done;
    }
    *xAcc *= scaling;

    pathLen = snprintf(path, sizeof(path), FormatStr, AccType, CompY);
    LE_ASSERT(pathLen < sizeof(path));
    r = readDoubleFromFile(path, yAcc);
    if (r != LE_OK)
    {
        goto done;
    }
    *yAcc *= scaling;

    pathLen = snprintf(path, sizeof(path), FormatStr, AccType, CompZ);
    LE_ASSERT(pathLen < sizeof(path));
    r = readDoubleFromFile(path, zAcc);
    *zAcc *= scaling;

done:
    return r;
}


le_result_t mangOH_ReadGyro (double *x, double *y, double *z) {
    le_result_t r;
    char path[256];

    double scaling = 0.0;
    int pathLen = snprintf(path, sizeof(path), FormatStr, GyroType, CompScale);
    LE_ASSERT(pathLen < sizeof(path));
    r = readDoubleFromFile(path, &scaling);
    if (r != LE_OK)
    {
        goto done;
    }

    pathLen = snprintf(path, sizeof(path), FormatStr, GyroType, CompX);
    LE_ASSERT(pathLen < sizeof(path));
    r = readDoubleFromFile(path, x);
    if (r != LE_OK)
    {
        goto done;
    }
    *x *= scaling;

    pathLen = snprintf(path, sizeof(path), FormatStr, GyroType, CompY);
    LE_ASSERT(pathLen < sizeof(path));
    r = readDoubleFromFile(path, y);
    if (r != LE_OK)
    {
        goto done;
    }
    *y *= scaling;

    pathLen = snprintf(path, sizeof(path), FormatStr, GyroType, CompZ);
    LE_ASSERT(pathLen < sizeof(path));
    r = readDoubleFromFile(path, z);
    *z *= scaling;

done:
    return r;
}
