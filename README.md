### Available Commands

| Command | Description | Usage | Arguments | Adafruit GFX | espi |
|---------|-------------|-------|-----------|--------------|------|
| tt      | Set mode to text (TEXT) | tt | None | Yes | Yes |
| tv      | Set mode to text centered vertically (TEXT_CENTER_VERTICAL) | tv | None | Yes | Yes |
| th      | Set mode to text centered horizontally (TEXT_CENTER_HORIZONTAL) | th | None | Yes | Yes |
| ts      | Set mode to text size (TEXT_SIZE) | ts<size> | size: 1-9 | Yes | Yes |
| ch      | Set mode to hollow circle (CIRCLE_HOLLOW) | ch<x><y><radius> | x, y: coordinates; radius: circle radius | Yes | Yes |
| cf      | Set mode to filled circle (CIRCLE_FILL) | cf<x><y><radius> | x, y: coordinates; radius: circle radius | Yes | Yes |
| gh      | Set mode to hollow triangle (TRIANGLE_HOLLOW) | gh<x1><y1><x2><y2><x3><y3> | x1, y1, x2, y2, x3, y3: triangle vertices coordinates | Yes | Yes |
| gf      | Set mode to filled triangle (TRIANGLE_FILL) | gf<x1><y1><x2><y2><x3><y3> | x1, y1, x2, y2, x3, y3: triangle vertices coordinates | Yes | Yes |
| rh      | Set mode to hollow rectangle (RECTANGLE_HOLLOW) | rh<x><y><width><height> | x, y: coordinates; width, height: rectangle dimensions | Yes | Yes |
| rf      | Set mode to filled rectangle (RECTANGLE_FILL) | rf<x><y><width><height> | x, y: coordinates; width, height: rectangle dimensions | Yes | Yes |
| ri      | Set mode to hollow rounded rectangle (RECTANGLE_ROUND_HOLLOW) | ri<x><y><width><height><radius> | x, y: coordinates; width, height: rectangle dimensions; radius: corner radius | Yes | Yes |
| rj      | Set mode to filled rounded rectangle (RECTANGLE_ROUND_FILL) | rj<x><y><width><height><radius> | x, y: coordinates; width, height: rectangle dimensions; radius: corner radius | Yes | Yes |
| sc      | Set mode to set cursor (SET_CURSOR) | sc<x><y> | x, y: coordinates | Yes | Yes |
| lv      | Set mode to fast vertical line (LINE_FAST_VERTICAL) | lv<x><y><length> | x, y: coordinates; length: line length | Yes | Yes |
| lh      | Set mode to fast horizontal line (LINE_FAST_HORIZONTAL) | lh<x><y><length> | x, y: coordinates; length: line length | Yes | Yes |
| dl      | Set mode to line (LINE) | dl<x1><y1><x2><y2> | x1, y1, x2, y2: line endpoints coordinates | Yes | Yes |
| ro      | Set mode to rotate (ROTATE) | ro<angle> | angle: rotation angle in degrees | Yes | No |

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
