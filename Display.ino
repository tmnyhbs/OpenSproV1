/* This is the code to control the display output
 */

#define TFT_SCLK 13         // SPI clock
#define TFT_MOSI 11         // SPI Data
#define TFT_CS   A3         // Display enable (Chip select), if not enabled will not talk on SPI bus
#define TFT_RST   -1         // Display reset pin connect this to the Arduino reset
#define TFT_DC     8        // register select (stands for Data Control perhaps!)

// initialise the routine to talk to this display with these pin connections (as we've missed off
// TFT_SCLK and TFT_MOSI the routine presumes we are using hardware SPI and internally uses 13 and 11
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

void setupDisplay() {
  tft.initR(INITR_144GREENTAB);
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLUE);
}

void updateDisplay() {
  tft.setCursor(0, 0);
  tft.setTextColor(ST7735_WHITE, ST7735_BLUE);
  tft.setTextSize(2);
  tft.println(" OpenSpro");
  tft.setTextSize(1);
  tft.println();
  tft.setTextSize(2);
  tft.println(" *STATUS*");
  tft.setTextSize(1);
  tft.println();
  tft.setTextSize(2);
  tft.println("Group:"); tft.println(digitalRead(BREW));
  tft.setTextSize(1);
  tft.println();
  tft.setTextSize(2);
  tft.println("Steam:"); tft.println(digitalRead(STEAM));
  tft.setTextSize(1);
  tft.println();
  tft.setTextSize(4);
  tft.setCursor(0, 96);
  tft.println("TIMER");
}

