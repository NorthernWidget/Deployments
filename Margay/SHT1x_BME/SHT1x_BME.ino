//MargayDemo.ino
#include "Margay.h"
#include <BME.h>
//#include <SHT1x.h>
#include <SoftwareSerial.h>

#define DataPin 11
//#define ClockPin 7

BME RH;
SoftwareSerial UART(11, -1); //Only setup to recieve, not send 
//SHT1x ExtRH(DataPin, ClockPin);


String Header = "AirTemp [C], Humidity [%], "; //Information header
uint8_t I2CVals[1] = {0x77}; 

unsigned long UpdateRate = 60; //Number of seconds between readings 

Margay Logger(Model_1v0, Build_A);  //Use build_b with correct ADC for board

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
  delay(10000); //wait for reading?? //DEBUG!
  unsigned long LocalTime = millis();
  String Test = ""; //Use to compare to input string
  float Val1 = 0; //Temp value from SHT10
  float Val2 = 0;  //Pressure value from SHT10
  while(Test.indexOf("SHT10") < 0 && (millis() - LocalTime) < 5000) { //Read until you get input or timeout
    Test = UART.readStringUntil('\n');
//    Serial.print(Test); //DEBUG!
//    Serial.print("\t"); //DEBUG!
//    Serial.println(Test.indexOf("SHT10")); //DEBUG!
//    delay(10);
  } 
  if(Test.indexOf("SHT10") >= 0) { //If valid result is sent, parse out values 
    Val1 = UART.parseFloat(); 
    Val2 = UART.parseFloat();
  }
  else {  //Otherwise return specifed fail values
    Val1 = -9999;
    Val2 = -9999; 
  }
//  delay(2000);
//  float Val1 = ExtRH.readTemperatureC();
//  float Val2 = ExtRH.readHumidity();
  return String(Val1) + "," + String(Val2) + "," + RH.GetString(); //Return compensated value as string //DEBUG!
}

void Init() 
{
//  pinMode(DataPin, INPUT_PULLUP);
  UART.begin(9600);
  RH.begin();
}
