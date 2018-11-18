//Configuration and libraries
#include "Configuration.h"
#include "Sensors.h"

//Set autofill sensor pin
Sensors boiler(9);

//PID and heater control variables
unsigned long lastPIDTime;  // most recent PID update time in ms
float targetTemp;  //current temperature goal
float heatPower; // 0 - 1000  milliseconds on per second

//Setup program
void setup() {
  delay(2500);
  setupAutofill();
  delay(2500);
  setupPID(PGAIN_ADR, IGAIN_ADR, DGAIN_ADR); // Send addresses to the PID module
  setupTempSensor();
  setupHeater();
  lastPIDTime = millis();
  setupBrewControl();
  setupSerialInterface();
  targetTemp = 125.0;
}

//Continuous Loop
void loop() {
  updateSerialInterface();
  updateAutofill();
  getTemp();
  if (millis() < lastPIDTime) {
    lastPIDTime = 0;
  }
  if ((millis() - lastPIDTime) > PID_UPDATE_INTERVAL) {
    lastPIDTime +=  PID_UPDATE_INTERVAL;
    heatPower = updatePID(targetTemp, getTemp());
    setHeatPowerPercentage(heatPower);
  }
  updateHeater();
  brewControl();
}
