#if defined(_ADAFRUIT_TFTLCD_H_)

#define DISP Adafruit_TFTLCD

#endif // _ADAFRUIT_TFTLCD_H_

#if defined(_TFT_eSPIH_)

#define DISP TFT_eSPI

#endif // _TFT_eSPIH_

#define MAX_DATA_CAPTURE 30
#define MAX_ARG_CAPTURE 9
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
    ELLIPSE_OUTLINE,
    ELLIPSE_FILL,
    TRIANGLE_HOLLOW,
    TRIANGLE_FILL,
    RECTANGLE_HOLLOW,
    RECTANGLE_FILL,
    RECTANGLE_FILL_GRADIENT_HORIZONTAL,
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
    ROTATE,
    PIXEL
  };

  DISP *display;
  MODE currentMode;
  Capture captureData;
  uint32_t currentColor = 0xFFFF;
  int displayWidth;
  int displayHeight;
  unsigned long lastSerialRead;
  char serialBuffer[255];
  const char *displayName;

  const char *displaySizeKeywords = "WwHh";

  void decodeInput(char input);
  void executeCommand(void);
  void captureInput(Capture *, char);
  void openCapture(Capture *, int);
  void closeCapture(Capture *);
  void nextArgCapture(Capture *);
  int32_t *getIntFromCapture(Capture *, int);
  int32_t *getIntFromCapture(Capture *, int, int);
  int32_t getIntFromCapture(char *);
  float getFloatFromCapture(char *);
  bool getBoolFromCapture(char *);
  int getValueFromKeyword(char);
  int32_t *getColorFromCapture(Capture *, int, int);
  uint32_t getColorFromCapture(char *);
  void captureCommand(char);
  boolean isCommand(const char *);
  void serialPrintFormatted(const char *formatStr, ...);
  bool containsOnlyDigits(const char *);
  inline void serialPrintFormattedMacro(serialDisplay *disp, const char *fmt, ...)
  {
#ifdef OUTPUT_CODE_ON_SERIAL
    va_list args;
    va_start(args, fmt);
    vsnprintf_P(disp->serialBuffer, sizeof(disp->serialBuffer), fmt, args);
    va_end(args);
    Serial.println(disp->serialBuffer);
#endif
  }

public:
  serialDisplay(DISP *d, const char *dName = nullptr);
  ~serialDisplay();
  void readCommandsFromSerial(void);
  void runCommands(char *);
  void runCommands(const __FlashStringHelper *ifsh);
};

serialDisplay::serialDisplay(DISP *d, const char *dName)
{
  if (dName != nullptr)
  {
    displayName = dName;
  }
  else
  {
    displayName = "tft";
  }

  currentMode = UNDEFINED;
  display = d;

  displayWidth = d->width();
  displayHeight = d->height();

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
  while (1)
  {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0)
      break;
    decodeInput(c);
  }
}

bool serialDisplay::containsOnlyDigits(const char *str)
{
  for (int i = 0; str[i] != '\0'; i++)
  {
    if (!isdigit(str[i]))
    {
      return false;
    }
  }
  return true;
}

float serialDisplay::getFloatFromCapture(char *capture)
{
  if (containsOnlyDigits(capture))
  {
    return atof(capture);
  }
  else
  {
    return getValueFromKeyword(capture[0]);
  }
}

uint32_t serialDisplay::getColorFromCapture(char *capture)
{
  return strtoul(capture, NULL, 16);
}
int32_t *serialDisplay::getColorFromCapture(Capture *capture, int start, int end)
{
  static int32_t res[MAX_ARG_CAPTURE];
  for (int i = start; i <= end && i <= MAX_ARG_CAPTURE; i++)
  {
    res[i] = getColorFromCapture(capture->capture[i]);
  }
  return res;
}

int32_t *serialDisplay::getIntFromCapture(Capture *capture, int count)
{
  return getIntFromCapture(capture, 0, count - 1);
}
int32_t *serialDisplay::getIntFromCapture(Capture *capture, int start, int end)
{
  static int32_t res[MAX_ARG_CAPTURE];
  for (int i = start; i <= end && i <= MAX_ARG_CAPTURE; i++)
  {
    res[i] = getIntFromCapture(capture->capture[i]);
  }
  return res;
}

int32_t serialDisplay::getIntFromCapture(char *capture)
{
  if (containsOnlyDigits(capture))
  {
    return atoi(capture);
  }
  else
  {
    return getValueFromKeyword(capture[0]);
  }
}

bool serialDisplay::getBoolFromCapture(char *capture)
{
  if (!containsOnlyDigits(capture))
  {
    if (getValueFromKeyword(capture[0]) == 1)
    {
      return true;
    }
  }
  return false;
}

