//MargayDemo.ino
#include "Margay.h"
#include <BME.h>

BME RH; //Initialzie BME280

String Header = ""; //Information header
uint8_t I2CVals[1] = {0x77}; 
// int Count = 0;
unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0);

void setup() {
	Header = Header + RH.GetHeader();
	Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
	Init();
}

void loop() {
	Logger.Run(Update, UpdateRate);
}

String Update() 
{
	Init();
	return RH.GetString();
}

void Init() 
{
	RH.begin(0x77);
}
