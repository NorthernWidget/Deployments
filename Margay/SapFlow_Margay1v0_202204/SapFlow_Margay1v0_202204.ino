/*
 * Margay v1.0 connected to thermal sap-flow sensor with thermocouple
 */

#include "Margay.h"

// No sensor libraries needed

// Instantiate Margay class
Margay Logger(MODEL_1v0, BUILD_B);

// Empty header to start; will include sensor labels and information
String header;

// Number of seconds between readings
// The Watchdog timer will automatically reset the logger after approximately 36 minutes.
// We recommend logging intervals of 30 minutes (1800 s) or less.
// Intervals that divide cleanly into hours are strongly preferable.
uint32_t updateRate = 10;

void setup(){
    // No I2C values to pass
    // header = header + mySensor.getHeader(); // + nextSensor.getHeader() + ...
    header = header + "Thermocouple Voltage";
    Logger.begin(header);
}

void loop(){
    Logger.run(update, updateRate);
}

String update() {
    initialize(); // Unnecessary here; keeping for the sake of example + consistency
    // Turn on auxiliary power -- enable the heater.
    Logger.powerAux(HIGH);
    //
    // PROBABLY WANT TO WAIT SOME TIME: LET'S COME BACK TO THIS
    //
    float _V = Logger.getVoltage(); // Thermocouple voltage
    String _VString = String(_V, 6); // 10 decimal places (more than needed, but space is not a concern): 1.8V / 2**18 = 6.86455E-6
    return _VString; // If a sensor were attached
    Logger.powerAux(LOW); // Turn off heater -- or should we make many measurements while the heater is still on?
}

void initialize(){
    // Empty function: No I2C sensors to initialize
    //mySensor.begin(); // For any Northern Widget sensor
                       // Other libraries may have different standards
}

