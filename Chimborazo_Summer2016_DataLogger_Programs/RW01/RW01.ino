#include "Logger.h"

Logger logger;

////////////////////////////
// USER-ENTERED VARIABLES //
////////////////////////////
char* dataLoggerName = "Solar Radiation and Wind Direction 1";
char* fileName = "RW01.txt";
int dataLoggingIntervalMinutes = 5; // Will log when the remainder of "minutes", divided by
                                     // this, equals 0. For regular logging intervals, make  
                                     // sure that this number divides evenly into 60.
bool external_interrupt = false; // e.g., rain gage
// END USER-ENTERED VALUES //

void setup(){
  //noInterrupts();
  delay(50);
  pinMode(3, INPUT); // Include in library later
  digitalWrite(3, HIGH);
  logger.initialize(dataLoggerName, fileName, dataLoggingIntervalMinutes, external_interrupt);
  logger.setupLogger();
  pinMode(3, INPUT); // Include in library later
  digitalWrite(3, HIGH);
  delay(100);
  interrupts();
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

// Kipp and Zonen CMP 3
// Serial Number 163422
// Sensitivity 15.48 uV/W/m**2
// Gain = 1 + (100000 ohms / R_G)
// Original Gain of 51.025 -- 1999 ohms of resistance on amp
// Now removing one resistor -- then 2500 ohms
// Now nominal gain of 41 -- 2500 ohms of resistance on amp

// that uses the AD623
// Can't go over 1.1V
// with the original gain and the 15.48 uV/W/m**2 sensitivity value,
// We can go up to 1386.5255 W/m**2
// With the new gain of 41,
// We can go up to 1733.16 W/m**2
// For 2500 ohms, we need 4 10Kohm resistors in parallel.
// At 14 bit resolution, we have 0.3177 W/m**2 resolution

//while(1){}

//delay(5000);

logger.Pyranometer(6, 0.01548, 41, 3.301);
logger.Wind_Vane_Inspeed(7);
logger.Anemometer_reed_switch(1, 4000, 1.1176);

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
