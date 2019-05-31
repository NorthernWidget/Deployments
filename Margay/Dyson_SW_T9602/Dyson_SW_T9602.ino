#include "Margay.h"
#include <T9602.h>
#include <DysonSW.h>
//#include <DysonLW.h>

DysonSW PyroUp(UP); //Initialzie Upward facing Dyson short wave
DysonSW	PyroDown(DOWN); //Initialize Downward facing Dyson short wave
T9602 RH;  //Initialize T9602 Humidity sensor
//DysonLW Pyrg; //Initialize (Downward) Dyson long wave 

String Header = ""; //Information header
uint8_t I2CVals[5] = {0x41, 0x53, 0x40, 0x1D, 0x28}; 
unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0);

void setup() {
	Header = Header + PyroUp.GetHeader() + PyroDown.GetHeader() + RH.GetHeader();
	Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
	Init();
}

void loop() {
	Logger.Run(Update, UpdateRate);
}

String Update() {
	Init(); //DEBUG!
	return PyroUp.GetString() + PyroDown.GetString() + RH.GetString();
}

void Init() 
{
	PyroUp.begin();
	PyroDown.begin();
  RH.begin();
}
