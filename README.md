# Fast Display Prototyping for Adafruit GFX and TFT eSPI
**Streamline your development process!** This library enables rapid prototyping of graphical functions by utilizing the Arduino IDE's serial monitor to communicate via the serial port with any display supported by Adafruit GFX and TFT_eSPI libraries. By eliminating the need for time-consuming microcontroller uploads when testing graphical functions, developers can focus on refining their designs more efficiently. 

### Tutorial

### Usage
Simply use the serial monitor to send graphical commands to your microcontroller, in the example below the commands `x;sc0,0,ttHello World!` sent will clear the display and show Hello World! Make sure the option **No Line Endind** is selected in the Serial Monitor.
![Usage](https://github.com/thelastoutpostworkshop/DisplayPrototyping/blob/main/images/usage_serial_monitor.png)

### Type of Displays supported
All display supported by Adafruit GFX and TFT_eSPI libraries

## Contents
1. [Installation](#installation)
2. [Code Setup Adafruit GFX](#code-setup-adafruit-gfx)
3. [Code Setup TFT_eSPI](#code-setup-tft-espi)
4. [Examples](#examples)
5. [Serial Commands](#serial-commands)

### Installation
To get started, download the source code (zip) [the latest release](https://github.com/thelastoutpostworkshop/DisplayPrototyping/releases/latest). Then install the library in the Arduino IDE with the menu `Sketch > Include Library > Add ZIP Library`.

### Code Setup Adafruit GFX
(You can also use the examples provided with the library in the Arduino IDE through the menu `File > Examples > FastDisplayPrototyping`

```c
#include <Adafruit_TFTLCD.h> 
#include <Adafruit_GFX.h>
#define OUTPUT_CODE_ON_SERIAL     // Corresponding code output to Serial Monitor
#include <DisplayPrototyping.h> // Display Protyping Library

// Follow your display driver documentation
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Initialize the display prototyping library
serialDisplay sDisplay(&tft);

void setup() {
  Serial.begin(9600); // This line mandatory for using the display prototyping library

  tft.begin();
  tft.setRotation(0);

  // Your specific code here
}

void loop(void) {
  sDisplay.readCommandsFromSerial();  // This line mandatory for using the display prototyping library, change the baud rate if needed

  // Your specific code here
}
```

### Code Setup TFT_eSPI
(You can also use the examples provided with the library in the Arduino IDE through the menu `File > Examples > FastDisplayPrototyping`

```c
#include <TFT_eSPI.h>
#define OUTPUT_CODE_ON_SERIAL     // Corresponding code output to Serial Monitor
#include "DisplayPrototyping.h"

// Follow your display driver documentation
TFT_eSPI tft = TFT_eSPI(); 

void setup() {
  Serial.begin(9600); //  // This line mandatory for using the display prototyping library, change the baud rate if needed

  tft.begin();
  tft.setRotation(0);

  // Your specific code here
}

void loop(void) {
  sDisplay.readCommandsFromSerial(); // This line mandatory for using the display prototyping library
  
  // Your specific code here
}
```
### Examples
For colors you can use this [RGB565 Color Picker](http://www.barth-dev.de/online/rgb565-color-picker/#)

| Type this in the Serial Monitor | Result on the display |
|---------|-------------|
|x;sc10,10;thVertical Center | Clear screen & Text Centered vertically on row 10 |
|x;#ffe0;cf50,60,10 | Clear screen & Yellow filled circle at position 50,60 radius of 10 |
|x;#00ff;ri10,10,40,40,10 | Clear screen & Blue rounded rectangle outline at position 10,10, width 40, height 40, corner radius 10 |

### Serial Commands

| Command | Description | Usage | Adafruit GFX | TFT_eSPI |
|---------|-------------|-------|--------------|------|
| **tt**[string]| Print text | **tt**Hello World! | ✓  | ✓  |
| **tv**[string]| Print text centered vertically | **tv**Hello World! | ✓  | ✓  |
| **th**[string]| Print text centered horizontally | **th**Hello World! | ✓  | ✓  |
| **ts**[size] | Set text size | **ts**3 | ✓ | ✓ |
| **ch**[x,y,radius] | Draw a circle outline | **ch**50,50,30 | ✓ | ✓ |
| **cf**[x,y,radius] | Draw a filled circle | **cf**50,50,30 | ✓ | ✓ |
| **gh**[x1,y1,x2,y2,x3,y3] | Draw a triangle outline using 3 points (vertices) | **gh**10,10,20,20,30,10 | ✓ | ✓ |
| **gf**[x1,y1,x2,y2,x3,y3] | Draw a filled triangle using 3 points (vertices)| **gf**10,10,20,20,30,10 | ✓ | ✓ |
| **rh**[x,y,width,height] | Draw a rectangle outline | **rh**20,20,40,30 | ✓ | ✓ |
| **rf**[x,y,width,height] | Draw a filled rectangle | **rf**20,20,40,30 | ✓ | ✓ |
| **ri**[x,y,width,height,radius] | Draw a rounded corner rectangle outline | **ri**20,20,40,30,5 | ✓ | ✓ |
| **rj**[x,y,width,height,radius] | Draw a rounded corner filled rectangle | **rj**20,20,40,30,5 | ✓ | ✓ |
| **sc**[x,y] | Set the text cursor position | **sc**10,20 | ✓ | ✓ |
| **lv**[x,y,length] | Draw a vertical line | **lv**50,50,20 | ✓ | ✓ |
| **lh**[x,y,length] | Draw a horizontal line | **lh**50,50,20 | ✓ | ✓ |
| **dl**[x1,y1,x2,y2] | draw a line between 2 points | **dl**10,10,50,50 | ✓ | ✓ |
| **ro**[number] | Set rotation setting for display (0-3 or 4-7 for BMP drawing) | **ro**1 | ✓ | ✗ |


