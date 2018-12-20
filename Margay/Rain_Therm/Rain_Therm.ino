//MargayDemo.ino
#include "Margay.h"

String Header = "Rain [in], TempAtmos [C],"; //Information header
uint8_t I2CVals[0] = {}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0, Build_C);  //Use build_b with correct ADC for board

volatile unsigned int Count = 0; //Global counter for tipping bucket 
unsigned long Holdoff = 25; //25ms between bucket tips minimum

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
  float Val1 = Count*0.01;  //Account for volume per tip
  Count = 0; //Clear count with each update 
  float Volt = Logger.GetVoltage(); 
  float Val2 = TempConvert(Volt, 1.8, 10000, 3977, 10000); //For use with thermistor NTCLE400E3103H
  return String(Val1) + "," + String(Val2);
}

void Init() 
{
  attachInterrupt(digitalPinToInterrupt(Logger.ExtInt), Tip, FALLING);
  pinMode(Logger.ExtInt, INPUT_PULLUP);
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
