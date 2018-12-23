/* This is the code to control the display output
 */

void setupDisplay() {
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE, ST7735_BLUE);
  tft.setTextSize(2);
  tft.println(" OpenSpro");
  tft.setTextSize(1);
  tft.println();
  tft.setTextSize(2);
  tft.println(" *STATUS*");
  tft.println(" *BOOT*");
}

void clearDisplay() {
  tft.fillScreen(ST7735_BLUE);
}

void updateDisplay() {
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE, ST7735_BLUE);
  tft.setTextSize(2);
  tft.println(" OpenSpro");
  tft.setTextSize(1);
  tft.println();
  tft.println();
  tft.setTextSize(2);
  tft.print("SET:"); tft.print(getTargetTemp(), 0); tft.print("C"); tft.println();
  tft.print("CUR:"); tft.print(getTemp(), 0); tft.print("C"); tft.print(" PWR:"); tft.print(getHeatCycles(), 0); tft.println();
  tft.print("GR V:"); tft.print(digitalRead(BREW)); tft.print(" P:"); tft.print(digitalRead(PUMP)); tft.println();
  tft.print("STEAM:"); tft.print(digitalRead(STEAM)); tft.println();
  tft.setTextSize(4);
  tft.setCursor(0, 96);
  tft.print(shotTimer.readTimer());
}

