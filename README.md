# Fast Display Prototyping for Adafruit GFX and TFT_eSPI
**Streamline your development process!** This library enables rapid prototyping of graphical functions by utilizing the Arduino IDE's serial monitor to communicate via the serial port with any display supported by Adafruit GFX ![GFX] and TFT_eSPI libraries ![ESPI]. 
It eliminates the need for time-consuming microcontroller uploads when testing graphical functions, you can focus on refining your designs more efficiently. 

### Tutorial

### Usage
Simply use the serial monitor to send graphical commands to your microcontroller, in the example below the commands `x;sc0,0;ttHello World!` when sent will clear the display and show Hello World! Make sure the option **No Line Endind** is selected in the Serial Monitor.
![Usage](https://github.com/thelastoutpostworkshop/DisplayPrototyping/blob/main/images/usage_serial_monitor.png)

### Type of Displays supported
All display supported by Adafruit GFX and TFT_eSPI libraries

## Contents
1. [Installation](#installation)
2. [Code Setup Adafruit GFX](#code-setup-adafruit-gfx) ![GFX]
3. [Code Setup TFT_eSPI](#code-setup-tft_espi) ![ESPI]
4. [Examples](#examples)
5. [Serial Commands Reference](#serial-commands-reference)
6. [Using Fonts](#using-fonts)
7. [Library Configuration](#library-configuration)
8. [Library Size](#library-size)
9. [Serial Buffer Limitation](#serial-buffer-limitation-on-arduino-uno-and-nano)

### Installation
To get started, download the source code (zip) [the latest release](https://github.com/thelastoutpostworkshop/DisplayPrototyping/releases/latest). Then install the library in the Arduino IDE with the menu `Sketch > Include Library > Add ZIP Library`.

### Code Setup Adafruit GFX ![GFX]
>ℹ️ You can also use get this setup code with the examples provided with the library in the Arduino IDE through the menu `File > Examples > FastDisplayPrototyping`

```c
// Core graphics library
#include <Adafruit_GFX.h>     

// -- Hardware-specific library & Definitions Section
// -- Change this section according to your type of display
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
```

### Code Setup TFT_eSPI ![ESPI]
>ℹ️ You can also use get this setup code with the examples provided with the library in the Arduino IDE through the menu `File > Examples > FastDisplayPrototyping`

```c
// Core graphics library
// Don't forget to select the driver of your display in the User_Setup.h file 
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
```
### Examples
>ℹ️ You can send multiple graphical commands through the Serial Monitor by seperating them with a semi-colon `;` <br>

| Type this in the Serial Monitor | Result on the display |
|---------|-------------|
|x;sc10,10;ttHello World! | Clear screen & print text on row 10 |
|x;#ffe0;cf50,60,10 | Clear screen & Yellow filled circle at position 50,60 radius of 10 |
|x;#077f;ri10,10,40,40,10 | Clear screen & Blue rounded rectangle outline at position 10,10, width 40, height 40, corner radius 10 |

### Serial Commands Reference
>ℹ️ You can replace any numeric value with `w`, `h`, `c` or `m` and it will be replaced by the width, the height, half of the height or half of the width of the display respectively.  For example `lhc,10,w`<br>
>ℹ️ For most serial commands, you don't need to specify a color, as they will use the current color set by the `#` serial command. This reduces the amount of typing needed<br>
>ℹ️ Color format is **RGB565**, you can use this [Color Name Defintions Reference](https://github.com/newdigate/rgb565_colors) or  [RGB565 Color Picker](http://www.barth-dev.de/online/rgb565-color-picker/#) (There are many others on the web)<br>
>ℹ️ A graphical function supported by Adafruit GFX is indicated with ![GFX] and supported by TFT_eSPI is indicated with ![ESPI]

| Graphics functions | Corresponding Serial Command Example | Description | 
|--------------------|---------------------------------------|-------------|
| **Text Functions** |                                       |             |  
| setTextColor(color)<br>![GFX]![ESPI] | #00FF | Set Text and Graphic `color` | ✓ | ✓ |
| setCursor(x,y)<br>![GFX]![ESPI] | **sc**10,20 | Set the text cursor at position `x`,`y`| 
| print(string)<br>![GFX]![ESPI] | **tt**Hello World! | Print `string` at current cursor position using the current font | 
| setTextSize(size)<br>![GFX]![ESPI] | **ts**3 | Set character `size` multiplier (increases pixel size) |
| **Basic Drawing Functions** |                                 |             |              
| fillScreen(0x0000)<br>![GFX]![ESPI] | **x** | Clear the screen to black |
| drawPixel(x,y,color)<br>![GFX]![ESPI] | **dp**10,10 | Draw a pixel at position `x`,`y` using the current color |
| drawLine(x1,y1,x2,y2)<br>![GFX]![ESPI] | **dl**10,10,50,50 | Draw a line between 2 points `(x1,y1,x2,y2)` using the current color | 
| drawFastHLine(x,y,l,color)<br>![GFX]![ESPI] | **lh**20,30,100 | Draw a horizontal line from position `x`,`y` of length `l` using the current color | 
| drawFastVLine(x,y,l,color)<br>![GFX]![ESPI] | **lv**20,30,100 | Draw a vertical line from position `x`,`y` of length `l` using the current color | 
| **Circle Functions** |                                       |             |              
| drawCircle(x,y,r,color)<br>![GFX]![ESPI] | **ch**50,50,30 | Draw a circle outline with the center at position `x`,`y` of radius `r` using the current color | 
| fillCircle(x,y,r,color)<br>![GFX]![ESPI] | **cf**75,50,30 | Draw a filled circle with the center at position `x`,`y` of radius `r` using the current color  | 
| drawSmoothCircle(x,y,r,fgColor,bgColor)<br>![ESPI] | **ci**65,35,13,77e0,0 | Draw an anti-aliased circle outline with the center at position `x`,`y` of radius `r` using a foreground color `fgColor` background color `bgColor` | 
| fillSmoothCircle(x,y,r,fgColor,bgColor)<br>![ESPI] | **cj**65,75,13,07e5,0 | Draw an anti-aliased filled circle with the center at position `x`,`y` of radius `r` using a foreground color `fgColor` background color `bgColor` | 
| drawEllipse(x,y,r1,r2,color)<br>![ESPI] | **ce**75,75,25,50 | Draw an ellipse outline with the center at position `x`,`y` of horizontal radius `r1` and vertical radius `r2` using the current color  |
| fillEllipse(x,y,r1,r2,color)<br>![ESPI] | **cg**75,75,25,50 | Draw a filled ellipse with the center at position `x`,`y` of horizontal radius `r1` and vertical radius `r2` using the current color  | 
| drawArc(x,y,r1,r2,startAngle,endAngle,<br>fgColor,bgColor,smoothArc)<br>![ESPI] | **ca**50,50,50,40,0,<br>180,00ff,0000,1 | Draw an arc with the center at position `x`,`y` outer radius of `r1` inner radius of `r2` starting at angle (in degrees) `startAngle` ending at `endAngle` using a foreground color `fgColor` background color `bgColor` and with anti-aliasing (smoothArc=`1`) or no anti-aliasing (smoothArc=`0`).  The start angle may be larger than the end angle. Arcs are always drawn clockwise from the start angle.| 
| drawSmoothArc(x,y,r1,r2,startAngle,endAngle,<br>fgColor,bgColor,roundEnds)<br>![ESPI] | **cb**50,50,50,40,0,<br>180,00ff,0000,1 | Draw an anti-aliased (smooth) arc with the center at position `x`,`y` outer radius of `r1` inner radius of `r2` starting at angle (in degrees) `startAngle` ending at `endAngle` using a foreground color `fgColor` background color `bgColor` and with round ends (roundEnds=`1`) or square ends(roundEnds=`0`). The start angle may be larger than the end angle. Arcs are always drawn clockwise from the start angle.| 
| **Rectangle Functions** |                                    |             |              
| drawRect(x,y,w,h,color)<br>![GFX]![ESPI]  | **rh**20,20,40,30 | Draw a rectangle outline at position `x`,`y` of width `w` and height `h` using the current color | 
| fillRect(x,y,w,h,color)<br>![GFX]![ESPI]  | **rf**20,20,40,30 | Draw a filled rectangle at position `x`,`y` of width `w` and height `h` using the current color | 
| drawRoundRect<br>(x,y,w,h,r,color)<br>![GFX]![ESPI]  | **ri**20,20,40,30,5 | Draw a rounded corner rectangle outline at position `x`,`y` of width `w`, height `h` and radius `r` using the current color | 
| fillRoundRect<br>(x,y,w,h,r,color)<br>![GFX]![ESPI] | **rj**20,20,40,30,5 | Draw a filled rounded corner rectangle at position `x`,`y` of width `w`, height `h` and radius `r` using the current | 
| drawSmoothRoundRect(x,y,r,ir,w,h,<br>fgColor,bgColor)<br>![ESPI]  | **rs**70,60,5,8,20,30,f820,0 | Draw an anti-aliased rounded corner rectangle outline at position `x`,`y` radius outer corner of `r`, radius inner corner `ir`, of width `w`, height `h`using a foreground color `fgColor` background color `bgColor`. The rectangle that has a line thickness of r-ir+1 | 
| fillSmoothRoundRect(x,y,w,h,r,<br>fgColor,bgColor)<br>![ESPI]  | **rt**80,100,20,20,5,fde0,0 | Draw an anti-aliased filled rounded corner rectangle at position `x`,`y`, width `w`, height `h`, corner radius of `r` using a foreground color `fgColor` background color `bgColor`. | 
| **Triangle Functions** |                                     |             |              
| drawTriangle<br>(x1,y1,x2,y2,x3,y3,color)<br>![GFX]![ESPI]  | **gh**10,10,20,20,30,10 | Draw a triangle outline using 3 points `x1,y1,x2,y2,x3,y3` (vertices) using the current color | 
| fillTriangle<br>(x1,y1,x2,y2,x3,y3,color)<br>![GFX]![ESPI]  | **gf**10,10,20,20,30,10 | Draw a filled triangle using 3 points `x1,y1,x2,y2,x3,y3` (vertices) using the current color| 

### Using Fonts
The library utilizes the currently defined font in the code. Support for handling multiple preloaded fonts is planned for the upcoming release of the library.

### Library Configuration
By default, the graphical commands corresponding to the serial commands sent are displayed in the Serial Monitor, allowing you to easily copy and paste them into your code. If you wish to disable this feature and reduce the library size, you can comment out this definition:
```c
// #define OUTPUT_CODE_ON_SERIAL  
```
To facilitate the process of copying graphical commands into your code, you can initialize the library using the variable that represents the display in your code. For instance, if you have a variable named "display" for the display in your code, you can initialize the library as follows:<br><br>
![ESPI]
```c
// Initialize the display
TFT_eSPI tft = TFT_eSPI(); 

// Initialize the display prototyping library
serialDisplay sDisplay(&tft);
```

![GFX]
```c
// Initialize the display
Adafruit_TFTLCD display(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Initialize the display prototyping library
serialDisplay sDisplay(&tft,"display"); 
```
All the graphical commands will be preceded by the "display" keyword, for example `display.fillSmoothRoundRect(80,100,20,20,5,0xfde0,0x0);`

### Library Size
The library utilizes a wide range of graphical functions, which can pose a challenge for microcontrollers with limited memory, such as the Arduino Uno or Nano. In such cases, you can use the library within an empty sketch to prototype your designs and then copy the code output from the Serial Monitor into your main sketch. This approach helps you avoid potential memory issues while still benefiting from the library's functionality.

[GFX]: https://img.shields.io/badge/GFX-green
[ESPI]: https://img.shields.io/badge/eSPI-blue

### Serial Buffer Limitation
**Arduino Uno and Nano**, both equipped with the **ATmega328P microcontroller**, have a default serial buffer size of **64 bytes**.  When sending data through the Serial Monitor it is crucial to be aware of this limitation, as attempting to send a message larger than 64 bytes can lead to data loss or unexpected behavior.

On the **ESP32**, the default serial buffer size is typically set to **256 bytes**.