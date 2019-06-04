#include "Margay.h"
#include <DysonSW.h>
#include <DysonLW.h>
#include <BME.h>
#include <Maxbotix.h>

Margay Logger(Model_2v0, Build_C);

DysonSW PyroUp(UP); // Initialzie upward-facing Dyson shortwave
DysonSW PyroDown(DOWN); // Initialize downward-facing Dyson shortwave
DysonLW Pyrg; // Initialize (downward) Dyson longwave 
BME BME280; // Initialize BME280 temperature, pressure, and relative humidity
Maxbotix Range(Logger.D0); // Initialize Maxbotix rangefinder on D0 pin for digital interface

String Header = ""; //Information header
uint8_t I2CVals[6] = {0x77, 0x4A, 0x41, 0x53, 0x40, 0x1D};
unsigned long UpdateRate = 60; //Number of seconds between readings 

void setup() {
        Header = Header + Range.GetHeader() + BME280.GetHeader() + \
                 PyroUp.GetHeader() + PyroDown.GetHeader() + Pyrg.GetHeader();
        Logger.begin(I2CVals, sizeof(I2CVals), Header); // Pass header info 
                                                        // to logger
        Init();
}

void loop() {
        Init(); //Ensure devices are intialized after power cycle 
        Logger.Run(Update, UpdateRate);
}

String Update() {
        return Range.GetString() + BME280.GetString() + \
               PyroUp.GetString() + PyroDown.GetString() + Pyrg.GetString();
}

void Init()
{
        BME280.begin();
        Range.begin(); // Begin Maxbotix on CS pin as software RX
        PyroUp.begin();
        PyroDown.begin();
        Pyrg.begin();
}

