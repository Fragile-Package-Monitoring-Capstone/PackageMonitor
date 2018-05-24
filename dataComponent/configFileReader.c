#include "configFileReader.h"
#include "legato.h"

#define numberOfConfigOptions (5)
#define fieldSeparator ": "
#define lineSeparator "\n"

int debugEnvVarSet = 0;

struct configData configOptions2 = {
    1000,  /*Data Interval: */
    false, /*Temp Logged Bool*/ 
    false, /*Pressure Logged Bool */
    false, /*Acceleration Logged Bool*/ 
    false, /*Gyro Logged Bool*/
};

int configOptions[numberOfConfigOptions] = {/*Data Interval: */ 0, /*Temp Logged Bool*/ 0, /*Pressure Logged Bool*/ 0, /*Acceleration Logged Bool*/ 0, /*Gyro Logged Bool*/ 0}; 


char nameOfConfigOptions[numberOfConfigOptions][21] = {"dataInterval", "isTempLogged", "isPressureLogged", "isAccelerationLogged", "isGyroLogged"};

#define configFilePath  ("configfile")

//Read the data from the config file
struct configData readConfigOption(const char *filePath) {
    FILE *configFile = fopen(filePath, "r");
    //check to make sure the file exists, and if not kill it with legato. 
    LE_ASSERT(configFile != NULL);

    char buffer[64];

    //These arrays are for the parts of the config options that don't need to be kept and stored
    char optionArray[8];
    char valueArray[7];
    //These variables are what we actually care about
    char optionName[21];
    int optionValue;

    for(size_t j = 0; j < numberOfConfigOptions; j++) {
        //iterate over the lines in the file
        fgets(buffer, sizeof(buffer), configFile);
        //printf("%s", buffer);
        sscanf(buffer, "%7s%21s %6s%d", optionArray, optionName, valueArray, &optionValue);
        for(int j = 0; j < numberOfConfigOptions; j++) {
            
            if(strcmp(optionName, nameOfConfigOptions[j]) == 0) {
                configOptions[j] = optionValue; /*
                char formatString[64] = "Config Option: ";
                strcat(formatString, nameOfConfigOptions[j]);
                char optionValueString[32];
                strcat(formatString, " is now set to: ");
                sprintf(optionValueString, "%i", configOptions[j]);
                strcat(formatString, optionValueString);
                LE_INFO("%s", formatString); */
            } else {
            
            }
            
        }
    } 

    fclose(configFile);
    // return a copy of the config object
    return configOptions2;
}    
/*This is maintained for testing purposes in the future, but the function and variables will be exposed in a header 
file. 
int main() { 
    if(getenv("DEBUG")) {
        printf("DEBUG envvar found\n");
        debugEnvVarSet = 1;
    }
    
    readConfigOption(configFilePath);
    if(debugEnvVarSet == 1) {
        char optionFromFile[35];
        for(size_t j = 0; j < numberOfConfigOptions; j++) {
            printf("%j", configOptions[j]);
            printf("\n");
        }     
    }
    
    return 0;
} */