#include "sensorCode/bmp280.h"
#include "sensorCode/bmi160.h"
#include "legato.h"
#include "interfaces.h"
#include "configFileReader.h"
#include "logFileHandler.h"
//#include "le_timer.h"

//These are the variables that sensor data is stored in.
double temp;
double pressure;

double xaccel;
double yaccel;
double zaccel;

double xgyro;
double ygyro;
double zgyro;

const char logFilePath[] = "/var/log/package-monitor-logfile";
const char configFilePath[] = "/etc/package-monitor-configfile";

bool tempLogged;
bool pressureLogged;
bool accelerationLogged;
bool gyroLogged;

// Ian's Timer Code
#define SAMPLE_TIMER_PERIOD_MS (1000)

static le_timer_Ref_t sampleTimer;

static void sampleTimerCallback (le_timer_Ref_t timerRef) {

    FILE *lf = fopen(logFilePath, "a");
    LE_ASSERT(lf != NULL);

    // Not used
    (void)timerRef;
    if(1 /* waiting for ian's help to fix this problem tempLogged == 1 */) {
        mangOH_ReadTemperatureSensor(&temp);
        LE_INFO("Current Temperature is: %f.", temp);
        char tempString[32];
        sprintf(tempString, "%f", temp);
        logDataToFile("Temperature", tempString, lf);
    }

    if(1 /* waiting for ian's help to fix this problem pressureLogged == 1 */) {
        mangOH_ReadPressureSensor(&pressure);
        LE_INFO("Current Pressure is: %f.", pressure);
        char pressureString[32];
        sprintf(pressureString, "%f", pressure);
        logDataToFile("Pressure", pressureString, lf);
    }

    if (1 /* waiting for ian's help to fix this problem accelerationLogged == 1 */) {
        mangOH_ReadAccelerometer(&xaccel, &yaccel, &zaccel);
        LE_INFO("Current Acceleration X: %f Y: %f Z: %f.", xaccel, yaccel, zaccel);
        char xString[32];
        char yString[32];
        char zString[32];
        sprintf(xString, "%f", xaccel);
        sprintf(yString, "%f", yaccel);
        sprintf(zString, "%f", zaccel);
        logDataToFile("X Acceleration", xString, lf);
        logDataToFile("Y Acceleration", yString, lf);
        logDataToFile("Z Acceleration", zString, lf);
    }

    if(1 /* waiting for ian's help to fix this problem (gyroLogged == 1 */) {
        mangOH_ReadGyro(&xgyro, &ygyro, &zgyro);
        LE_INFO("Current Orientation X: %f Y: %f Z: %f.", xgyro, ygyro, zgyro);
        char xGyroString[32];
        char yGyroString[32];
        char zGyroString[32];
        sprintf(xGyroString, "%f", xgyro);
        sprintf(yGyroString, "%f", ygyro);
        sprintf(zGyroString, "%f", zgyro);
        logDataToFile("X Orientation", xGyroString, lf);
        logDataToFile("Y Orientation", yGyroString, lf);
        logDataToFile("Z Orientation", zGyroString, lf);   
    }

    fclose(lf);
}


COMPONENT_INIT {     
  
    struct configData config = readConfigOption(configFilePath);
    
    LE_INFO("Logging interval is set to: %i", config.dataInterval);

    tempLogged = config.isTempLogged;
    LE_INFO("Temperature logging is set to: %i", tempLogged);

    pressureLogged = config.isPressureLogged;
    LE_INFO("Pressure logging is set to: %i", pressureLogged);

    accelerationLogged = config.isAccelerationLogged;
    LE_INFO("Acceleration logging is set to: %i", accelerationLogged);

    gyroLogged = config.isGyroLogged;
    LE_INFO("Temperature logging is set to: %i", gyroLogged);

    //Test if the log file can be opened
    FILE *lf = fopen(logFilePath, "a");
    LE_ASSERT(lf != NULL);
    fclose(lf);
    sampleTimer = le_timer_Create("Sample Timer");       

    le_timer_SetMsInterval(sampleTimer, config.dataInterval);           
                
    le_timer_SetRepeat(sampleTimer, 0);                           

    le_timer_SetHandler(sampleTimer, sampleTimerCallback);        

    le_timer_Start(sampleTimer);      

}