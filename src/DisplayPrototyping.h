
#if defined(_ADAFRUIT_TFTLCD_H_)

#define DISP Adafruit_TFTLCD

#endif // _ADAFRUIT_TFTLCD_H_

// #include <TFT_eSPI.h>  // Hardware-specific library
#define MAX_DATA_CAPTURE 30
#define MAX_ARG_CAPTURE 6
#define COLOR_BLACK 0x0000
#define DEBOUNCE_READ_SERIAL 300

class serialDisplay
{
private:
  struct Capture
  {
    char capture[MAX_ARG_CAPTURE][MAX_DATA_CAPTURE];
    byte index[MAX_ARG_CAPTURE];
    byte argIndex;
    byte maxArg;
  };
  enum MODE
  {
    UNDEFINED,
    COMMAND,
    TEXT,
    TEXT_CENTER_HORIZONTAL,
    TEXT_CENTER_VERTICAL,
    TEXT_SIZE,
    CIRCLE_HOLLOW,
    CIRCLE_FILL,
    TRIANGLE_HOLLOW,
    TRIANGLE_FILL,
    RECTANGLE_HOLLOW,
    RECTANGLE_FILL,
    RECTANGLE_ROUND_HOLLOW,
    RECTANGLE_ROUND_FILL,
    LINE_FAST_VERTICAL,
    LINE_FAST_HORIZONTAL,
    LINE,
    FILL_SCREEN,
    DISPLAY_COLOR,
    CLEAR_SCREEN,
    SET_CURSOR,
    VERTICAL_LINE,
    ROTATE
  };

  DISP *display;
  MODE currentMode;
  Capture captureData;
  uint16_t currentColor = 0xFFFF;
  int displayWidth;
  int displayHeight;
  unsigned long lastSerialRead;

  void decodeInput(char input);
  void executeCommand(void);
  void captureInput(Capture *, char);
  void openCapture(Capture *, int);
  void closeCapture(Capture *);
  void nextArgCapture(Capture *);
  int *getIntFromCapture(Capture *, int);
  void captureCommand(char);
  boolean isCommand(const char *);

public:
  serialDisplay(DISP *d);
  ~serialDisplay();
  void readCommandsFromSerial(void);
  void runCommands(char *);
  void runCommands(const __FlashStringHelper *ifsh);
};

serialDisplay::serialDisplay(DISP *d)
{
  currentMode = UNDEFINED;
  display = d;
#if defined(_ADAFRUIT_TFTLCD_H_)

  displayWidth = d->width();
  displayHeight = d->height();

#endif //

  lastSerialRead = millis();
}

serialDisplay::~serialDisplay()
{
}

void serialDisplay::runCommands(char *commands)
{
  for (int i = 0; i < strlen(commands); i++)
  {
    decodeInput(*(commands + i));
  }
}
void serialDisplay::runCommands(const __FlashStringHelper *ifsh)
{
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0) break;
    decodeInput(c);
  }
}

int *serialDisplay::getIntFromCapture(Capture *capture, int count)
{
  static int res[MAX_ARG_CAPTURE];
  for (int i = 0; i < count && i < MAX_ARG_CAPTURE; i++)
  {
    res[i] = atoi(capture->capture[i]);
  }
  return res;
}

void serialDisplay::captureInput(Capture *capture, char input)
{
  if (capture->index[capture->argIndex] == MAX_DATA_CAPTURE)
  {
    Serial.println(F("Capture Max Reached"));
    capture->index[capture->argIndex] = 0;
  }
  capture->capture[capture->argIndex][capture->index[capture->argIndex]] = input;
  capture->index[capture->argIndex]++;
}

void serialDisplay::closeCapture(Capture *capture)
{
  capture->argIndex = 0;
  for (int i = 0; i < capture->maxArg; i++)
  {
    capture->capture[i][capture->index[i]] = 0;
  }
}
void serialDisplay::openCapture(Capture *capture, int maxArg)
{
  capture->argIndex = 0;
  capture->maxArg = maxArg;
  for (int i = 0; i < capture->maxArg; i++)
  {
    capture->index[i] = 0;
  }
}

void serialDisplay::nextArgCapture(Capture *capture)
{
  if (capture->argIndex >= capture->maxArg)
  {
    Serial.println(F("Capture Max Arg Reached"));
    capture->argIndex = 0;
  }
  else
  {
    capture->argIndex++;
  }
}

