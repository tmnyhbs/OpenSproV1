/*    Configuration
      Default configurations for Espresso Machine
*/

#ifndef Configuration_h
#define Configuration_h

// These are addresses into EEPROM memory.  The values to be stores are floats which
// need 4 bytes each.  Thus 0,4,8,12,...
#define PGAIN_ADR 0
#define IGAIN_ADR 4
#define DGAIN_ADR 8
#define TEMP_ADDRESS 12

// Setup Relay Pins
#define AUTOFILL 3
#define HEAT 6
#define BREW 4
#define PUMP 5
#define STEAM 2

// Setup Button Pins
const uint8_t BREWBUT = A0;
#define BREWLED A1
const uint8_t STEAMBUT = A2;
#define STEAMLED A3

// Delays + Intervals
#define AUTOFILL_DELAY 500
#define PID_UPDATE_INTERVAL 20
#define PREINF_DELAY 0

// Simple extension to the EEPROM library
#include <avr/EEPROM.h>

float readFloat(int address) {
  float out;
  eeprom_read_block((void *) &out, (unsigned char *) address , 4 );
  return out;
}

void writeFloat(float value, int address) {
  eeprom_write_block((void *) &value, (unsigned char *) address , 4);
}
// END EEPROM Float

#endif
