#include "bmp280.h"
#include "legato.h"
#include "interfaces.h"

double temp;
double pressure;

COMPONENT_INIT {     
    LE_INFO("Logread Started");
    mangOH_ReadTemperatureSensor(&temp);
    mangOH_ReadPressureSensor(&pressure);
    LE_INFO("Current Temperature is: %f.", temp);
    LE_INFO("Current Pressure is: %f.", pressure);
}