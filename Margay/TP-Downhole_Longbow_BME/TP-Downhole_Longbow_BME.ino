//MargayDemo.ino
#include "Margay.h"
#include <TP_Downhole_Longbow.h>
#include <BME.h>

TP_Downhole_Longbow DH; //Initalize TP-Downhole sensor
BME RH;  //Initialize BME280

String Header = ""; //Information header
uint8_t I2CVals[2] = {0x22, 0x77}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0);

void setup() {
	Header = Header + DH.GetHeader() + RH.GetHeader();
	Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
	Init();
}

void loop() {
	Logger.Run(Update, UpdateRate);
}

String Update() 
{
	Init();
	return DH.GetString() + RH.GetString();
}

void Init() 
{
	DH.begin(13, 0x22); //Initialize TP-Downhole Longbow (at address = 13) and Longbow Widget (at address = 0x22)
	RH.begin(0x77);
}
