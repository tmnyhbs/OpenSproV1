#include <core_build_options.h>
//Configuration and libraries
#include "Configuration.h"
#include "Sensors.h"
#include <secTimer.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

//display
#define TFT_SCLK 13         // SPI clock
#define TFT_MOSI 11         // SPI Data
#define TFT_CS   A5         // Display enable (Chip select), if not enabled will not talk on SPI bus
#define TFT_RST   -1         // Display reset pin connect this to the Arduino reset
#define TFT_DC     8        // register select (stands for Data Control perhaps!)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);


//Set autofill sensor pin
Sensors boiler(9);

//PID and heater control variables
unsigned long lastPIDTime;  // most recent PID update time in ms
float targetTemp = 125.0;  //current temperature goal
float heatPower; // 0 - 1000  milliseconds on per second

//Setup program
void setup() {
  tft.initR(INITR_144GREENTAB);
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLUE);
  tft.setTextSize(2);
  tft.println("Initialize");
  tft.println("Autofill");
  setupAutofill();
  tft.println("PID");
  delay(2000);
  setupPID(PGAIN_ADR, IGAIN_ADR, DGAIN_ADR); // Send addresses to the PID module
  tft.println("RTD Probe");
  setupTempSensor();
  tft.println("Heater");
  setupHeater();
  lastPIDTime = millis();
  tft.println("Buttons");
  setupControls();
  tft.println("Serial");
  setupSerialInterface();
  tft.println("Display");
  delay(2000);
  setupDisplay();
  clearDisplay();
}

//Continuous Loop
void loop() {
  updateSerialInterface();
  updateDisplay();
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
