//MargayDemo.ino
#include "Resnik.h"
#include <TP_Downhole_Longbow.h>

TP_Downhole_Longbow DH; //Initalize TP-Downhole sensor

String Header = ""; //Information header
uint8_t I2CVals[1] = {0x22}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 

Resnik Logger;

void setup() {
  Header = Header + DH.GetHeader();
  Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
  Init();
}

void loop() {
  Logger.Run(Update, UpdateRate);
}

String Update() 
{
  Init();
  delay(1500);
  return DH.GetString();
}

void Init() 
{
  DH.begin(13, 0x22); //Initialize TP-Downhole Longbow (at address = 13) and Longbow Widget (at address = 0x22)
}
