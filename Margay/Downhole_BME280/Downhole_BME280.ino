//MargayDemo.ino
#include "Margay.h"
#include <TP_Downhole.h>
#include <BME.h>

// #define MARGAY_1v0
TP_Downhole DH; //Initalize TP-Downhole sensor
BME RH; //Initialzie BME280

String Header = ""; //Information header
uint8_t I2CVals[3] = {0x6A, 0x77, 0x76}; 
// int Count = 0;
unsigned long UpdateRate = 5; //Number of seconds between readings 

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
	DH.begin(TP2A2);
	RH.begin();
	return DH.GetString() + RH.GetString();
}

void Init() 
{
	DH.begin(TP2A2);
	RH.begin();
}
