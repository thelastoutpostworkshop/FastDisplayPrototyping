// GFX Test

#include <Adafruit_TFTLCD.h>  // Hardware-specific library
#include <Adafruit_GFX.h>     // Core graphics library
#define OUTPUT_CODE_ON_SERIAL // Output graphical functions on the Serial Monitor, comment it to disable
#include "src/FastDisplayPrototyping.h"

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Initialize the display
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Initialize the display prototyping library
FastSerialDisplay sDisplay(&tft, "tft");

void setup()
{
  Serial.begin(9600); // This line mandatory for using the display prototyping library, change the baud rate if needed

  tft.begin();
  tft.setRotation(0);

  // Test 1
  // sDisplay.runCommands(F("x;ro3;#6f5e;sc77,10;ts2;ttDisplay Prototyping;"));
  // sDisplay.runCommands(F("dl10,10,h,w;lh70,30,235;lv70,8,23;"));
  // sDisplay.runCommands(F("#ff00;dp100,10;"));
  // sDisplay.runCommands(F("#0f83;ch280,60,20;#daad;cf280,60,15;"));
  // sDisplay.runCommands(F("#ffe0;rh200,45,40,30;#f6cb;rf205,50,30,20;"));
  // sDisplay.runCommands(F("#f81f;ri200,90,40,30,8;#f014;rj205,95,30,20,5;"));
  // sDisplay.runCommands(F("#fbe0;gh250,100,300,100,277,140;#dd24;gf260,105,290,105,277,130;"));

  // Test 2
  // sDisplay.runCommands(F("x;ro3;#3666;lv12,0,h;lv70,0,h;lv118,0,h;lv176,0,h;lv244,0,h;lv300,0,h;"));
  // sDisplay.runCommands(F("#07e0;ch70,m,70;ch70,m,50;ch70,m,15;ch70,m,6;"));
  // sDisplay.runCommands(F("#3666;dl25,0,142,h;#3666;dl111,0,0,h;#3666;dl70,0,70,h;"));
  // sDisplay.runCommands(F("#ffff;ri2,200,10,20,3;ri15,200,10,20,3;;ri28,200,10,20,3;"));
  // sDisplay.runCommands(F("ri80,200,30,20,3;ri180,200,10,20,3;"));
  // sDisplay.runCommands(F("ri265,200,10,20,3;ri280,200,10,20,3;"));
  // sDisplay.runCommands(F("#F7be;ch250,35,25;sc240,43;ttx1c;"));
  // sDisplay.runCommands(F("#ffff;gf60,65,60,75,50,70;gf100,95,100,105,90,100;"));
  // sDisplay.runCommands(F("gh30,120,40,125,30,130;gf40,180,40,190,30,185;"));

  // Draw commands
  // tft.fillScreen(0x0);
  // tft.setRotation(3);
  // tft.setTextColor(0x3666);
  // tft.drawFastVLine(12, 0, 320, 0x3666);
  // tft.drawFastVLine(70, 0, 320, 0x3666);
  // tft.drawFastVLine(118, 0, 320, 0x3666);
  // tft.drawFastVLine(176, 0, 320, 0x3666);
  // tft.drawFastVLine(244, 0, 320, 0x3666);
  // tft.drawFastVLine(300, 0, 320, 0x3666);
  // tft.drawLine(25, 0, 142, 320, 0x3666);
  // tft.drawLine(111, 0, 0, 320, 0x3666);
  // tft.drawLine(70, 0, 70, 320, 0x3666);
  // tft.setTextColor(0x7e0);
  // tft.drawCircle(70, 120, 70, 0x7e0);
  // tft.drawCircle(70, 120, 50, 0x7e0);
  // tft.drawCircle(70, 120, 15, 0x7e0);
  // tft.drawCircle(70, 120, 6, 0x7e0);
  // tft.setTextColor(0xffff);
  // tft.drawRoundRect(2, 200, 10, 20, 3, 0xffff);
  // tft.drawRoundRect(15, 200, 10, 20, 3, 0xffff);
  // tft.drawRoundRect(28, 200, 10, 20, 3, 0xffff);
  // tft.drawRoundRect(80, 200, 30, 20, 3, 0xffff);
  // tft.drawRoundRect(180, 200, 10, 20, 3, 0xffff);
  // tft.drawRoundRect(265, 200, 10, 20, 3, 0xffff);
  // tft.drawRoundRect(280, 200, 10, 20, 3, 0xffff);
  // tft.drawCircle(250, 35, 25, 0xf7be);
  // tft.drawCircle(30,87,10,0xf7be);
  // tft.setCursor(240, 43);
  // tft.print("x1c");
  // tft.fillTriangle(60, 65, 60, 75, 50, 70, 0xffff);
  // tft.fillTriangle(100, 95, 100, 105, 90, 100, 0xffff);
  // tft.drawTriangle(30,120,40,125,30,130,0xffff);
  // tft.fillTriangle(40,180,40,190,30,185,0xffff);

  // Test 3
  // sDisplay.runCommands(F("x;#ffff;y;ro3;#03d6;rf23,23,60,60;#07ff;rf20,20,60,60;"));
  // sDisplay.runCommands(F("#ded8;cf133,53,30;#07f9;cf130,50,30;"));
  // sDisplay.runCommands(F("#ded8;gf183,23,263,23,223,83;#f840;gf180,20,260,20,220,80;"));
  // sDisplay.runCommands(F("sc15,90;ts2;#fb39;ttSquare;"));
  // sDisplay.runCommands(F("sc100,90;ts2;#53e5;ttCircle;"));
  // sDisplay.runCommands(F("#981f;lh0,m,h;"));

  // Draw Commands
  tft.fillScreen(0x0);
  tft.setTextColor(0xffff);
  tft.fillScreen(0xffff);
  tft.setRotation(3);
  tft.setTextColor(0x3d6);
  tft.fillRect(23, 23, 60, 60, 0x3d6);
  tft.setTextColor(0x7ff);
  tft.fillRect(20, 20, 60, 60, 0x7ff);
  tft.setTextColor(0xded8);
  tft.fillCircle(133, 53, 30, 0xded8);
  tft.setTextColor(0x7f9);
  tft.fillCircle(130, 50, 30, 0x7f9);
  tft.setTextColor(0xded8);
  tft.fillTriangle(183, 23, 263, 23, 223, 83, 0xded8);
  tft.setTextColor(0xf840);
  tft.fillTriangle(180, 20, 260, 20, 220, 80, 0xf840);
  tft.setCursor(15, 90);
  tft.setTextSize(2);
  tft.setTextColor(0xfb39);
  tft.print("Square");
  tft.setCursor(100, 90);
  tft.setTextSize(2);
  tft.setTextColor(0x53e5);
  tft.print("Circle");
  tft.setTextColor(0x981f);
  tft.drawFastHLine(0, 120, 320, 0x981f);
  tft.setCursor(180, 90);
  tft.setTextSize(2);
  tft.setTextColor(0x401f);
  tft.print("Triangle");
}

void loop(void)
{
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