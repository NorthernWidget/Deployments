//MargayDemo.ino
#include "Margay.h"
#include <T9602.h>

T9602 RH;  //Initialize T9602 Humidity sensor

String Header = ""; //Information header
uint8_t I2CVals[2] = {0x28}; 
// int Count = 0;
unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_2v0);

void setup() {
  Header = Header + RH.GetHeader();
  Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
  Init();
}

void loop() {
  Logger.Run(Update, UpdateRate);
}

String Update() 
{
  Init();
  return RH.GetString();
}

void Init() 
{
  RH.begin();
}
