//MargayDemo.ino
#include "Margay.h"
#include <BME.h>
#include <Maxbotix.h>

Margay Logger(Model_2v0);

BME RH;
Maxbotix Range(Logger.D0);

String Header = ""; //Information header
uint8_t I2CVals[1] = {0x77}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 


void setup() {
	Header = Header + Range.GetHeader() + RH.GetHeader();
	Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
	Init();
  digitalWrite(17, LOW); //Turn off internal I2C pullups
  digitalWrite(16, LOW);
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
	Range.begin(); //Begin maxbotics on cs pin
}
