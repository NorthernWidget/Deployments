//MargayDemo.ino
#include "Margay.h"
#include <Maxbotix.h>
#include <DysonSW.h>
#include <DysonLW.h>
#include <T9602.h>
#include <Tally_I2C.h>

Margay Logger(Model_2v0, Build_C);  //Use build_b with correct ADC for board

DysonSW PyroUp(UP); // Initialzie upward-facing Dyson shortwave
DysonSW PyroDown(DOWN); // Initialize downward-facing Dyson shortwave
DysonLW Pyrg; // Initialize (downward) Dyson longwave 
Maxbotix Range(Logger.D0); // Initialize Maxbotix rangefinder on D0 pin for digital interface
T9602 RH;  //Initialize T9602 Humidity sensor
Tally_I2C Counter; //Initialize Tally counter 

String Header = "Rain [in], WindDir [Deg], GndTemp [C], "; //Information header
uint8_t I2CVals[7] = {0x28, 0x33, 0x4A, 0x41, 0x53, 0x40, 0x1D}; //RH, Tally, LW, SW down, SW up

unsigned long UpdateRate = 60; //Number of seconds between readings 

volatile unsigned int Count = 0; //Global counter for tipping bucket 
unsigned long Holdoff = 25; //25ms between bucket tips minimum

void setup() {
  // Header = Header;  //Manually add atmospheric temp to header
  Header = Header + Range.GetHeader() +  \
			PyroUp.GetHeader() + PyroDown.GetHeader() + Pyrg.GetHeader() + RH.GetHeader() + Counter.GetHeader(true);
  Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
  Init();
}

void loop() {
  Logger.Run(Update, UpdateRate);
}

String Update() 
{
  float Rain = Count*0.01;  //Account for volume per tip
  Count = 0; //Clear count with each update 
  float WindDir = (analogRead(A0)/1024.0)*365.0; //Convert analog read into angle 
  float Volt = Logger.GetVoltage(); //Get accurate analog voltage 
  float Temp = TempConvert(Volt, 1.8, 10000, 3977, 10000); //For use with thermistor NTCLE400E3103H
  Temp = Temp - 273.15; //Convert to C from K
  return String(Rain) + "," + String(WindDir) + "," + String(Temp) + "," + Range.GetString() + \
               PyroUp.GetString() + PyroDown.GetString() + Pyrg.GetString() + RH.GetString() + Counter.GetString();
}

void Init() 
{
	attachInterrupt(digitalPinToInterrupt(Logger.TX), Tip, FALLING);
//	pinMode(Logger.ExtInt, INPUT_PULLUP);
	RH.begin();
	Range.begin(); // Begin Maxbotix on CS pin as software RX
	PyroUp.begin();
	PyroDown.begin();
	Pyrg.begin();
  Counter.begin();
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

float TempConvert(float V, float Vcc, float R, float Beta, float R25)
{
  // float Rt = (Vcc/V)*R - R;  //Use if thermistor is on TOP side of voltage divider
  float Rt = -R/(1 - (Vcc/V)); //Use if thermistor is on BOTTOM side of voltage divider  
  float T = 1.0/((1.0/Beta)*log(Rt/R25) + 1/298.15);
  return T;
}
