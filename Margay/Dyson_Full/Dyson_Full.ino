#include "Margay.h"
#include <DysonSW.h>
#include <DysonLW.h>

DysonSW PyroUp(UP); //Initialzie Upward facing Dyson short wave
DysonSW	PyroDown(DOWN); //Initialize Downward facing Dyson short wave
DysonLW Pyrg; //Initialize (Downward) Dyson long wave 

String Header = ""; //Information header
uint8_t I2CVals[1] = {0x4A}; 
unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0);

void setup() {
	Header = Header + PyroUp.GetHeader() + PyroDown.GetHeader() + Pyrg.GetHeader();
	Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
	Init();
}

void loop() {
	Logger.Run(Update, UpdateRate);
}

String Update() 
{
	Init();
// delay(4000);
//	return PyroUp.GetString() + PyroDown.GetString() + Pyrg.GetString();
  return PyroUp.GetString() + PyroDown.GetString();
}

void Init() 
{
	PyroUp.begin();
	PyroDown.begin();
//	Pyrg.begin();
}
