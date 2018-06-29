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
logger.thermistorB(1, 1, 10000, 25, 0); //  0  cm; nonfunctional; REPLACE!
logger.thermistorB(10150.2633156, 3788.02263361, 10000, 25, 1); // -5  cm; 17degC reading high R, discarded
logger.thermistorB(10081.9328752, 3829.20190643, 10000, 25, 2); // -10 cm; 17degC reading high R, discarded
logger.thermistorB(10140.8869792, 3830.71443474, 10000, 25, 3); // -15 cm
logger.thermistorB(10115.6127114, 3819.00197808, 10000, 25, 6); // -25 cm
logger.thermistorB(10101.3830281, 3822.56921131, 10000, 25, 7); // -35 cm

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
