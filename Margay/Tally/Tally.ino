//Tally Demo
#include "Margay.h"
#include <Tally.h>

// #define MARGAY_1v0
Tally Counter;

String Header = ""; //Information header
uint8_t I2CVals[0] = {}; 
unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0);

void setup() {
  Header = Header + Counter.GetHeader();
  Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
  Init();
}

void loop() {
  Logger.Run(Update, UpdateRate);
}

String Update() 
{
  Init();
  return Counter.GetString();
}

void Init() 
{
  Counter.begin(3, 11, HIGH); //Initialize counter on pins 3 and 11 for clock and data, use inverted clock logic
}
