#include "Logger.h"

Logger logger;

////////////////////////////
// USER-ENTERED VARIABLES //
////////////////////////////
char* dataLoggerName = "Glacier Station 5";
char* fileName = "GS05.txt";
int dataLoggingIntervalMinutes = 5; // Will log when the remainder of "minutes", divided by
                                     // this, equals 0. For regular logging intervals, make  
                                     // sure that this number divides evenly into 60.
bool external_interrupt = false; // e.g., rain gage
// END USER-ENTERED VALUES //

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

//while(1){}

// Temperature probe = T3 (from calibration sheet)
// Voltages measured with Fluke meter, not checked against precision Vref

logger.HM1500LF_humidity_with_external_temperature(1, 3.285, 10035.6525854, 3311.13197286, 10000, 25, 0);
logger.Inclinometer_SCA100T_D02_analog_Tcorr(6, 7, 3.285, 5.206, 10035.6525854, 3311.13197286, 10000, 25, 0);
logger.maxbotixHRXL_WR_analog(10, 3, 99, true);
//logger.maxbotixHRXL_WR_analog_oneping(3); // Desktop/Logger.cpp.new
// FAILS TO WRITE TO SD CARD WITH DELAY! -- fixed, was because I turned on and off SD power more than it wanted

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
