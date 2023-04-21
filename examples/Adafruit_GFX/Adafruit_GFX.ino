/***
This example is intended to demonstrate the use of the Fast Display Prototyping Library
for the TFT_eSPI grahics library.

Upload this code and start sending graphical commands using the Serial Monitor!
Try sending this with the Serial Monitor : x;sc1,1;ttHello World!

Tutorial :
Documentation : https://github.com/thelastoutpostworkshop/FastDisplayPrototyping
***/

// Core graphics library
#include <Adafruit_GFX.h>     

// -- Hardware-specific library & Definitions Section
#include <Adafruit_TFTLCD.h>  

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); // Initialize the display
// -- End of the Hardware-specific Section

// Fast Display Prototyping library
#define OUTPUT_CODE_ON_SERIAL // Output graphical functions on the Serial Monitor, comment it to disable
#include <FastDisplayPrototyping.h>

// Initialize the display prototyping library
FastSerialDisplay sDisplay(&tft, "tft");

void setup() {
  Serial.begin(9600); // This line mandatory for using the display prototyping library, change the baud rate if needed

  tft.begin();
  tft.setRotation(0);

  // Your specific code here
}

void loop(void) {
  sDisplay.readCommandsFromSerial(); // This line mandatory for using the display prototyping library
  // Your specific code here
}