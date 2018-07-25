//MargayDemo.ino
#include "Margay.h"
#include <BME.h>
#include <Maxbotix.h>

BME RH;
Maxbotix Range;

String Header = ""; //Information header
uint8_t I2CVals[1] = {0x77}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0);

void setup() {
	Header = Header + Range.GetHeader() + RH.GetHeader();
	Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
	Init();
}

void loop() {
	Init();
	Logger.Run(Update, UpdateRate);
}

String Update() 
{
	return Range.GetString() + RH.GetString();
}

void Init() 
{
	RH.begin();
	Range.begin(Logger.ExtInt); //Begin maxbotics on cs pin
}