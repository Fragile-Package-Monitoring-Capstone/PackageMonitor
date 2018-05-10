#include "configFileReader.h"
#include "legato.h"

const int numberOfConfigOptions = 6;
char configoptions[numberOfConfigOptions];
int dataInterval;

//Read the data from the config file
void readConfigOption(char* filePath[]) {
    FILE *f = fopen(filePath, "r+");
}