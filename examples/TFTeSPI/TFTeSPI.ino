/***
This example is intended to demonstrate the use of the Fast Display Prototyping Library
for the TFT_eSPI grahics library.

Tutorial :
Documentation : https://github.com/thelastoutpostworkshop/FastDisplayPrototyping
***/

#include <TFT_eSPI.h>                 // Core graphics library
#define OUTPUT_CODE_ON_SERIAL         // Output graphical functions on the Serial Monitor, comment it to disable
#include <FastDisplayPrototyping.h>

// Initialize the display
TFT_eSPI tft = TFT_eSPI(); 

// Initialize the display prototyping library
fastSerialDisplay sDisplay(&tft);

void setup() {
  Serial.begin(115200);  // This line mandatory for using the display prototyping library, change the baud rate if needed

  tft.begin();
  tft.setRotation(0);

  // Your specific code here
}

void loop(void) {
  sDisplay.readCommandsFromSerial(); // This line mandatory for using the display prototyping library
  // Your specific code here
}