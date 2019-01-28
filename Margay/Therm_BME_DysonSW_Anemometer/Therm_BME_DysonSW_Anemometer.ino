//MargayDemo.ino
#include "Margay.h"
#include <BME.h>
#include <DysonSW.h>
#include <Tally.h>

BME RH;
DysonSW PyroUp(UP); //Initialzie Upward facing Dyson short wave
Tally Counter;


String Header = "TempGround [C],"; //Information header
uint8_t I2CVals[3] = {0x40, 0x1D, 0x77}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0, Build_B);  //Use build_b with correct ADC for board

void setup() {
  Header = Header + RH.GetHeader() + PyroUp.GetHeader() + Counter.GetHeader();  //Manually add soil temp to header, along with BME280 header
  Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
  Init();
}

void loop() {
  	Logger.Run(Update, UpdateRate);
}

String Update() 
{
  Init(); //Ensure devices are intialized after power cycle 
  float Volt = Logger.GetVoltage(); //Get raw voltage from logger
  float Val1 = TempConvert(Volt, 1.8, 10000, 3977, 10000); //For use with thermistor NTCLE400E3103H
  Val1 = Val1 - 273.15; //Convert to C from K
  return String(Val1) + "," + RH.GetString() + PyroUp.GetString() + Counter.GetString(); //Return compensated value as string //DEBUG!
}

void Init() 
{
  RH.begin();
  PyroUp.begin();
  Counter.begin(3, 11, HIGH); //Initialize counter on pins 3 and 11 for clock and data, use inverted clock logic
}

float TempConvert(float V, float Vcc, float R, float Beta, float R25)
{
  // float Rt = (Vcc/V)*R - R;  //Use if thermistor is on TOP side of voltage divider
  float Rt = -R/(1 - (Vcc/V)); //Use if thermistor is on BOTTOM side of voltage divider  
  float T = 1.0/((1.0/Beta)*log(Rt/R25) + 1/298.15);
  return T;
}
