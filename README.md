### Commands

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
| **rh**[x,y,width,height] | Draw a hollow rectangle | **rh**20,20,40,30 | ✓ | ✓ |
| **rf**[x,y,width,height] | Draw a filled rectangle | **rf**20,20,40,30 | ✓ | ✓ |
| **ri**[x,y,width,height,radius] | Draw a hollow rounded rectangle | **ri**20,20,40,30,5 | ✓ | ✓ |
| **rj**[x,y,width,height,radius] | Draw a filled rounded rectangle | **rj**20,20,40,30,5 | ✓ | ✓ |
| **sc**[x,y] | Set cursor position | **sc**10,20 | ✓ | ✓ |
| **lv**[x,y,length] | Draw a fast vertical line | **lv**50,50,20 | ✓ | ✓ |
| **lh**[x,y,length] | Draw a fast horizontal line | **lh**50,50,20 | ✓ | ✓ |
| **dl**[x1,y1,x2,y2] | Draw a line | **dl**10,10,50,50 | ✓ | ✓ |
| **ro**[number] | Set Rotation (0-3 or 4-7 for BMP drawing) | **ro**1 | ✓ | ✗ |


