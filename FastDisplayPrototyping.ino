
#include <TFT_eSPI.h>
#define OUTPUT_CODE_ON_SERIAL
#include "src/FastDisplayPrototyping.h"


TFT_eSPI tft = TFT_eSPI(); // Invoke custom library
serialDisplay sDisplay(&tft);

//------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);

  tft.begin();
  tft.setRotation(0);

  // tft.setFreeFont(LABEL2_FONT);

  //Buffer Limit from the Serial Monitor is 64 bytes
  sDisplay.runCommands(F("x;ts1;sc10,10;#17e0;thDisplay Prototyping;"));
  sDisplay.runCommands(F("sc10,30;ts1;thLibrary v1.0;"));
  sDisplay.runCommands(F("sc10,10;tvVertical Center;sc10,85;ttNormal text;"));
  sDisplay.runCommands(F("#f804;ch20,60,10;#ffe0;cf50,60,10;"));
  sDisplay.runCommands(F("#05ff;gh70,50,90,60,70,70;#ffff;gf100,50,120,60,100,70;"));
  sDisplay.runCommands(F("#fc7c;rh130,50,20,20;#263c;rf160,50,20,20;#efe0;ri10,100,40,40,10;"));
  sDisplay.runCommands(F("#f9e0;rj60,100,40,40,13;#1f9d;lv2,45,280;#07ff;lh2,170,240;"));
  sDisplay.runCommands(F("#ded8;dl2,170,240,320;"));

  // tft.fillScreen(TFT_BLACK);
  // tft.fillRectHGradient(10,50,50,50,0x72ff,0xd2ff);
}

void loop(void) {

  sDisplay.readCommandsFromSerial();
}