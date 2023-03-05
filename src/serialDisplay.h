
#if defined(_ADAFRUIT_TFTLCD_H_)

#define DISP Adafruit_TFTLCD

#endif // _ADAFRUIT_TFTLCD_H_

// #include <TFT_eSPI.h>  // Hardware-specific library
#define MAX_TEXT_CAPTURE 50
#define MAX_ARG_CAPTURE 6
#define COLOR_BLACK 0x0000
#define DEBOUNCE_READ_SERIAL 300

class serialDisplay
{
private:
  struct Capture
  {
    char capture[MAX_ARG_CAPTURE][MAX_TEXT_CAPTURE];
    byte index[MAX_ARG_CAPTURE];
    byte argIndex;
    byte maxCapture;
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
    DISPLAY_COLOR,
    CLEAR_SCREEN,
    SET_CURSOR,
    VERTICAL_LINE
  };

  DISP *display;
  MODE currentMode;
  Capture captureText;
  Capture captureColor;
  Capture capture2Arg;
  Capture capture3Arg;
  uint16_t currentColor = 0xFFFF;
  int displayWidth;
  int displayHeight;
  unsigned long lastSerialRead;

  void decodeInput(char input);
  void executeCommand(void);
  void captureInput(Capture *, char);
  void openCapture(Capture *);
  void closeCapture(Capture *);
  void initCapture(Capture *, byte, byte);
  void nextArgCapture(Capture *);
  void captureCommand(char);
  boolean isCommand(char*);

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

  initCapture(&captureText, MAX_TEXT_CAPTURE, 1);
  initCapture(&captureColor, 4, 1);
  initCapture(&capture2Arg, 6, 2);
  initCapture(&capture3Arg, 6, 3);
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
  capture->capture[capture->argIndex][capture->index[capture->argIndex]] = input;
  capture->index[capture->argIndex]++;
  if (capture->index[capture->argIndex] >= capture->maxCapture)
  {
    capture->index[capture->argIndex] = 0;
  }
}

void serialDisplay::closeCapture(Capture *capture)
{
  capture->argIndex = 0;
  for (int i = 0; i < capture->maxArg; i++)
  {
    capture->capture[i][capture->index[i]] = 0;
  }
}
void serialDisplay::openCapture(Capture *capture)
{
  capture->argIndex = 0;
  for (int i = 0; i < capture->maxArg; i++)
  {
    capture->index[i] = 0;
  }
}
void serialDisplay::initCapture(Capture *capture, byte maxCapture, byte maxArg)
{
  capture->maxCapture = maxCapture;
  capture->maxArg = maxArg;
}
void serialDisplay::nextArgCapture(Capture *capture)
{
  capture->argIndex++;
  if (capture->argIndex >= capture->maxArg)
  {
    capture->argIndex = 0;
  }
}

