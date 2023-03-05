
#if defined(_ADAFRUIT_TFTLCD_H_)

#define DISP Adafruit_TFTLCD

#endif // _ADAFRUIT_TFTLCD_H_

// #include <TFT_eSPI.h>  // Hardware-specific library
#define MAX_DATA_CAPTURE 50
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
    DISPLAY_COLOR,
    CLEAR_SCREEN,
    SET_CURSOR,
    VERTICAL_LINE
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
  void captureCommand(char);
  boolean isCommand(char *);

public:
  serialDisplay(DISP *d);
  ~serialDisplay();
  void readCommandsFromSerial(void);
  void runCommands(char *);
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
  if (isCommand("tt"))
  {
    openCapture(&captureData, 1);
    currentMode = TEXT;
    return;
  }
  if (isCommand("tv"))
  {
    openCapture(&captureData, 1);
    currentMode = TEXT_CENTER_VERTICAL;
    return;
  }
  if (isCommand("th"))
  {
    openCapture(&captureData, 1);
    currentMode = TEXT_CENTER_HORIZONTAL;
    return;
  }
  if (isCommand("ts"))
  {
    openCapture(&captureData, 1);
    currentMode = TEXT_SIZE;
    return;
  }
  if (isCommand("ch"))
  {
    openCapture(&captureData, 3);
    currentMode = CIRCLE_HOLLOW;
    return;
  }
  if (isCommand("cf"))
  {
    openCapture(&captureData, 3);
    currentMode = CIRCLE_FILL;
    return;
  }
  if (isCommand("gh"))
  {
    openCapture(&captureData, 6);
    currentMode = TRIANGLE_HOLLOW;
    return;
  }
  if (isCommand("gf"))
  {
    openCapture(&captureData, 6);
    currentMode = TRIANGLE_FILL;
    return;
  }
  if (isCommand("sc"))
  {
    openCapture(&captureData, 2);
    currentMode = SET_CURSOR;
    return;
  }
}
boolean serialDisplay::isCommand(char *command)
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
  case TRIANGLE_FILL:
  case TRIANGLE_HOLLOW:
  case CIRCLE_FILL:
  case CIRCLE_HOLLOW:
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
  int16_t x, y, x1, y1, x2, y2, r;
  uint16_t w, h;
  uint16_t color;
  int size;

  switch (currentMode)
  {
  case UNDEFINED:
    break;
  case DISPLAY_COLOR:
    // Serial.println(F("DISPLAY_COLOR"));
    closeCapture(&captureData);
    color = strtol(captureData.capture[0], NULL, 16);
    currentColor = color;
    display->setTextColor(currentColor);
    break;
  case TEXT_SIZE:
    // Serial.println(F("TEXT_SIZE"));
    closeCapture(&captureData);
    size = atoi(captureData.capture[0]);
    display->setTextSize(size);
    break;
  case TEXT:
    // Serial.println(F("TEXT"));
    closeCapture(&captureData);
    display->print(captureData.capture[0]);
    break;
  case TEXT_CENTER_HORIZONTAL:
    // Serial.println(F("TEXT_CENTER_HORIZONTAL"));
    closeCapture(&captureData);
#if defined(_ADAFRUIT_TFTLCD_H_)
    y = display->getCursorY();
    display->getTextBounds(captureData.capture[0], &x, &y, &x1, &y1, &w, &h);
    display->setCursor((displayWidth - w) / 2, y);
#endif // _ADAFRUIT_TFTLCD_H_
    display->print(captureData.capture[0]);
    break;
  case TEXT_CENTER_VERTICAL:
    // Serial.println(F("TEXT_CENTER_VERTICAL"));
    closeCapture(&captureData);
#if defined(_ADAFRUIT_TFTLCD_H_)
    x = display->getCursorX();
    display->getTextBounds(captureData.capture[0], &x, &y, &x1, &y1, &w, &h);
    display->setCursor(x, (displayHeight - h) / 2);
#endif // _ADAFRUIT_TFTLCD_H_
    display->print(captureData.capture[0]);

    break;
  case CLEAR_SCREEN:
    // Serial.println(F("CLEAR_SCREEN"));
    display->fillScreen(COLOR_BLACK);
    break;
  case SET_CURSOR:
    // Serial.println(F("SET_CURSOR"));
    closeCapture(&captureData);
    x = atoi(captureData.capture[0]);
    y = atoi(captureData.capture[1]);
    display->setCursor(x, y);
    break;
  case CIRCLE_HOLLOW:
    // Serial.println(F("CIRCLE_HOLLOW"));
    closeCapture(&captureData);
    x = atoi(captureData.capture[0]);
    y = atoi(captureData.capture[1]);
    r = atoi(captureData.capture[2]);
    display->drawCircle(x, y, r, currentColor);
    break;
  case CIRCLE_FILL:
    closeCapture(&captureData);
    x = atoi(captureData.capture[0]);
    y = atoi(captureData.capture[1]);
    r = atoi(captureData.capture[2]);
    display->fillCircle(x, y, r, currentColor);
    break;
  case TRIANGLE_HOLLOW:
    closeCapture(&captureData);
    x = atoi(captureData.capture[0]);
    y = atoi(captureData.capture[1]);
    x1 = atoi(captureData.capture[2]);
    y1 = atoi(captureData.capture[3]);
    x2 = atoi(captureData.capture[4]);
    y2 = atoi(captureData.capture[5]);
    display->drawTriangle(x, y, x1, y1, x2, y2, currentColor);
    break;
  case TRIANGLE_FILL:
    closeCapture(&captureData);
    x = atoi(captureData.capture[0]);
    y = atoi(captureData.capture[1]);
    x1 = atoi(captureData.capture[2]);
    y1 = atoi(captureData.capture[3]);
    x2 = atoi(captureData.capture[4]);
    y2 = atoi(captureData.capture[5]);
    display->fillTriangle(x, y, x1, y1, x2, y2, currentColor);
    break;
  default:
    Serial.println(F("Unknown Command"));
    break;
  }
  currentMode = UNDEFINED;
}
