
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <Adafruit_GFX.h>    // Core graphics library
#include "src/serialDisplay.h"

// TFT_eSPI tft = TFT_eSPI(); // Invoke custom library

// The control pins for the LCD can be assigned to any digital or
// analog pins...but we'll use the analog pins as this allows us to
// double up the pins with the touch screen (see the TFT paint example).
#define LCD_CS A3    // Chip Select goes to Analog 3
#define LCD_CD A2    // Command/Data goes to Analog 2
#define LCD_WR A1    // LCD Write goes to Analog 1
#define LCD_RD A0    // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Using two fonts since numbers are nice when bold
// #define LABEL1_FONT &FreeSansOblique12pt7b // Key label font 1
// #define LABEL2_FONT &FreeSansBold12pt7b    // Key label font 2


serialDisplay sDisplay(&tft);

//------------------------------------------------------------------------------------------

void setup() {
  // Use serial port
  Serial.begin(9600);

  // Initialise the TFT screen
  tft.begin();

  // Set the rotation before we calibrate
  tft.setRotation(0);

  // tft.setFreeFont(LABEL2_FONT);

  sDisplay.runCommands("x;sc100,100;ts2;ththis is a test;ch100,100,10");
  // // Clear the screen
  // tft.fillScreen(TFT_BLACK);

  // // Draw keypad background
  // tft.fillRect(0, 0, 240, 320, TFT_DARKGREY);

  // // Draw number display area and frame
  // tft.fillRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_BLACK);
  // tft.drawRect(DISP_X, DISP_Y, DISP_W, DISP_H, TFT_WHITE);

  // // Draw keypad
  // drawKeypad();
}

void loop(void) {

  sDisplay.readCommandsFromSerial();

}
