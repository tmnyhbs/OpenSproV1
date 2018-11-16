/*    Configuration
 *   
 *    Default configurations for Espresso Machine
 *  
 */

#ifndef Configuration_h
#define Configuration_h

// These are addresses into EEPROM memory.  The values to be stores are floats which
// need 4 bytes each.  Thus 0,4,8,12,...
#define PGAIN_ADR 0
#define IGAIN_ADR 4
#define DGAIN_ADR 8
#define TEMP_ADDRESS 12

 // Debug Settings
 #define DEBUG true
 #define DEBUG_DELAY 1000

// Setup Relay Pins
#define AUTOFILL 3
#define HEAT 6
#define BREW 4
#define STEAM 2

// Delays + Intervals
#define AUTOFILL_DELAY 500
#define PID_UPDATE_INTERVAL 20


//Intervals for Serial
#define AUTO_PRINT_INTERVAL 200  // milliseconds
#define MAX_DELTA  100
#define MIN_DELTA  0.01
#define PRINT_PLACES_AFTER_DECIMAL 2  // set to match MIN_DELTA

// Simple extension to the EEPROM library
#include <avr/EEPROM.h>

float readFloat(int address) {
  float out;
  eeprom_read_block((void *) &out, (unsigned char *) address ,4 );
  return out;
}

void writeFloat(float value, int address) {
  eeprom_write_block((void *) &value, (unsigned char *) address ,4);
}

// END EEPROM Float

#endif


