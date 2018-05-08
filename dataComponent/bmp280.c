#include "legato.h"
#include "interfaces.h"
#include "sensorTools.h"

static const char PressureFile[] = "/sys/devices/i2c-4/4-0076/iio:device1/in_pressure_input";
static const char TemperatureFile[] = "/sys/devices/i2c-4/4-0076/iio:device1/in_temp_input";

le_result_t mangOH_ReadPressureSensor(double *reading) {
    return readDoubleFromFile(PressureFile, reading);
}

le_result_t mangOH_ReadTemperatureSensor(double *reading) {
    int temperature; 
    le_result_t result = readIntFromFile(TemperatureFile, &temperature);

    if (result != LE_OK) {
        return result;
    }

    //Divide temperature by 1000 to get the correct reading
    *reading = ((double)temperature) / 1000.0;
    return LE_OK;
}