# Fast Display Prototyping for Adafruit GFX and TFT_eSPI
**Streamline your development process!** This library enables rapid prototyping of graphical functions by utilizing the Arduino IDE's serial monitor to communicate via the serial port with any display supported by Adafruit GFX and TFT_eSPI libraries. By eliminating the need for time-consuming microcontroller uploads when testing graphical functions, developers can focus on refining their designs more efficiently. 

### Tutorial

### Usage
Simply use the serial monitor to send graphical commands to your microcontroller, in the example below the commands `x;sc0,0,ttHello World!` when sent will clear the display and show Hello World! Make sure the option **No Line Endind** is selected in the Serial Monitor.
![Usage](https://github.com/thelastoutpostworkshop/DisplayPrototyping/blob/main/images/usage_serial_monitor.png)

### Type of Displays supported
All display supported by Adafruit GFX and TFT_eSPI libraries

## Contents
1. [Installation](#installation)
2. [Code Setup Adafruit GFX](#code-setup-adafruit-gfx)
3. [Code Setup TFT_eSPI](#code-setup-tft_espi)
4. [Examples](#examples)
5. [Serial Commands Reference](#serial-commands-reference)

### Installation
To get started, download the source code (zip) [the latest release](https://github.com/thelastoutpostworkshop/DisplayPrototyping/releases/latest). Then install the library in the Arduino IDE with the menu `Sketch > Include Library > Add ZIP Library`.

### Code Setup Adafruit GFX
>ℹ️ You can also use get this setup code with the examples provided with the library in the Arduino IDE through the menu `File > Examples > FastDisplayPrototyping`

```c
#include <Adafruit_TFTLCD.h>    // Hardware-specific library
#include <Adafruit_GFX.h>       // Core graphics library
#define OUTPUT_CODE_ON_SERIAL   // Output graphical functions used for the display
#include <FastDisplayPrototyping.h>

// Follow your display driver documentation
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Initialize the display prototyping library
serialDisplay sDisplay(&tft);

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
```

### Code Setup TFT_eSPI
>ℹ️ You can also use get this setup code with the examples provided with the library in the Arduino IDE through the menu `File > Examples > FastDisplayPrototyping`

```c
#include <TFT_eSPI.h>                 // Core graphics library
#define OUTPUT_CODE_ON_SERIAL         // Output graphical functions used for the display
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
```
### Examples
>ℹ️ You can send multiple graphical commands through the Serial Monitor by seperating them with a semi-colon `;` <br>

| Type this in the Serial Monitor | Result on the display |
|---------|-------------|
|x;sc10,10;thVertical Center | Clear screen & Text Centered vertically on row 10 |
|x;#ffe0;cf50,60,10 | Clear screen & Yellow filled circle at position 50,60 radius of 10 |
|x;#00ff;ri10,10,40,40,10 | Clear screen & Blue rounded rectangle outline at position 10,10, width 40, height 40, corner radius 10 |

### Serial Commands Reference
>ℹ️ You can replace any numeric value with **w** or **h** and it will be replaced by the width or the height of the display, for example `lh10,10,w`<br>
>ℹ️ For most serial commands, you don't need to specify a color, as they will use the current color set by the `#` serial command. This reduces the amount of typing needed<br>
>ℹ️ For colors you can use this [RGB565 Color Picker](http://www.barth-dev.de/online/rgb565-color-picker/#) (There are many others on the web)

| Graphical function | Corresponding Serial Command Example | Description | Adafruit GFX | TFT_eSPI |
|--------------------|---------------------------------------|-------------|:--------------:|:----------:|
| **Text Functions** |                                       |             |              |          |
| setTextColor(color) | #00FF | Set Text and Graphic `color` | ✓ | ✓ |
| setCursor(x,y) | **sc**10,20 | Set the text cursor at position `x`,`y`| ✓ | ✓ |
| print(string) | **tt**Hello World! | Print `string` at current cursor position | ✓ | ✓ |
| setTextSize(size) | **ts**3 | Set character `size` multiplier (increases pixel size) | ✓ | ✓ |
| **Basic Drawing Functions** |                                 |             |              |          |
| drawPixel(x,y,color) | **dp**10,10 | Draw a pixel at position `x`,`y` using the current color | ✓ | ✓ |
| drawLine(x1,y1,x2,y2) | **dl**10,10,50,50 | Draw a line between 2 points `(x1,y1,x2,y2)` using the current color | ✓ | ✓ |
| **Circle Functions** |                                       |             |              |          |
| drawCircle(x,y,r,color) | **ch**50,50,30 | Draw a circle outline at position `x`,`y` of radius `r` using the current color | ✓ | ✓ |
| fillCircle(x,y,r,color) | **cf**50,50,30 | Draw a filled circle at position `x`,`y` of radius `r` using the current color  | ✓ | ✓ |
| **Rectangle Functions** |                                    |             |              |          |
| drawRect(x,y,w,h,color) | **rh**20,20,40,30 | Draw a rectangle outline at position `x`,`y` of width `w` and height `h` using the current color | ✓ | ✓ |
| fillRect(x,y,w,h,color) | **rf**20,20,40,30 | Draw a filled rectangle at position `x`,`y` of width `w` and height `h` using the current color | ✓ | ✓ |
| **Rounded Rectangle Functions** |                             |             |              |          |
| drawRoundRect<br>(x,y,w,h,r,color) | **ri**20,20,40,30,5 | Draw a rounded corner rectangle outline at position `x`,`y` of width `w`, height `h` and radius `r` using the current color | ✓ | ✓ |
| fillRoundRect<br>(x,y,w,h,r,color) | **rj**20,20,40,30,5 | Draw a filled rounded corner rectangle at position `x`,`y` of width `w`, height `h` and radius `r` using the current | ✓ | ✓ |
| **Triangle Functions** |                                     |             |              |          |
| drawTriangle<br>(x1,y1,x2,y2,x3,y3,color) | **gh**10,10,20,20,30,10 | Draw a triangle outline using 3 points `x1,y1,x2,y2,x3,y3` (vertices) using the current color | ✓ | ✓ |
| fillTriangle<br>(x1,y1,x2,y2,x3,y3,color) | **gf**10,10,20,20,30,10 | Draw a filled triangle using 3 points `x1,y1,x2,y2,x3,y3` (vertices) using the current color| ✓ | ✓ |

### Using the Serial Commands in Code

### Configuration

### Library Behavior

### Library Size
