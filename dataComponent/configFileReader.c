#include "configFileReader.h"
#include <stdio.h>
#include <stdlib.h>

#define numberOfConfigOptions (5)

int debugEnvVarSet = 0;

static int dataInterval;
/*
boolean values are stored as int because stdbool does this and there's no point in 
including stdbool when it just stores true and false as 0 and 1 anyways. 
*/
static int isTempLogged;
static int isPressureLogged;
static int isGyroLogged;
static int isAccelerationLogged;
int *configOptions[numberOfConfigOptions] = {&dataInterval, &isTempLogged, &isPressureLogged ,&isAccelerationLogged, &isGyroLogged}; 

//These are used to determine what the config options are in the file
char optionDataInterval[] = "dataInterval";
char optionIsTempLogged[] = "isTempLogged";
char optionIsPressureLogged[] = "isPressureLogged";
char optionIsGyroLogged[] = "isGyroLogged";
char optionIsAccelerationLogged[] = "isAccelerationLogged";
char *nameOfConfigOptions[numberOfConfigOptions] = {optionDataInterval, optionIsTempLogged, optionIsPressureLogged, optionIsAccelerationLogged, optionIsGyroLogged};

#define configFilePath  ("configfile")

//Read the data from the config file
void readConfigOption(const char *filePath) {
    FILE *f = fopen(filePath, "r+");
    if(f == NULL) {
        printf("Error, File could not be opened.\n");
        exit(1);
    }

    char buffer[22];

    if (debugEnvVarSet = 1) {
        printf("File opened successfully\n");
        while(fgets(buffer, sizeof(buffer), f)) {
            printf("%s", buffer);
        }        
    }

    
    for(size_t i = 0; i < numberOfConfigOptions; i++) {
        fgets(buffer, sizeof(buffer), f);
        if(buffer == nameOfConfigOptions[i]) {
            
        }
        
        
        
    }
    
    fclose(f);
}

int main() {
    if(getenv("DEBUG")) {
        printf("DEBUG envvar found\n");
        debugEnvVarSet = 1;
    }
    
    readConfigOption(configFilePath);
    
    /*for(int i = 0; i < numberOfConfigOptions; i++) {
        printf("%d ", *configOptions[i]);
        printf("\n");
    } */
    
    return 0;
}