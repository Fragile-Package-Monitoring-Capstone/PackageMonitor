#include "bmp280.h"
#include "legato.h"
#include "interfaces.h"
#include <stdlib.h>

double temp;
double pressure;
char tempstring[5];
char pressurestring[5];
COMPONENT_INIT {     
    mangOH_ReadTemperatureSensor(&temp);
    mangOH_ReadPressureSensor(&pressure);
    snprintf(tempstring, 5, "%f", temp);
    snprintf(pressurestring, 5, "%f", pressure);
    LE_INFO("Current Temperature is: %s.", tempstring);
    LE_INFO("Current Pressure is: %s.", pressurestring);
}