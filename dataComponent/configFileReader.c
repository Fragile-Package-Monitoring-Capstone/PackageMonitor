#include "configFileReader.h"
#include <stdbool.h>
#include "legato.h"

int dataInterval;
bool temperatureLogged;
bool pressureLogged;
bool accelerationLogged;
bool gyroscopeLogged;


//Read the data from the    
void readConfigOption(char* filePath[]) {
    FILE *f = fopen(filePath, "%r+");
}