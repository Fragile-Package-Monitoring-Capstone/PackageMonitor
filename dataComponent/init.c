#include "sensorCode/bmp280.h"
#include "sensorCode/bmi160.h"
#include "legato.h"
#include "interfaces.h"
#include "configFileReader.h"
#include "logFileHandler.h"
#include "le_timer.h"

//These are the variables that sensor data is stored in.
double temp;
double pressure;

double xaccel;
double yaccel;
double zaccel;

double xgyro;
double ygyro;
double zgyro;

const char logFilePath[] = "/legato/systems/current/apps/Package_Monitor_mangOH/writeable/var/log/package-monitor-logfile";
const char configFilePath[] = "/legato/systems/current/apps/Package_Monitor_mangOH/read-only/etc/package-monitor-configfile";

COMPONENT_INIT {     
    
  /*  le_timer_Ref_t logTimer = le_timer_Create();

    le_timer_SetInterval(logTimer, dataInterval);
*/
    readConfigOption(configFilePath);
    
    while(true){    
        if(isTempLogged) {
            mangOH_ReadTemperatureSensor(&temp);
            LE_INFO("Current Temperature is: %f.", temp);
            char tempString[32];
            sprintf(tempString, "%f", temp);
            LE_DEBUG(tempString);
            logDataToFile("Temperature", tempString, logFilePath);
        }
        
        if(isPressureLogged) {
            mangOH_ReadPressureSensor(&pressure);
            LE_INFO("Current Pressure is: %f.", pressure);
            char pressureString[32];
            sprintf(pressureString, "%f", pressure);
            logDataToFile("Pressure", pressureString, logFilePath);
        }
        
        if(isAccelerationLogged) {
            mangOH_ReadAccelerometer(&xaccel, &yaccel, &zaccel);
            LE_INFO("Current Acceleration X: %f Y: %f Z: %f.", xaccel, yaccel, zaccel);
            char xString[32];
            char yString[32];
            char zString[32];
            sprintf(xString, "%f", xaccel);
            sprintf(yString, "%f", yaccel);
            sprintf(zString, "%f", zaccel);
            logDataToFile("X Acceleration", xString, logFilePath);
            logDataToFile("Y Acceleration", yString, logFilePath);
            logDataToFile("Z Acceleration", zString, logFilePath);
        }
        
        if(isGyroLogged) {
            mangOH_ReadGyro(&xgyro, &ygyro, &zgyro);
            LE_INFO("Current Orientation X: %f Y: %f Z: %f.", xgyro, ygyro, zgyro);
            char xGyroString[32];
            char yGyroString[32];
            char zGyroString[32];
            sprintf(xGyroString, "%f", xgyro);
            sprintf(yGyroString, "%f", ygyro);
            sprintf(zGyroString, "%f", zgyro);
            logDataToFile("X Orientation", xGyroString, logFilePath);
            logDataToFile("Y Orientation", yGyroString, logFilePath);
            logDataToFile("Z Orientation", zGyroString, logFilePath);
        }
        
        sleep(dataInterval);
    }
}