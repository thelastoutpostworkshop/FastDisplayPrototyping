/***
This example is intended to demonstrate the use of the Fast Display Prototyping Library
for the TFT_eSPI grahics library.

Upload this code and start sending graphical commands using the Serial Monitor!
Try sending this with the Serial Monitor : x;sc1,1;ttHello World!

Tutorial :
Documentation : https://github.com/thelastoutpostworkshop/FastDisplayPrototyping
***/

// Core graphics library
// Don't forget to select the driver of your display in the User_Setup_Select.h file 
#include <TFT_eSPI.h>

// Initialize the display
TFT_eSPI tft = TFT_eSPI(); 

// Fast Display Prototyping library
#define OUTPUT_CODE_ON_SERIAL         // Output graphical functions on the Serial Monitor, comment it to disable
#include <FastDisplayPrototyping.h>

// Initialize the display prototyping library
FastSerialDisplay sDisplay(&tft,"tft");

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