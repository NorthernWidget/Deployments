//MargayDemo.ino
#include "TLog.h"
#include <DysonSW.h>
#include <DysonLW.h>
#include <Maxbotics.h>
#include <BME.h>

String Header = "Soil Moisture A [mV], Soil Moisture B [mV], Ground Temp [C], Wind Vane Pos [deg], Wind Speed [Rot/s], Rain Fall [in]"; //Information header

uint8_t I2CVals[2] = {0x6A, 0x77};  //FIX?? 

unsigned long UpdateRate = 5; //Number of seconds between readings 

const uint8_t ClkPin = 4;  //External digital pins for event counter 
const uint8_t DataPin = 5;

uint8_t SoilMoistPin1 = 0; //Analog channel 0
uint8_t SoilMoistPin2 = 1; //Analog channel 1

uint8_t GroundTempPin = 5; //Analog channel 5, hard wired resistor divider

uint8_t WindVanePin = 2; //Analog channel 2

uint8_t RainGaugeInt = 11; //Digital pin 11, AKA TX_EXT

volatile unsigned int Count = 0; //Global counter for tipping bucket 
//Pyro short wave 
DysonSW PyroUp;
DysonSW PyroDown;

//Pyro long wave 
DysonLW Pyrg;

//Counter for anamometer
// Tally Counter;

//Maxbotics rangefinder
Maxbotics Ultrasonic;

//BMP temp, pressure, relative humidty
BME RH;

TLog Logger;

void setup() {
	// Header = Header + PyroUp.GetHeader() + PyroDown.GetHeader() + Pyrg.GetHeader() + Ultrasonic.GetHeader() + RH.GetHeader();
	Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
	Init();
}

void loop() {
	Logger.Run(Update, UpdateRate);
}

String Update() 
{
	float Val1 = Logger.GetVoltage(SoilMoistPin1);
	float Val2 = Logger.GetVoltage(SoilMoistPin2);
	float Val3 = Logger.GetVoltage(GroundTempPin);
	float Val4 = GetTicks()/UpdateRate;  //DEBUG!
	float Val5 = Logger.GetVoltage(WindVanePin);
	unsigned int Val6 = Count*0.01; //Convert to inches of rain
	Count = 0; //Clear counter with each read 
	ClearTicks(); //Clear anemometer counter with each read //DEBUG!
	return String(Val1) + "," + String(Val2) + "," + String(Val3) + "," + String(Val4) + "," + String(Val5) + "," + String(Val6) + "," + PyroUp.GetString() + PyroDown.GetString() + Pyrg.GetString() + Ultrasonic.GetString() + RH.GetString();
}

void Init() 
{
	PyroUp.begin(UP);
	PyroDown.begin(DOWN);
	Pyrg.begin();
	// Counter.begin();
	Ultrasonic.begin();
	RH.begin(0x77); //Begin with standard address
	attachInterrupt(digitalPinToInterrupt(RainGaugeInt), Tip, FALLING);
	pinMode(RainGaugeInt, INPUT_PULLUP);

	Logger.io.pinMode(DataPin, INPUT);  //Set pin modes for clock and data 
	Logger.io.pinMode(ClkPin, OUTPUT);
}

unsigned int GetTicks() 
{
	unsigned int Data = 0; //Number of pulses since last read
	Logger.io.digitalWrite(ClkPin, HIGH);  //Pulse clock pin high for 5ms to load new data
	delay(7);
	Logger.io.digitalWrite(ClkPin, LOW);  

	for(int i = 0; i < 16; i++) {
		Logger.io.digitalWrite(ClkPin, HIGH);
		delayMicroseconds(500); //Wait to stabilize
		Data = (Data << 1) | Logger.io.digitalRead(DataPin);
		// Serial.println(digitalRead(DATA_PIN));
		Logger.io.digitalWrite(ClkPin, LOW);
		delayMicroseconds(500);
	}

	return Data;
}

void ClearTicks() 
{
	Logger.io.digitalWrite(ClkPin, HIGH);  //Pulse clock pin high for 10ms to clear data
	delay(20);
	Logger.io.digitalWrite(ClkPin, LOW); 
}

void Tip()  //Tipping bucket ISR
{
	Count++;
}
