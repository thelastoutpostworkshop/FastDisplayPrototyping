
#include <TFT_eSPI.h>
#include "DisplayPrototyping.h"

// Follow your display driver documentation
TFT_eSPI tft = TFT_eSPI(); 

void setup() {
  Serial.begin(9600); // This line mandatory for using the display prototyping library

  tft.begin();
  tft.setRotation(0);

  // Your specific code here
}

void loop(void) {
  sDisplay.readCommandsFromSerial(); // This line mandatory for using the display prototyping library
  
  // Your specific code here
}