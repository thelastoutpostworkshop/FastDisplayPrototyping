### Available Commands

| Command | Description | Usage | Adafruit GFX | TFT_eSPI |
|---------|-------------|-------|--------------|------|
| tt[string]      | Print text | ttHello World! | None |   Yes | Yes |


| tv      | Print text centered vertically | tv | None | tvHello World! | Yes | Yes |
| th      | Print text centered horizontally | th | None | thHelloWorld! | Yes | Yes |
| ts      | Settext size | ts<number> | number: 1-9 | ts3 | Yes | Yes |
| ch      | Draw a hollow circle | ch<x>,<y>,<radius> | x, y: coordinates; radius: circle radius | ch50,50,30 | Yes | Yes |
| cf      | Draw a filled circle | cf<x>,<y>,<radius> | x, y: coordinates; radius: circle radius | cf50,50,30 | Yes | Yes |
| gh      | Set mode to hollow triangle (TRIANGLE_HOLLOW) | gh<x1><y1><x2><y2><x3><y3> | x1, y1, x2, y2, x3, y3: triangle vertices coordinates | gh10,10,20,20,30,10 | Yes | Yes |
| gf      | Set mode to filled triangle (TRIANGLE_FILL) | gf<x1><y1><x2><y2><x3><y3> | x1, y1, x2, y2, x3, y3: triangle vertices coordinates | gf10,10,20,20,30,10 | Yes | Yes |
| rh      | Set mode to hollow rectangle (RECTANGLE_HOLLOW) | rh<x><y><width><height> | x, y: coordinates; width, height: rectangle dimensions | rh20,20,40,30 | Yes | Yes |
| rf      | Set mode to filled rectangle (RECTANGLE_FILL) | rf<x><y><width><height> | x, y: coordinates; width, height: rectangle dimensions | rf20,20,40,30 | Yes | Yes |
| ri      | Set mode to hollow rounded rectangle (RECTANGLE_ROUND_HOLLOW) | ri<x><y><width><height><radius> | x, y: coordinates; width, height: rectangle dimensions; radius: corner radius | ri20,20,40,30,5 | Yes | Yes |
| rj      | Set mode to filled rounded rectangle (RECTANGLE_ROUND_FILL) | rj<x><y><width><height><radius> | x, y: coordinates; width, height: rectangle dimensions; radius: corner radius | rj20,20,40,30,5 | Yes | Yes |
| sc      | Set mode to set cursor (SET_CURSOR) | sc<x><y> | x, y: coordinates | sc10,20 | Yes | Yes |
| lv      | Set mode to fast vertical line (LINE_FAST_VERTICAL) | lv<x><y><length> | x, y: coordinates; length: line length | lv50,50,20 | Yes | Yes |
| lh      | Set mode to fast horizontal line (LINE_FAST_HORIZONTAL) | lh<x><y><length> | x, y: coordinates; length: line length | lh50,50,20 | Yes | Yes |
| dl  | Set mode to line (LINE) | dl<x1><y1><x2><y2> | x1, y1, x2, y2: line endpoints coordinates | dl10,10,50,50 | Yes | Yes |
| ro | Set mode to rotate (ROTATE) | ro<angle> | angle: rotation angle in degrees | ro90 | Yes | No |
   

### Function Descriptions

- `serialDisplay::captureCommand(char input)`
  - Captures commands and sets the current mode.
  - Processes the input character and matches it with the available commands.
  - Calls the respective functions based on the matched command.

- `boolean serialDisplay::isCommand(const char *command)`
  - Checks if the given command matches the captured command.

- `void serialDisplay::decodeInput(char input)`
  - Decodes the input character and processes it according to the current mode.

- `void serialDisplay::readCommandsFromSerial(void)`
  - Reads commands from the serial
