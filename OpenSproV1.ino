//Configuration and libraries
#include "Configuration.h"
#include "Sensors.h"
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

//Set autofill sensor pin
Sensors boiler(9);

//PID and heater control variables
unsigned long lastPIDTime;  // most recent PID update time in ms
float targetTemp = 125.0;  //current temperature goal
float heatPower; // 0 - 1000  milliseconds on per second

//Setup program
void setup() {
  setupAutofill();
  delay(10000);
  setupPID(PGAIN_ADR, IGAIN_ADR, DGAIN_ADR); // Send addresses to the PID module
  setupTempSensor();
  setupHeater();
  lastPIDTime = millis();
  setupControls();
  setupSerialInterface();
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
  updateBrewControl();
  updateSteamControl();
}
