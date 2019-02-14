//BME280_DysonSW2.ino
#include "Margay.h"
#include <BME.h>
#include <DysonSW.h>

BME RH;
DysonSW PyroUp(UP); //Initialzie Upward facing Dyson short wave
DysonSW	PyroDown(DOWN); //Initialize Downward facing Dyson short wave

String Header = ""; //Information header
uint8_t I2CVals[5] = {0x40, 0x1D, 0x41, 0x53, 0x77};

unsigned long UpdateRate = 60; //Number of seconds between readings

Margay Logger(Model_1v0, Build_B);  //Use build_b with correct ADC for board

void setup() {
  Header = Header + RH.GetHeader() + PyroUp.GetHeader() + PyroDown.GetHeader(); //Manually add soil temp to header, along with BME280 header
  Logger.begin(I2CVals, sizeof(I2CVals), Header); //Pass header info to logger
  Init();
}

void loop() {
  Logger.Run(Update, UpdateRate);
}

String Update() {
  Init(); //Ensure devices are intialized after power cycle
  return RH.GetString() + PyroUp.GetString() + PyroDown.GetString(); //Return sensor outputs as String
}

void Init() {
  RH.begin();
  PyroUp.begin();
  PyroDown.begin();
}
