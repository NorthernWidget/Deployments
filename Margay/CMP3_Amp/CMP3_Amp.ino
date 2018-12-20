//MargayDemo.ino
#include "Margay.h"
#include "MCP3421.h"  //Inlcude ADC lib

MCP3421 CMP3(0x6B);  //Init with addres 0x6B

String Header = "Pyro [uV], "; //Information header
uint8_t I2CVals[1] = {0x6B}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0);

void setup() {
	Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
	Init();
}

void loop() {
	Init();
	Logger.Run(Update, UpdateRate);
}

String Update() 
{
	float Val1 = CMP3.GetVoltage()*(1.0e4); //Return val in uV, account for gain of amp (100 V/V)
	return String(Val1);
}

void Init() 
{
	CMP3.Begin();
	CMP3.SetResolution(18); //Set for full 18 bit resolution
}
