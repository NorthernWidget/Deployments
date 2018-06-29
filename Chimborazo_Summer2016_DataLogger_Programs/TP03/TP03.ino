#include "Logger.h"

Logger logger;

////////////////////////////
// USER-ENTERED VARIABLES //
////////////////////////////
char* dataLoggerName = "Temperature Probe 03";
char* fileName = "TP03.txt";
int dataLoggingIntervalMinutes = 5; // Will log when the remainder of "minutes", divided by
                                    // this, equals 0. For regular logging intervals, make  
                                    // sure that this number divides evenly into 60.
bool external_interrupt = false; // e.g., rain gage

void setup(){
  logger.initialize(dataLoggerName, fileName, dataLoggingIntervalMinutes, external_interrupt);
  logger.setupLogger();
}

void loop(){

// ***************************************** 

// Sleep 
logger.sleep();

// Wake up and initialize
logger.startLogging();

// ****** DO NOT EDIT ABOVE THIS LINE ****** 

//////////////////////////////////
// READ SENSORS: EDIT THIS PART //
//////////////////////////////////

// Analog sensors: place all analog sensor commands between
// startAnalog() and endAnalog().
// If you have no analog sensors, you should comment out the 
// startAnalog() and endAnalog() commands

logger.startAnalog();

// Arguments in order:
// 1. Resistance R0 at temperature T0
// 2. b-value
// 3. Reference resistor resistance
// 4. Temperature T0 at which thermistor resistance is R0
// 5. Analog pin to which thermistor is attached.
logger.thermistorB(10155.9398661, 3805.97380395, 10000, 25, 0); //  0  cm
logger.thermistorB(10120.8868173, 3835.20427835, 10000, 25, 1); // -5  cm
logger.thermistorB(10131.1325405, 3831.74033674, 10000, 25, 2); // -10 cm
logger.thermistorB(10111.2254651, 3822.32606211, 10000, 25, 3); // -15 cm
logger.thermistorB(10074.7754858, 3831.58391976, 10000, 25, 6); // -25 cm
logger.thermistorB(10125.2915462, 3826.75785612, 10000, 25, 7); // -35 cm

logger.endAnalog();

//
// INSERT DIGITAL SENSOR READING COMMANDS HERE!
//

// NOTE: THE BUFFER SIZE IS (CHECK ON THIS!!!!!!!!!!!!!!) 256 BYTES;
// run "logger.bufferWrite" if you think you are approaching this limit.
// Otherwise, the buffer will overflow and I'm not sure what will happen.


// ****** DO NOT EDIT BELOW THIS LINE ****** 

// Wrap up files, turn off SD card, and go back to sleep
logger.endLogging();

// ***************************************** 

}
