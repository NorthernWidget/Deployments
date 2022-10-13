#include "Margay.h"
#include <DysonSW.h>
#include <DysonLW.h>
#include <MaxbotixAW.h>
#include <Tally_I2C.h>
#include <T9602.h>
//#include <SoftwareSerial.h>

/*
Sensors:
1. Dyson SW up/down
2. Dyson LW down
3. TBRG
4. Wind vane
5. Anemometer
6. Ultrasonic rangefinder (& T correction)
7. T/RH
*/

Margay Logger(Model_2v0, Build_B);

// 1
DysonSW PyroUp(UP); // Initialzie upward-facing Dyson shortwave
DysonSW PyroDown(DOWN); // Initialize downward-facing Dyson shortwave

// 2
DysonLW Pyrg; // Initialize (downward) Dyson longwave 

// 3
// Rain -- no object -- but should make one for better coding in future

// 4
// Wind vane -- no object -- but should make one for better coding in future

// 5
Tally_I2C WindCounter;

// 6
// Hard-coded for RX1
Maxbotix Range;

// 7
T9602 TRH;  //Initialize T9602 Humidity sensor


String Header = ""; //Information header

//0x28: T9602 (T, RH)
//0x33: Tally (wind)
//0x40: Dyson up (Incoming SW radiation)
//0x41, 0x77: Dyson down (Outgoing SW radiation)
// ?: Dyson LW
uint8_t I2CVals[] = {0x77, 0x4A, 0x41, 0x53, 0x40, 0x1D, 0x28, 0x33};
unsigned long UpdateRate = 300; //Number of seconds between readings 



float getVaneOrientation(float VCC=3.3) {
  float Vin_normalized = analogRead(A0)/1023.; //Logger.GetVoltage() / VCC;
  float Vin_stretched = (Vin_normalized - 0.05) / 0.9;
  float Wind_angle = Vin_stretched * 360.; // Degrees -- azimuth
  return Wind_angle;
}

/*
float getAnemometerRPM(float VCC=3.3) {
  uint16_t Nrevs = WindCounter.GetTicks();
  float rpm = float(Nrevs) * UpdateRate / 60.;
  WindCounter.ClearTicks();
  return rpm;
}
*/

void setup() {
        // 11 is TX; 10 is RX. Not sure if this will work when also runnwining Serial; hope it does!
        // Actually, MaxBotix library is hard-coded for software serial, so should not be a problem
        // (unless SoftSerial conks out)
        pinMode(11, INPUT);
        digitalWrite(11, HIGH);
        Logger.SetExtInt(11, "Rain bucket tips [0.01in],"); // Must be set before begin
        //Logger.SetExtPCint(true, "Rain bucket tips [0.01in],"); // Must be set before begin

        Header = Header + PyroUp.GetHeader() + PyroDown.GetHeader() + \
                 Pyrg.GetHeader() + WindCounter.GetHeader() + \
                 "Wind direction [degrees]," + TRH.GetHeader() + \
                 Range.GetHeader();
                 
        Logger.begin(I2CVals, sizeof(I2CVals), Header); // Pass header info 
                                                        // to logger
        Init();

        WindCounter.Reset(); //Clear any old values on each system restart
}

void loop() {
        Init(); //Ensure devices are intialized after power cycle 
        Logger.Run(Update, UpdateRate);
}

String Update() {
        String VaneOrientation = String( getVaneOrientation(3.3) ) + ",";
        //String WindRPM = String( getAnemometerRPM() ) + ",";
        return PyroUp.GetString() + PyroDown.GetString() + \
               Pyrg.GetString() + WindCounter.GetString() + \
               VaneOrientation + TRH.GetString() + \
               Range.GetString() + \
               String(Logger.GetExtIntCount()) + ",";
               //String(Logger.GetExtPCintCount()) + ",";
}

void Init()
{
        pinMode(11, INPUT);
        digitalWrite(11, HIGH);
        PyroUp.begin();
        PyroDown.begin(); 
        Pyrg.begin();
        Range.begin();
        TRH.begin();
        WindCounter.begin();
}
