#ifndef DATA_TRANSFER_H
#define DATA_TRANSFER_H

#include "legato.h"


LE_SHARED le_result_t packageMonitor_UploadSingleDataImmediate
(
    const char *sensorName,  // Sensor name
    const char *data,        // String value from sensor
    double      timestamp    // Timestamp (seconds)
);

#endif // DATA_TRANSFER_H
