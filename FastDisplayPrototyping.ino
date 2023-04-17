//GFX Test

#include <Adafruit_TFTLCD.h>    // Hardware-specific library
#include <Adafruit_GFX.h>       // Core graphics library
#define OUTPUT_CODE_ON_SERIAL   // Output graphical functions on the Serial Monitor, comment it to disable
#include "src/FastDisplayPrototyping.h"

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Initialize the display
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Initialize the display prototyping library
FastSerialDisplay sDisplay(&tft,"tft"); 

void setup() {
  Serial.begin(9600); // This line mandatory for using the display prototyping library, change the baud rate if needed

  tft.begin();
  tft.setRotation(0);

  sDisplay.runCommands(F("sc1,1;ttHello;"));
  // sDisplay.runCommands(F("ts2;ttWorld!;"));
  // sDisplay.runCommands(F("#ff00;dp100,10;"));
  // sDisplay.runCommands(F("dl2,20,2,h;"));
  // sDisplay.runCommands(F("#005f;ch100,10,10;"));
  // sDisplay.runCommands(F("#f104;cf120,10,10;"));
  // sDisplay.runCommands(F("#f7c2;ce110,75,10,50;"));
  // sDisplay.runCommands(F("#12df;cg90,75,10,50;"));
  // sDisplay.runCommands(F("ca31,100,20,25,0,90,f8a2,00,0;"));
  // sDisplay.runCommands(F("#f8b9;rh5,20,20,30;"));
  // sDisplay.runCommands(F("#17de;rf5,60,20,30;"));
  // sDisplay.runCommands(F("#17cb;ri30,20,20,30,4;"));
  // sDisplay.runCommands(F("#18bf;rj30,60,20,30,4;"));
  // sDisplay.runCommands(F("#17d4;gh15,120,5,110,25,110;"));
  // sDisplay.runCommands(F("#fe42;gf35,120,25,110,55,120;"));
  // sDisplay.runCommands(F("cb50,25,80,70,300,360,00f5,00,1;"));
  // sDisplay.runCommands(F("ci65,35,13,77e0,0;"));
  // sDisplay.runCommands(F("cj65,75,13,07e5,0;"));
  // sDisplay.runCommands(F("rs70,60,5,8,20,30,f820,0;"));
  // sDisplay.runCommands(F("rt80,100,20,20,5,fde0,0;"));

  // Your specific code here
}

void loop(void) {
  sDisplay.readCommandsFromSerial(); // This line mandatory for using the display prototyping library
  // Your specific code here
}


// TFT eSPI test 

// #include <TFT_eSPI.h>
// #define OUTPUT_CODE_ON_SERIAL
// #include "src/FastDisplayPrototyping.h"

// TFT_eSPI display = TFT_eSPI(); 
// FastSerialDisplay sDisplay(&display,"display");

// //------------------------------------------------------------------------------------------

// void setup()
// {
//   Serial.begin(115200);

//   display.begin();
//   display.setRotation(0);

//   // display.setFreeFont(LABEL2_FONT);

//   // Buffer Limit from the Serial Monitor is 64 bytes
//   // sDisplay.runCommands(F("x;ts1;sc10,10;#17e0;thDisplay Prototyping;"));
//   // sDisplay.runCommands(F("sc10,30;ts1;thLibrary v1.0;lh0,22,w"));
//   // sDisplay.runCommands(F("sc10,10;tvVertical Center;sc10,85;ttNormal text;"));
//   // sDisplay.runCommands(F("#f804;ch20,60,10;#ffe0;cf50,60,10;"));
//   // sDisplay.runCommands(F("#05ff;gh70,50,90,60,70,70;#ffff;gf100,50,120,60,100,70;"));
//   // sDisplay.runCommands(F("#fc7c;rh130,50,20,20;#263c;rf160,50,20,20;#efe0;ri10,100,40,40,10;"));
//   // sDisplay.runCommands(F("#f9e0;rj60,100,40,40,13;#1f9d;lv2,45,280;#07ff;lh2,170,240;"));
//   // sDisplay.runCommands(F("#ded8;dl2,170,240,320;"));

//   sDisplay.runCommands(F("x;#00ff;"));
//   sDisplay.runCommands(F("sc1,1;ttHello;"));
//   sDisplay.runCommands(F("ts2;ttWorld!;"));
//   sDisplay.runCommands(F("#ff00;dp100,10;"));
//   sDisplay.runCommands(F("dl2,20,2,h;"));
//   sDisplay.runCommands(F("#005f;ch100,10,10;"));
//   sDisplay.runCommands(F("#f104;cf120,10,10;"));
//   sDisplay.runCommands(F("#f7c2;ce110,75,10,50;"));
//   sDisplay.runCommands(F("#12df;cg90,75,10,50;"));
//   sDisplay.runCommands(F("ca31,100,20,25,0,90,f8a2,00,0;"));
//   sDisplay.runCommands(F("#f8b9;rh5,20,20,30;"));
//   sDisplay.runCommands(F("#17de;rf5,60,20,30;"));
//   sDisplay.runCommands(F("#17cb;ri30,20,20,30,4;"));
//   sDisplay.runCommands(F("#18bf;rj30,60,20,30,4;"));
//   sDisplay.runCommands(F("#17d4;gh15,120,5,110,25,110;"));
//   sDisplay.runCommands(F("#fe42;gf35,120,25,110,55,120;"));
//   sDisplay.runCommands(F("cb50,25,80,70,300,360,00f5,00,1;"));
//   sDisplay.runCommands(F("ci65,35,13,77e0,0;"));
//   sDisplay.runCommands(F("cj65,75,13,07e5,0;"));
//   sDisplay.runCommands(F("rs70,60,5,8,20,30,f820,0;"));
//   sDisplay.runCommands(F("rt80,100,20,20,5,fde0,0;"));

//   // display.fillScreen(TFT_BLACK);
//   // display.fillRectHGradient(10,50,50,50,0x72ff,0xd2ff);
// }

// void loop(void)
// {

//   sDisplay.readCommandsFromSerial();
// }