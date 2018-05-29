#include "legato.h"
#include "interfaces.h"

#include "legato.h"
#include "interfaces.h"
#include "dataTransfer.h"

le_result_t packageMonitor_UploadSingleDataImmediate
(
    const char *sensorName,
    const char *data,
    double      timestamp
)
{
    (void)sensorName;
    (void)data;
    (void)timestamp;

    return LE_OK;
}

COMPONENT_INIT {     
  
}

