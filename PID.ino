/* PID Control Circuit with support for MAX31685 RTD Probe Amplifier
 * Adapted from:
 *PID control code
  December 2007
  Creative Commons Attribution-Noncommercial-Share Alike 3.0
*/

#define WINDUP_GUARD_GAIN 100.0

float iState = 0.0;
float lastTemp = 0.0;

float pgain;
float igain;
float dgain;

float pTerm, iTerm, dTerm;

int pgainAddress, igainAddress, dgainAddress;

void setupPID(unsigned int padd, int iadd, int dadd) {
  // with this setup, you pass the addresses for the PID algorithm to use to
  // for storing the gain settings.  This way wastes 6 bytes to store the addresses,
  // but its nice because you can keep all the EEPROM address allocaton in once place.

  pgainAddress = padd;
  igainAddress = iadd;
  dgainAddress = dadd;

  pgain = readFloat(pgainAddress);
  igain = readFloat(igainAddress);
  dgain = readFloat(dgainAddress);
}

float getP() {
  // get the P gain
  return pgain;
}
float getI() {
  // get the I gain
  return igain;
}
float getD() {
  // get the D gain
  return dgain;
}

void setP(float p) {
  // set the P gain and store it to eeprom
  pgain = p;
  writeFloat(p, pgainAddress);
}

void setI(float i) {
  // set the I gain and store it to eeprom
  igain = i;
  writeFloat(i, igainAddress);
}

void setD(float d) {
  // set the D gain and store it to eeprom
  dgain = d;
  writeFloat(d, dgainAddress);
}

float updatePID(float targetTemp, float curTemp)
{
  // these local variables can be factored out if memory is an issue,
  // but they make it more readable
  float error;
  float windupGaurd;

  // determine how badly we are doing
  error = targetTemp - curTemp;

  // the pTerm is the view from now, the pgain judges
  // how much we care about error we are this instant.
  pTerm = pgain * error;

  // iState keeps changing over time; it's
  // overall "performance" over time, or accumulated error
  iState += error;

  // to prevent the iTerm getting huge despite lots of
  //  error, we use a "windup guard"
  // (this happens when the machine is first turned on and
  // it cant help be cold despite its best efforts)

  // not necessary, but this makes windup guard values
  // relative to the current iGain
  windupGaurd = WINDUP_GUARD_GAIN / igain;

  if (iState > windupGaurd)
    iState = windupGaurd;
  else if (iState < -windupGaurd)
    iState = -windupGaurd;
  iTerm = igain * iState;

  // the dTerm, the difference between the temperature now
  //  and our last reading, indicated the "speed,"
  // how quickly the temp is changing. (aka. Differential)
  dTerm = (dgain * (curTemp - lastTemp));

  // now that we've use lastTemp, put the current temp in
  // our pocket until for the next round
  lastTemp = curTemp;

  // the magic feedback bit
  return  pTerm + iTerm - dTerm;
}

void printPIDDebugString() {
  // A  helper function to keep track of the PID algorithm
  Serial.print("PID formula (P + I - D): ");
  printFloat(pTerm, 2);
  Serial.print(" + ");
  printFloat(iTerm, 2);
  Serial.print(" - ");
  printFloat(dTerm, 2);
  Serial.print(" POWER: ");
  printFloat(getHeatCycles(), 0);
  Serial.print(" ");
}

// END PID

//RTD
/***************************************************
  This is a library for the Adafruit PT100/P1000 RTD Sensor w/MAX31865

  Designed specifically to work with the Adafruit RTD Sensor
  ----> https://www.adafruit.com/products/3328

  This sensor uses SPI to communicate, 4 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_MAX31865.h>

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 max = Adafruit_MAX31865(10, 11, 12, 13);
// use hardware SPI, just pass in the CS pin
//Adafruit_MAX31865 max = Adafruit_MAX31865(10);

// The value of the Rref resistor. Use 430.0 for PT100 and 4300.0 for PT1000
#define RREF      430.0
// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0
float temp;

void setupTempSensor() {
  max.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  uint16_t rtd = max.readRTD();

  Serial.print("RTD value: "); Serial.println(rtd);
  float ratio = rtd;
  ratio /= 32768;
  Serial.print("Ratio = "); Serial.println(ratio, 8);
  Serial.print("Resistance = "); Serial.println(RREF * ratio, 8);
  Serial.print("Temperature = "); Serial.println((max.temperature(RNOMINAL, RREF)));

  // Check and print any faults
  uint8_t fault = max.readFault();
  if (fault) {
    Serial.print("Fault 0x"); Serial.println(fault, HEX);
    if (fault & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold");
    }
    if (fault & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold");
    }
    if (fault & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias");
    }
    if (fault & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open");
    }
    if (fault & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage");
    }
    max.clearFault();
  }
  Serial.println();
  delay(1000);
}

float getFreshTemp() {
  return (max.temperature(RNOMINAL, RREF));
}

float getTemp() {
  return (max.temperature(RNOMINAL, RREF));
}

//end RTD
