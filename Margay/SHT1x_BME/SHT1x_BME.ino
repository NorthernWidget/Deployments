//MargayDemo.ino
#include "Margay.h"
#include <BME.h>
#include <SHT1x.h>

#define DataPin 11
#define ClockPin 7

BME RH;
SHT1x ExtRH(DataPin, ClockPin);


String Header = "AirTemp [C], Humidity [%], "; //Information header
uint8_t I2CVals[1] = {0x77}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0, Build_B);  //Use build_b with correct ADC for board

void setup() {
  Header = Header + RH.GetHeader();  //Manually add soil temp to header, along with BME280 header
  Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
  Init();
}

void loop() {
  Init(); //Ensure devices are intialized after power cycle 
    Logger.Run(Update, UpdateRate);
}

String Update() 
{
  delay(2000);
  float Val1 = ExtRH.readTemperatureC();
  float Val2 = ExtRH.readHumidity();
  return String(Val1) + "," + String(Val2) + "," + RH.GetString(); //Return compensated value as string //DEBUG!
}

void Init() 
{
//  pinMode(DataPin, INPUT_PULLUP);
  RH.begin();
}