void serialDisplay::captureCommand(char input)
{
  captureInput(&captureData, input);
  closeCapture(&captureData);
  
  const char* commands[] = {"tt", "tv", "th", "ts", "ch", "cf", "gh", "gf", "rh", "rf", "ri", "rj", "sc", "lv", "lh", "dl","ro"};
  const int numCommands = sizeof(commands)/sizeof(*commands);

  for (int i = 0; i < numCommands; i++) {
    if (isCommand(commands[i])) {
      switch(i) {
        case 0:
          currentMode = TEXT;
          openCapture(&captureData, 1);
          break;
        case 1:
          currentMode = TEXT_CENTER_VERTICAL;
          openCapture(&captureData, 1);
          break;
        case 2:
          currentMode = TEXT_CENTER_HORIZONTAL;
          openCapture(&captureData, 1);
          break;
        case 3:
          currentMode = TEXT_SIZE;
          openCapture(&captureData, 1);
          break;
        case 4:
          currentMode = CIRCLE_HOLLOW;
          openCapture(&captureData, 3);
          break;
        case 5:
          currentMode = CIRCLE_FILL;
          openCapture(&captureData, 3);
          break;
        case 6:
          currentMode = TRIANGLE_HOLLOW;
          openCapture(&captureData, 6);
          break;
        case 7:
          currentMode = TRIANGLE_FILL;
          openCapture(&captureData, 6);
          break;
        case 8:
          currentMode = RECTANGLE_HOLLOW;
          openCapture(&captureData, 4);
          break;
        case 9:
          currentMode = RECTANGLE_FILL;
          openCapture(&captureData, 4);
          break;
        case 10:
          currentMode = RECTANGLE_ROUND_HOLLOW;
          openCapture(&captureData, 5);
          break;
        case 11:
          currentMode = RECTANGLE_ROUND_FILL;
          openCapture(&captureData, 5);
          break;
        case 12:
          currentMode = SET_CURSOR;
          openCapture(&captureData, 2);
          break;
        case 13:
          currentMode = LINE_FAST_VERTICAL;
          openCapture(&captureData, 3);
          break;
        case 14:
          currentMode = LINE_FAST_HORIZONTAL;
          openCapture(&captureData, 3);
          break;
        case 15:
          currentMode = LINE;
          openCapture(&captureData, 4);
          break;
        case 16:
          currentMode = ROTATE;
          openCapture(&captureData, 1);
          break;
        default:
          Serial.println(F("Unknown Command"));
          break;
      }
      return;
    }
  }
}

boolean serialDisplay::isCommand(const char *command)
{
  return strcmp(captureData.capture[0], command) == 0;
}

void serialDisplay::decodeInput(char input)
{
  if (input == ';')
  {
    executeCommand();
    return;
  }
  // Serial.println(currentMode);
  switch (currentMode)
  {
  case UNDEFINED:
    switch (input)
    {
    case '#':
      currentMode = DISPLAY_COLOR;
      openCapture(&captureData, 1);
      break;
    case 'x':
      currentMode = CLEAR_SCREEN;
      break;
    case 'y':
      currentMode = FILL_SCREEN;
      break;
    case 'd':
    case 'l':
    case 'r':
    case 'g':
    case 'c':
    case 't':
    case 's':
      currentMode = COMMAND;
      openCapture(&captureData, 1);
      captureInput(&captureData, input);
      break;
    default:
      Serial.print(F("Unknown input="));
      Serial.println(input);
      break;
    }
    break;
  case COMMAND:
    captureCommand(input);
    break;
  case TEXT_CENTER_VERTICAL:
  case TEXT_CENTER_HORIZONTAL:
  case TEXT:
    captureInput(&captureData, input);
    break;
  case SET_CURSOR:
    if (input == ',')
    {
      nextArgCapture(&captureData);
    }
    else
    {
      if (input >= '0' && input <= '9')
      {
        captureInput(&captureData, input);
      }
    }
    break;
  case LINE:
  case LINE_FAST_HORIZONTAL:
  case LINE_FAST_VERTICAL:
  case RECTANGLE_ROUND_FILL:
  case RECTANGLE_ROUND_HOLLOW:
  case RECTANGLE_FILL:
  case RECTANGLE_HOLLOW:
  case TRIANGLE_FILL:
  case TRIANGLE_HOLLOW:
  case CIRCLE_FILL:
  case CIRCLE_HOLLOW:
  case ROTATE:
    if (input == ',')
    {
      nextArgCapture(&captureData);
    }
    else
    {
      if (input >= '0' && input <= '9')
      {
        captureInput(&captureData, input);
      }
    }
    break;
  case DISPLAY_COLOR:
    if ((input >= '0' && input <= '9') || (input >= 'a' && input <= 'f') || (input >= 'A' && input <= 'F'))
    {
      captureInput(&captureData, input);
    }
    break;
  case TEXT_SIZE:
    if ((input >= '0' && input <= '9'))
    {
      captureInput(&captureData, input);
    }
    break;
  default:
    Serial.println(F("Unknown current mode"));
    break;
  }
}

