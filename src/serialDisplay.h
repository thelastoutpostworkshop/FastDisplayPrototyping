
#if defined(_ADAFRUIT_TFTLCD_H_)

#define DISP Adafruit_TFTLCD

#endif // _ADAFRUIT_TFTLCD_H_

// #include <TFT_eSPI.h>  // Hardware-specific library
#define MAX_TEXT_CAPTURE 20
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
  if (capture->index[capture->argIndex] > capture->maxCapture)
  {
    capture->index[capture->argIndex] = 0;
  }
}

void serialDisplay::closeCapture(Capture *capture)
{
  capture->argIndex = 0;
  for (int i = 0; i < MAX_ARG_CAPTURE; i++)
  {
    capture->capture[i][capture->index[i]] = 0;
  }
}
void serialDisplay::openCapture(Capture *capture)
{
  capture->argIndex = 0;
  for (int i = 0; i < MAX_ARG_CAPTURE; i++)
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
  if (capture->argIndex > capture->maxArg)
  {
    capture->argIndex = 0;
  }
}

void serialDisplay::captureCommand(char input)
{
  captureInput(&captureText, input);
  closeCapture(&captureText);
  if (strcmp(captureText.capture[0], "tt") == 0)
  {
    openCapture(&captureText);
    currentMode = TEXT;
    return;
  }
  if (strcmp(captureText.capture[0], "tv") == 0)
  {
    openCapture(&captureText);
    currentMode = TEXT_CENTER_VERTICAL;
    return;
  }
  if (strcmp(captureText.capture[0], "th") == 0)
  {
    openCapture(&captureText);
    currentMode = TEXT_CENTER_HORIZONTAL;
    return;
  }
  if (strcmp(captureText.capture[0], "sc") == 0)
  {
    openCapture(&capture2Arg);
    currentMode = SET_CURSOR;
    return;
  }
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
    case 'c':
      currentMode = CLEAR_SCREEN;
      break;
    case 't':
    case 's':
      openCapture(&captureText);
      captureInput(&captureText, input);
      currentMode = COMMAND;
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
  case DISPLAY_COLOR:
    if ((input >= '0' && input <= '9') || (input >= 'a' && input <= 'f') || (input >= 'A' && input <= 'F'))
    {
      captureInput(&captureColor, input);
    }
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
  }
  else
  {
    if (currentColor != UNDEFINED && millis() - lastSerialRead > DEBOUNCE_READ_SERIAL)
    {
      executeCommand();
      lastSerialRead = millis();
    }
  }
}

void serialDisplay::executeCommand(void)
{
  int16_t x, y, x1, y1;
  uint16_t w, h;
  uint16_t color;

  switch (currentMode)
  {
  case UNDEFINED:
    break;
  case DISPLAY_COLOR:
    closeCapture(&captureColor);
    color = strtol(captureColor.capture[0], NULL, 16);
    currentColor = color;
    display->setTextColor(currentColor);
    Serial.print("DISPLAY_COLOR: ");
    Serial.println(captureColor.capture[0]);
    break;
  case TEXT:
    closeCapture(&captureText);
    display->print(captureText.capture[0]);
    Serial.print("TEXT: ");
    Serial.println(captureText.capture[0]);
    break;
  case TEXT_CENTER_HORIZONTAL:
    Serial.println("TEXT_CENTER_HORIZONTAL: ");
    closeCapture(&captureText);
#if defined(_ADAFRUIT_TFTLCD_H_)
    display->getTextBounds(captureText.capture[0], &x, &y, &x1, &y1, &w, &h);
    display->setCursor((displayWidth-w)/2,y);

#endif // _ADAFRUIT_TFTLCD_H_
    // y = display->getCursorY();
    // w = display->textWidth(captureText.capture[0]);
    // display->setCursor((displayWidth / 2) - (w / 2), y);
    display->print(captureText.capture[0]);

    Serial.println(captureText.capture[0]);
    break;
  case TEXT_CENTER_VERTICAL:
    closeCapture(&captureText);
    // x = display->getCursorX();
    // w = display->fontHeight();
    // display->setCursor(x, (displayWidth / 2) - (w / 2));
    // display->print(captureText.capture[0]);

    Serial.print("TEXT_CENTER_VERTICAL: ");
    Serial.println(captureText.capture[0]);
    break;
  case CLEAR_SCREEN:
    display->fillScreen(COLOR_BLACK);
    Serial.println("CLEAR_SCREEN");
    break;
  case SET_CURSOR:
    closeCapture(&capture2Arg);
    x = atol(capture2Arg.capture[0]);
    y = atol(capture2Arg.capture[1]);
    display->setCursor(x, y);
    Serial.print("SET_CURSOR: ");
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);
    break;
  }
  currentMode = UNDEFINED;
}
