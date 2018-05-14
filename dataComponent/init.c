#include "sensorCode/bmp280.h"
#include "sensorCode/bmi160.h"
#include "legato.h"
#include "interfaces.h"
//#include "configFileReader.h"

double temp;
double pressure;
double xaccel;
double yaccel;
double zaccel;
double xgyro;
double ygyro;
double zgyro;

char configFilePath[] = "";

COMPONENT_INIT {     

    //readConfigOption(*configFilePath);
    
    while(true){    
        mangOH_ReadTemperatureSensor(&temp);
        mangOH_ReadPressureSensor(&pressure);
        mangOH_ReadAccelerometer(&xaccel, &yaccel, &zaccel);
        mangOH_ReadGyro(&xgyro, &ygyro, &zgyro);
        LE_INFO("Current Temperature is: %f.", temp);
        LE_INFO("Current Pressure is: %f.", pressure);
        LE_INFO("Current Acceleration X: %f Y: %f Z: %f.", xaccel, yaccel, zaccel);
        LE_INFO("Current Orientation X: %f Y: %f Z: %f.", xgyro, ygyro, zgyro);
        sleep(1);
    }
}