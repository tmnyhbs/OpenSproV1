/* This is an update to the "Heater Control" function
 *  Developed by Tim Herzil with the original
 *  BBCC in 2007
 */

float heatcycles; // the number of millis out of 1000 for the current heat amount (percent * 10)

boolean heaterState = 0;

unsigned long heatCurrentTime, heatLastTime;

void setTargetTemp(float t) {
  targetTemp = t;
  writeFloat(t, TEMP_ADDRESS);
}

float getTargetTemp() {
  return targetTemp;
}

void updateHeater() {
  heatCurrentTime = millis();
  if (heatCurrentTime - heatLastTime >= 1000 or heatLastTime > heatCurrentTime) { //second statement prevents overflow errors
    // begin cycle
    _turnHeatElementOnOff(1);  //
    heatLastTime = heatCurrentTime;
  }
  if (heatCurrentTime - heatLastTime >= heatcycles) {
    _turnHeatElementOnOff(0);
  }
}

void setHeatPowerPercentage(float power) {
  if (power <= 0.0) {
    power = 0.0;
  }
  if (power >= 1000.0) {
    power = 1000.0;
  }
  heatcycles = power;
}

float getHeatCycles() {
  return heatcycles;
}

void _turnHeatElementOnOff(boolean on) {
  digitalWrite(HEAT, on); //turn pin high
  heaterState = on;
}

//End Heater Control
