//MargayDemo.ino
#include "Margay.h"
#include <T9602.h>
#include <Maxbotix.h>

Margay Logger(Model_2v0);

T9602 RH;  //Initialize T9602 Humidity sensor
Maxbotix Range(Logger.D0); // Initialize Maxbotix rangefinder on D0 pin for digital interface

String Header = ""; //Information header
uint8_t I2CVals[1] = {0x28}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 

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
	Range.begin(); 
}
