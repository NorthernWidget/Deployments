//MargayDemo.ino
#include "Margay.h"
#include <BME.h>

BME RH;

String Header = "Rain [in]"; //Information header
uint8_t I2CVals[1] = {0x77}; 
// int Count = 0;
unsigned long UpdateRate = 5; //Number of seconds between readings 

Margay Logger(Model_1v0);

volatile unsigned int Count = 0; //Global counter for tipping bucket 
unsigned long Holdoff = 25; //10ms between bucket tips minimum

void setup() {
	Header = Header + RH.GetHeader();
	Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
	Init();
}

void loop() {
	RH.begin();
  Logger.Run(Update, UpdateRate);
}

String Update() 
{
	float Val1 = Count*0.01;  //Account for volume per tip
	Count = 0; //Clear count with each update 
	return String(Val1) + RH.GetString();
}

void Init() 
{
	RH.begin();
	attachInterrupt(digitalPinToInterrupt(Logger.ExtInt), Tip, FALLING);
	pinMode(Logger.ExtInt, INPUT_PULLUP);
}

void Tip()
{
	static unsigned long TimeLocal = millis() % 1000; //Protect the system from rollover errors
	if((millis() % 1000) - TimeLocal > Holdoff) {
		Count++; //Increment global counter 
	}
	//Else do nothing
	TimeLocal = millis() % 1000; //Update the local time


}