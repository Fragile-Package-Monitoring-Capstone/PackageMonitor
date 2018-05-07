#include "legato.h"
#include "interfaces.h"
#include "bmp280.h"

COMPONENT_INIT {     
    double temp;
    double pressure;
    LE_INFO("Current Temperature is: %s.", mangOH_ReadTemperatureSensor(*temp));
    LE_INFO("Current Pressure is: %s.", mangOH_ReadPressureSensor(*pressure));
}