
#if defined(_ADAFRUIT_TFTLCD_H_)

#define DISP Adafruit_TFTLCD

#endif // _ADAFRUIT_TFTLCD_H_

// #include <TFT_eSPI.h>  // Hardware-specific library
#define MAX_TEXT_CAPTURE 50
#define MAX_ARG_CAPTURE 6
#define COLOR_BLACK 0x0000

class serialDisplay
{
private:
  struct Capture
  {
    char capture[MAX_ARG_CAPTURE][30];
    byte index[MAX_ARG_CAPTURE];
    byte argIndex;
    byte maxCapture;
    byte maxArg;
  };
  enum MODE
  {
    UNDEFINED,
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

  void decodeInput(char input);
  void executeCommand(void);
  void captureInput(Capture *, char);
  void openCapture(Capture *);
  void closeCapture(Capture *);
  void initCapture(Capture *, byte, byte);
  void nextArgCapture(Capture *);

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

void serialDisplay::decodeInput(char input)
{
  if (input == ';')
  {
    executeCommand();
    return;
  }
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
    case 'C':
      currentMode = CLEAR_SCREEN;
      break;
    case 'h':
    case 'H':
      openCapture(&captureText);
      currentMode = TEXT_CENTER_HORIZONTAL;
      break;
    case 'v':
    case 'V':
      openCapture(&captureText);
      currentMode = TEXT_CENTER_VERTICAL;
      break;
    case 'T':
    case 't':
      openCapture(&captureText);
      currentMode = TEXT;
      break;
    case 'S':
    case 's':
      currentMode = SET_CURSOR;
      openCapture(&capture2Arg);
      break;
    }
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
    if (currentMode != UNDEFINED)
    {
      executeCommand();
    }
  }
}

void serialDisplay::executeCommand(void)
{
  int16_t x, y, w;
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
    closeCapture(&captureText);
    // y = display->getCursorY();
    // w = display->textWidth(captureText.capture[0]);
    // display->setCursor((displayWidth / 2) - (w / 2), y);
    // display->print(captureText.capture[0]);

    Serial.print("TEXT_CENTER_HORIZONTAL: ");
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