void serialDisplay::captureCommand(char input)
{
  captureInput(&captureText, input);
  closeCapture(&captureText);
  if (isCommand("tt"))
  {
    openCapture(&captureText);
    currentMode = TEXT;
    return;
  }
  if (isCommand("tv"))
  {
    openCapture(&captureText);
    currentMode = TEXT_CENTER_VERTICAL;
    return;
  }
  if (isCommand("th"))
  {
    openCapture(&captureText);
    currentMode = TEXT_CENTER_HORIZONTAL;
    return;
  }
  if (isCommand("ts"))
  {
    openCapture(&captureText);
    currentMode = TEXT_SIZE;
    return;
  }
  if (isCommand("ch"))
  {
    Serial.println(F("CIRCLE_HOLLOW"));
    openCapture(&capture3Arg);
    currentMode = CIRCLE_HOLLOW;
    return;
  }
  if (isCommand("sc"))
  {
    openCapture(&capture2Arg);
    currentMode = SET_CURSOR;
    return;
  }
}
boolean serialDisplay::isCommand(char *command){
  return strcmp(captureText.capture[0], command) == 0;
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
      openCapture(&captureColor);
      break;
    case 'x':
      currentMode = CLEAR_SCREEN;
      break;
    case 'c':
    case 't':
    case 's':
      currentMode = COMMAND;
      openCapture(&captureText);
      captureInput(&captureText, input);
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
    captureInput(&captureText, input);
    break;
  case SET_CURSOR:
    if (input == ',')
    {
      nextArgCapture(&capture2Arg);
    }
    else
    {
      if (input >= '0' && input <= '9')
      {
        captureInput(&capture2Arg, input);
      }
    }
    break;
  case CIRCLE_HOLLOW:
    if (input == ',')
    {
      nextArgCapture(&capture3Arg);
    }
    else
    {
      if (input >= '0' && input <= '9')
      {
        captureInput(&capture3Arg, input);
      }
    }
    break;
  case DISPLAY_COLOR:
    if ((input >= '0' && input <= '9') || (input >= 'a' && input <= 'f') || (input >= 'A' && input <= 'F'))
    {
      captureInput(&captureColor, input);
    }
    break;
  case TEXT_SIZE:
    if ((input >= '0' && input <= '9'))
    {
      captureInput(&captureText, input);
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
}

void serialDisplay::executeCommand(void)
{
  int16_t x, y, x1, y1, r;
  uint16_t w, h;
  uint16_t color;
  int size;

  switch (currentMode)
  {
  case UNDEFINED:
    break;
  case DISPLAY_COLOR:
    Serial.println(F("DISPLAY_COLOR"));
    closeCapture(&captureColor);
    color = strtol(captureColor.capture[0], NULL, 16);
    currentColor = color;
    display->setTextColor(currentColor);
    break;
  case TEXT_SIZE:
    Serial.println(F("TEXT_SIZE"));
    closeCapture(&captureText);
    size = atoi(captureText.capture[0]);
    display->setTextSize(size);
    break;
  case TEXT:
    Serial.println(F("TEXT"));
    closeCapture(&captureText);
    display->print(captureText.capture[0]);
    break;
  case TEXT_CENTER_HORIZONTAL:
    Serial.println(F("TEXT_CENTER_HORIZONTAL"));
    closeCapture(&captureText);
#if defined(_ADAFRUIT_TFTLCD_H_)
    y = display->getCursorY();
    display->getTextBounds(captureText.capture[0], &x, &y, &x1, &y1, &w, &h);
    display->setCursor((displayWidth - w) / 2, y);
#endif // _ADAFRUIT_TFTLCD_H_
    display->print(captureText.capture[0]);
    break;
  case TEXT_CENTER_VERTICAL:
    Serial.println(F("TEXT_CENTER_VERTICAL"));
    closeCapture(&captureText);
#if defined(_ADAFRUIT_TFTLCD_H_)
    x = display->getCursorX();
    display->getTextBounds(captureText.capture[0], &x, &y, &x1, &y1, &w, &h);
    display->setCursor(x, (displayHeight - h) / 2);
#endif // _ADAFRUIT_TFTLCD_H_
    display->print(captureText.capture[0]);

    break;
  case CLEAR_SCREEN:
    Serial.println(F("CLEAR_SCREEN"));
    display->fillScreen(COLOR_BLACK);
    break;
  case SET_CURSOR:
    Serial.println(F("SET_CURSOR"));
    closeCapture(&capture2Arg);
    x = atol(capture2Arg.capture[0]);
    y = atol(capture2Arg.capture[1]);
    display->setCursor(x, y);
    break;
  case CIRCLE_HOLLOW:
    Serial.println(F("CIRCLE_HOLLOW"));
    closeCapture(&capture3Arg);
    x = atol(capture3Arg.capture[0]);
    y = atol(capture3Arg.capture[1]);
    r = atol(capture3Arg.capture[2]);
    display->drawCircle(x, y, r, currentColor);
    break;
  default:
    Serial.println(F("Unknown Command"));
    break;
  }
  currentMode = UNDEFINED;
}