int serialDisplay::getValueFromKeyword(char c)
{
  if (strchr(displaySizeKeywords, c))
  {
    switch (c)
    {
    case 'W':
    case 'w':
      /* code */
      return (displayWidth);
      break;
    case 'H':
    case 'h':
      return (displayHeight);
      break;
    case 'T':
    case 't':
      return 1;
      break;
    case 'F':
    case 'f':
      return 0;
      break;
    }
  }
  return 0;
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

  const char *commands[] = {"tt", "tv", "th", "ts", "ch", "cf", "gh", "gf", "rh", "rf", "ri", "rj", "sc", "lv", "lh", "dl", "ro", "dp", "rk", "ce","cg"};
  const int numCommands = sizeof(commands) / sizeof(*commands);

  for (int i = 0; i < numCommands; i++)
  {
    if (isCommand(commands[i]))
    {
      switch (i)
      {
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
      case 17:
        currentMode = PIXEL;
        openCapture(&captureData, 2);
        break;
      case 18:
        currentMode = RECTANGLE_FILL_GRADIENT_HORIZONTAL;
        openCapture(&captureData, 6);
        break;
      case 19:
        currentMode = ELLIPSE_OUTLINE;
        openCapture(&captureData, 4);
        break;
      case 20:
        currentMode = ELLIPSE_FILL;
        openCapture(&captureData, 4);
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
      if (isdigit(input))
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
  case RECTANGLE_FILL_GRADIENT_HORIZONTAL:
  case RECTANGLE_HOLLOW:
  case TRIANGLE_FILL:
  case TRIANGLE_HOLLOW:
  case CIRCLE_FILL:
  case CIRCLE_HOLLOW:
  case ELLIPSE_OUTLINE:
  case ELLIPSE_FILL:
  case ROTATE:
  case PIXEL:
    if (input == ',')
    {
      nextArgCapture(&captureData);
    }
    else
    {
      if (isdigit(input) || strchr(displaySizeKeywords, input) || (input >= 'a' && input <= 'f') || (input >= 'A' && input <= 'F'))
      {
        captureInput(&captureData, input);
      }
    }
    break;
  case DISPLAY_COLOR:
    if (isdigit(input) || (input >= 'a' && input <= 'f') || (input >= 'A' && input <= 'F'))
    {
      captureInput(&captureData, input);
    }
    break;
  case TEXT_SIZE:
    if (isdigit(input))
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
  int32_t *arg, *colorArg;

  if (currentColor == UNDEFINED)
  {
    return;
  }

  closeCapture(&captureData);
  const char *formatStr = nullptr;

  switch (currentMode)
  {
  case DISPLAY_COLOR:
    currentColor = getColorFromCapture(captureData.capture[0]);
    display->setTextColor(currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.setTextColor(0x%x);"), displayName, currentColor);
    break;
  case TEXT_SIZE:
    arg = getIntFromCapture(&captureData, 1);
    display->setTextSize(arg[0]);
    serialPrintFormattedMacro(this, PSTR("%s.setTextSize(%d);"), displayName, arg[0]);
    break;
  case TEXT:
    display->print(captureData.capture[0]);
    serialPrintFormattedMacro(this, PSTR("%s.print(\"%s\");"), displayName, captureData.capture[0]);
    break;
  case TEXT_CENTER_HORIZONTAL:
#if defined(_ADAFRUIT_TFTLCD_H_)
    y = display->getCursorY();
    display->getTextBounds(captureData.capture[0], &x, &y, &x1, &y1, &w, &h);
    x = (displayWidth - w) / 2;
    display->setCursor(x, y);
#endif // _ADAFRUIT_TFTLCD_H_
#if defined(_TFT_eSPIH_)
    w = display->textWidth(captureData.capture[0]);
    x = (displayWidth - w) / 2;
    y = display->getCursorY();
    display->setCursor(x, y);
#endif // _TFT_eSPIH_
    display->print(captureData.capture[0]);
    serialPrintFormattedMacro(this, PSTR("%s.setCursor(%d,%d);"), displayName, x, y);
    serialPrintFormattedMacro(this, PSTR("%s.print(\"%s\");"), displayName, captureData.capture[0]);
    break;
  case TEXT_CENTER_VERTICAL:
#if defined(_ADAFRUIT_TFTLCD_H_)
    x = display->getCursorX();
    display->getTextBounds(captureData.capture[0], &x, &y, &x1, &y1, &w, &h);
    y = (displayHeight - h) / 2;
    display->setCursor(x, y);
#endif // _ADAFRUIT_TFTLCD_H_
#if defined(_TFT_eSPIH_)
    h = display->fontHeight();
    y = (displayHeight - h) / 2;
    x = display->getCursorX();
    display->setCursor(x, y);
#endif // _TFT_eSPIH_
    display->print(captureData.capture[0]);
    serialPrintFormattedMacro(this, PSTR("%s.setCursor(%d,%d);"), displayName, x, y);
    serialPrintFormattedMacro(this, PSTR("%s.print(\"%s\");"), displayName, captureData.capture[0]);
    break;
  case CLEAR_SCREEN:
    display->fillScreen(COLOR_BLACK);
    serialPrintFormattedMacro(this, PSTR("%s.fillScreen(0x%x);"), displayName, COLOR_BLACK);
    break;
  case FILL_SCREEN:
    display->fillScreen(currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.fillScreen(0x%x);"), displayName, currentColor);
    break;
  case SET_CURSOR:
    arg = getIntFromCapture(&captureData, 2);
    display->setCursor(arg[0], arg[1]);
    serialPrintFormattedMacro(this, PSTR("%s.setCursor(%d,%d);"), displayName, arg[0], arg[1]);
    break;
  case CIRCLE_HOLLOW:
    arg = getIntFromCapture(&captureData, 3);
    display->drawCircle(arg[0], arg[1], arg[2], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.drawCircle(%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], currentColor);
    break;
  case CIRCLE_FILL:
    arg = getIntFromCapture(&captureData, 3);
    display->fillCircle(arg[0], arg[1], arg[2], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.fillCircle(%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], currentColor);
    break;
  case TRIANGLE_HOLLOW:
    arg = getIntFromCapture(&captureData, 6);
    display->drawTriangle(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.drawTriangle(%d,%d,%d,%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], currentColor);
    break;
  case TRIANGLE_FILL:
    arg = getIntFromCapture(&captureData, 6);
    display->fillTriangle(arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.fillTriangle(%d,%d,%d,%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], arg[3], arg[4], arg[5], currentColor);
    break;
  case RECTANGLE_HOLLOW:
    arg = getIntFromCapture(&captureData, 4);
    display->drawRect(arg[0], arg[1], arg[2], arg[3], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.drawRect(%d,%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], arg[3], currentColor);
    break;
  case RECTANGLE_FILL:
    arg = getIntFromCapture(&captureData, 4);
    display->fillRect(arg[0], arg[1], arg[2], arg[3], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.fillRect(%d,%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], arg[3], currentColor);
    break;
  case RECTANGLE_ROUND_HOLLOW:
    arg = getIntFromCapture(&captureData, 5);
    display->drawRoundRect(arg[0], arg[1], arg[2], arg[3], arg[4], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.drawRoundRect(%d,%d,%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], arg[3], arg[4], currentColor);
    break;
  case RECTANGLE_ROUND_FILL:
    arg = getIntFromCapture(&captureData, 5);
    display->fillRoundRect(arg[0], arg[1], arg[2], arg[3], arg[4], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.fillRoundRect(%d,%d,%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], arg[3], arg[4], currentColor);
    break;
  case LINE_FAST_VERTICAL:
    arg = getIntFromCapture(&captureData, 3);
    display->drawFastVLine(arg[0], arg[1], arg[2], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.drawFastVLine(%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], currentColor);
    break;
  case LINE_FAST_HORIZONTAL:
    arg = getIntFromCapture(&captureData, 3);
    display->drawFastHLine(arg[0], arg[1], arg[2], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.drawFastHLine(%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], currentColor);
    break;
  case LINE:
    arg = getIntFromCapture(&captureData, 4);
    display->drawLine(arg[0], arg[1], arg[2], arg[3], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.drawLine(%d,%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], arg[3], currentColor);
    break;
  case ROTATE:
    arg = getIntFromCapture(&captureData, 1);
    display->setRotation(arg[0]);
    serialPrintFormattedMacro(this, PSTR("%s.setRotation(%d);"), displayName, arg[0]);
    break;
  case PIXEL:
    arg = getIntFromCapture(&captureData, 2);
    display->drawPixel(arg[0], arg[1], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.drawPixel(%d,%d,0x%x);"), displayName, arg[0], arg[1], currentColor);
    break;
#if defined(_TFT_eSPIH_)
  case RECTANGLE_FILL_GRADIENT_HORIZONTAL:
    arg = getIntFromCapture(&captureData, 0, 3);
    colorArg = getColorFromCapture(&captureData, 4, 5);
    display->fillRectHGradient(arg[0], arg[1], arg[2], arg[3], colorArg[4], colorArg[5]);
    serialPrintFormattedMacro(this, PSTR("%s.fillRectVGradient(%d,%d,%d,%d,0x%x,0x%x);"), displayName, arg[0], arg[1], arg[2], arg[3], colorArg[4], colorArg[5]);
    break;
  case ELLIPSE_OUTLINE:
    arg = getIntFromCapture(&captureData, 4);
    display->drawEllipse(arg[0], arg[1], arg[2], arg[3], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.drawEllipse(%d,%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], arg[3], currentColor);
    break;
  case ELLIPSE_FILL:
    arg = getIntFromCapture(&captureData, 4);
    display->fillEllipse(arg[0], arg[1], arg[2], arg[3], currentColor);
    serialPrintFormattedMacro(this, PSTR("%s.fillEllipse(%d,%d,%d,%d,0x%x);"), displayName, arg[0], arg[1], arg[2], arg[3], currentColor);
    break;
#endif
  default:
    Serial.println(F("Unknown Command"));
    break;
  }
  currentMode = UNDEFINED;
}
