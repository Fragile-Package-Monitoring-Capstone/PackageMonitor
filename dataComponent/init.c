#include "sensorCode/bmp280.h"
#include "sensorCode/bmi160.h"
#include "legato.h"
#include "interfaces.h"
#include "configFileReader.h"
#include "logFileHandler.h"
//#include "dataTransfer.h"
//These are the variables that sensor data is stored in.
double temp;
double pressure;

double xaccel;
double yaccel;
double zaccel;

double xgyro;
double ygyro;
double zgyro;

//logfilepath is determined by createFirstLogFile()
char *logFilePath = "";
const char configFilePath[] = "/etc/package-monitor-configfile";

bool tempLogged;
bool pressureLogged;
bool accelerationLogged;
bool gyroLogged;

//Used to check when the file needs to be recycled.
int logCycleCounter;


// Ian's Timer Code
#define SAMPLE_TIMER_PERIOD_MS (1000)

static le_timer_Ref_t sampleTimer;

/*Ian's sample timer code for sending to airvantage
comments in this code are broken, replace the 
*
*    (void)timerRef;
*    if(1  waiting for ian's help to fix this problem tempLogged == 1 ) {
*        mangOH_ReadTemperatureSensor(&temp);
*        LE_INFO("Current Temperature is: %f.", temp);
*        char tempString[32];
*        sprintf(tempString, "%f", temp);
*        logDataToFile("Temperature", tempString, lf);
<<<<<<< HEAD
*        Add logic to only send when temperature has changed AND is outside
*         of the allowed range
=======
*         Add logic to only send when temperature has changed AND is outside
*          of the allowed range
>>>>>>> 96672be73f9f6035c4a2de33270634ebf08d8fed
*         
*        if ( 1  temperature limit exceded? )
*        {
*            if (LE_OK != packageMonitor_UploadSingleDataImmediate(tempSensName, tempString, 0 get timestamp ))
*            {
*                LE_ERROR("Failed to send data for %s", tempSensName);
*            }
*        }
*    }
*/


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

    if(1 /* waiting for ian's help to fix this problem gyroLogged == 1 */) {
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

    logCycleCounter++;

    //There are 278 possible log entries into a file before it reaches maximum size
    //each time the function is called 368 bytes of data is logged(as of git commit fa81c7a)
    if(logCycleCounter >= 5) {
        logFilePath = "";
        logFilePath = recycleLogFile();
    }
    

    fclose(lf);
}


COMPONENT_INIT {     
    fopen("/logfiles/testing_file", "w");
    logFilePath = createFirstLogFile();
    LE_INFO("Log File Path is now: %s", logFilePath);
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

    //Create Log File
    FILE *lf = fopen(logFilePath, "w");
    LE_ASSERT(lf != NULL);
    fclose(lf);
    sampleTimer = le_timer_Create("Sample Timer");       

    le_timer_SetMsInterval(sampleTimer, config.dataInterval);           
                
    le_timer_SetRepeat(sampleTimer, 0);                           

    le_timer_SetHandler(sampleTimer, sampleTimerCallback);        

    le_timer_Start(sampleTimer);      

}
