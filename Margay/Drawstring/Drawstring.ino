//MargayDemo.ino
#include "Margay.h"

String Header = "Rain [in], TempAtmos [C],"; //Information header
uint8_t I2CVals[0] = {}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0, Build_B);  //Use build_b with correct ADC for board

void setup() {
  // Header = Header;  //Manually add atmospheric temp to header
  Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
  Init();
}

void loop() {
  Logger.Run(Update, UpdateRate);
}

String Update() 
{
  float Volt = Logger.GetVoltage(); 
  return String(Volt);
}

void Init() 
{
}
