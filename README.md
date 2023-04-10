# Display Prototyping for Adafruit GFX and TFT eSPI 

## Display supported
All display supported by Adafruit GFX and TFT eSPI libraries

## Commands

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


