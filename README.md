# OpenSproV1
Open Spro is the culmination of the hard work of many.  It is designed to work with the Arduino Uno R3, but can be easily adapted to other boards.  The display used is a generic 1.44" TFT Screen with the Adafruit GFX and ST7735 drivers.

## Code Contributors

Code for the PID Controller is adapted from:
Barebones Coffee Controller by Tim Hirzel
http://playground.arduino.cc/Main/BarebonesPIDForEspresso#main

Code for the Autofill Controller is adapted from:
Espresso Machine by Anthony Dipilato
http://anthonydipilato.com/2016/07/05/arduino-controlled-espresso-machine/

Code for TFT Display is adapted from:
128×128 Colour LCD to Arduino by Xtronical
http://www.xtronical.com/basics/displays/lcd-tft-colourcolor-display-128x128-pixelst7735-driver/lcd-tft-colourcolor-display-128x128-pixel-1-44inch-3-7cm-st7735-driver/

## Features

Current features include:

Full Gicar Fillbox Replacement (Autofill cirucit using PCB SSR and factory water level probe)

Full PID Controller using PT100 RTD Probe and Adafruit MAX31865 Thermocouple Amplifier

Electronic Brew Valve, Pump and Steam Valve Control (Currently via serial interface, buttons to come)

Shutdown mode which sets the target temperature to 0 and then open the electronic steam valve for 45 seconds. 

TFT Display showing status of the brew group and steam valves.

## Known Issues

Program used up 52% of storage memory and 75% of dynamic memory -- I am working to slim down the code to lower the dynamic memory consumption.  Any tips will be greatly appreciated!