void serialDisplay::readCommandsFromSerial(void)
{
  char input;
  if (Serial.available())
  {
    input = Serial.read();
    decodeInput(input);
    lastSerialRead = millis();
  }
  else
  {
    if (currentMode != UNDEFINED && millis() - lastSerialRead > DEBOUNCE_READ_SERIAL)
    {
      executeCommand();
      lastSerialRead = millis();
    }
  }
  delay(10);
}

void serialDisplay::executeCommand(void)
{
  int16_t x, y, x1, y1;
  uint16_t w, h;
  int *arg;

  if (currentColor == UNDEFINED)
  {
    return;
  }

  closeCapture(&captureData);
  switch (currentMode)
  {
  case DISPLAY_COLOR:
    currentColor = strtol(captureData.capture[0], NULL, 16);
    ;
    display->setTextColor(currentColor);
    break;
  case TEXT_SIZE:
    arg = getIntFromCapture(&captureData, 1);
    display->setTextSize(arg[0]);
    break;
  case TEXT:
    display->print(captureData.capture[0]);
    break;
  case TEXT_CENTER_HORIZONTAL:
#if defined(_ADAFRUIT_TFTLCD_H_)
    y = display->getCursorY();
    display->getTextBounds(captureData.capture[0], &x, &y, &x1, &y1, &w, &h);
    display->setCursor((displayWidth - w) / 2, y);
#endif // _ADAFRUIT_TFTLCD_H_
    display->print(captureData.capture[0]);
    break;
  case TEXT_CENTER_VERTICAL:
#if defined(_ADAFRUIT_TFTLCD_H_)
    x = display->getCursorX();
    display->getTextBounds(captureData.capture[0], &x, &y, &x1, &y1, &w, &h);
    display->setCursor(x, (displayHeight - h) / 2);
#endif // _ADAFRUIT_TFTLCD_H_
    display->print(captureData.capture[0]);

    break;
  case CLEAR_SCREEN:
    display->fillScreen(COLOR_BLACK);
    break;
  case FILL_SCREEN:
    display->fillScreen(currentColor);
    break;
  case SET_CURSOR:
    arg = getIntFromCapture(&captureData, 2);
    display->setCursor(arg[0], arg[1]);
    break;
  case CIRCLE_HOLLOW:
    arg = getIntFromCapture(&captureData, 3);
    display->drawCircle(arg[0], arg[1], arg[2], currentColor);
    break;
  case CIRCLE_FILL:
    arg = getIntFromCapture(&captureData, 3);
    display->fillCircle(arg[0], arg[1], arg[2], currentColor);
    break;
  case TRIANGLE_HOLLOW:
    arg = getIntFromCapture(&captureData, 6);
    display->drawTriangle(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], currentColor);
    break;
  case TRIANGLE_FILL:
    arg = getIntFromCapture(&captureData, 6);
    display->fillTriangle(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], currentColor);
    break;
  case RECTANGLE_HOLLOW:
    arg = getIntFromCapture(&captureData, 4);
    display->drawRect(arg[0], arg[1], arg[2], arg[3], currentColor);
    break;
  case RECTANGLE_FILL:
    arg = getIntFromCapture(&captureData, 4);
    display->fillRect(arg[0], arg[1], arg[2], arg[3], currentColor);
    break;
  case RECTANGLE_ROUND_HOLLOW:
    arg = getIntFromCapture(&captureData, 5);
    display->drawRoundRect(arg[0], arg[1], arg[2], arg[3], arg[4], currentColor);
    break;
  case RECTANGLE_ROUND_FILL:
    arg = getIntFromCapture(&captureData, 5);
    display->fillRoundRect(arg[0], arg[1], arg[2], arg[3], arg[4], currentColor);
    break;
  case LINE_FAST_VERTICAL:
    arg = getIntFromCapture(&captureData, 3);
    display->drawFastVLine(arg[0], arg[1], arg[2], currentColor);
    break;
  case LINE_FAST_HORIZONTAL:
    arg = getIntFromCapture(&captureData, 3);
    display->drawFastHLine(arg[0], arg[1], arg[2], currentColor);
    break;
  case LINE:
    arg = getIntFromCapture(&captureData, 4);
    display->drawLine(arg[0], arg[1], arg[2],arg[3], currentColor);
    break;
  case ROTATE:
    arg = getIntFromCapture(&captureData, 1);
    display->setRotation(arg[0]);
    break;
  default:
    Serial.println(F("Unknown Command"));
    break;
  }
  currentMode = UNDEFINED;
}
