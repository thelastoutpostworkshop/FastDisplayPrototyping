
#include <TFT_eSPI.h>
#define OUTPUT_CODE_ON_SERIAL
#include <FastDisplayPrototyping.h>

// Follow your display driver documentation
TFT_eSPI tft = TFT_eSPI(); 

// Initialize the display prototyping library
serialDisplay sDisplay(&tft);

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