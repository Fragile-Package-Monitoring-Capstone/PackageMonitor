#include "configFileReader.h"
#include "legato.h"
#define numberOfConfigOptions (5)

int debugEnvVarSet = 0;

int configOptions[numberOfConfigOptions] = {/*Data Interval: */ 0, /*Temp Logged Bool*/ 0, /*Pressure Logged Bool
*/ 0, /*Acceleration Logged Bool*/ 0, /*Gyro Logged Bool*/ 0}; 

char nameOfConfigOptions[numberOfConfigOptions][21] = {"dataInterval", "isTempLogged", "isPressureLogged", "isAccelerationLogged", "isGyroLogged"};

#define configFilePath  ("configfile")

//Read the data from the config file
void readConfigOption(const char *filePath) {
    FILE *f = fopen(filePath, "r+");
    if(f == NULL) {
        printf("Error, File could not be opened.\n");
        exit(1);
    }

    char buffer[64];
    /*
    if (debugEnvVarSet = 1) {
        printf("File opened successfully\n");
        while(fgets(buffer, sizeof(buffer), f)) {
            printf("%s", buffer);
        }        
    } */
    //These arrays are for the parts of the config options that don't need to be kept and stored
    char optionArray[8];
    char valueArray[7];
    //These variables are what we actually care about
    char optionName[21];
    int optionValue;

    for(size_t i = 0; i < numberOfConfigOptions; i++) {
        //iterate over the lines in the file
        fgets(buffer, sizeof(buffer), f);
        //printf("%s", buffer);
        sscanf(buffer, "%7s%21s %6s%d", optionArray, optionName, valueArray, &optionValue);
        for(int j = 0; j < numberOfConfigOptions; j++) {
            if(strcmp(optionName, nameOfConfigOptions[j]) == 0) {
                configOptions[j] = optionValue;
            
            } else {
            
            }
            
        }
    }
    
    fclose(f);
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
        for(size_t i = 0; i < numberOfConfigOptions; i++) {
            printf("%i", configOptions[i]);
            printf("\n");
        }     
    }
    
    return 0;
}*/