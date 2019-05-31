#include "Margay.h"
#include <DysonSW.h>
//#include <DysonLW.h>

DysonSW PyroUp(UP); //Initialzie Upward facing Dyson short wave
DysonSW	PyroDown(DOWN); //Initialize Downward facing Dyson short wave
//DysonLW Pyrg; //Initialize (Downward) Dyson long wave 

String Header = ""; //Information header
uint8_t I2CVals[4] = {0x41, 0x53, 0x40, 0x1D}; 
unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0);

void setup() {
	Header = Header + PyroUp.GetHeader() + PyroDown.GetHeader();
	Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
	Init();
}

void loop() {
	Logger.Run(Update, UpdateRate);
}

String Update() {
	Init(); //DEBUG!
	return PyroUp.GetString() + PyroDown.GetString();
}

void Init() 
{
	PyroUp.begin();
	PyroDown.begin();
}
