// Program to exercise the MD_MAX72XX library
//
// Uses most of the functions in the library
#include <MD_MAX72xx.h>

// Turn on debug statements to the serial output
#define  DEBUG  1

#if  DEBUG
#define PRINT(s, x) { Serial.print(F(s)); Serial.print(x); }
#define PRINTS(x) Serial.print(F(x))
#define PRINTD(x) Serial.println(x, DEC)

#else
#define PRINT(s, x)
#define PRINTS(x)
#define PRINTD(x)

#endif

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted

//# ModuleType_t
//MD_MAX72XX::PAROLA_HW  LITERAL1
//MD_MAX72XX::GENERIC_HW  LITERAL1
//MD_MAX72XX::ICSTATION_HW  LITERAL1
//MD_MAX72XX::FC16_HW LITERAL1
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES	8

#define CLK_PIN   18  // or SCK
#define DATA_PIN  23  // or MOSI
#define CS_PIN    21  // or SS

// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Specific SPI hardware interface
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, SPI1, CS_PIN, MAX_DEVICES);
// Arbitrary pins
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

// We always wait a bit between updates of the display
#define  DELAYTIME  100  // in milliseconds

void scrollText(const char *p)
{
  uint8_t charWidth;
  uint8_t cBuf[8];  // this should be ok for all built-in fonts

  PRINTS("\nScrolling text");
  mx.clear();

  while (*p != '\0')
  {
    charWidth = mx.getChar(*p++, sizeof(cBuf) / sizeof(cBuf[0]), cBuf);

    for (uint8_t i=0; i<=charWidth; i++)	// allow space between characters
    {
      mx.transform(MD_MAX72XX::TSL);
      mx.setColumn(0, (i < charWidth) ? cBuf[i] : 0); 
      delay(DELAYTIME);
    }
  }
}

void wrapText()
// Display text and animate scrolling using auto wraparound of the buffer
{
  PRINTS("\nwrapText");
  mx.clear();
  mx.wraparound(MD_MAX72XX::ON);

  // draw something that will show changes
  for (uint16_t j=0; j<mx.getDeviceCount(); j++)
  {
    mx.setChar(((j+1)*COL_SIZE)-1, (j&1 ? 'M' : 'W'));
  }
  delay(DELAYTIME*5);

  // run thru transformations
  for (uint16_t i=0; i<3*COL_SIZE*MAX_DEVICES; i++)
  {
    mx.transform(MD_MAX72XX::TSL);
    delay(DELAYTIME/2);
  }
  for (uint16_t i=0; i<3*COL_SIZE*MAX_DEVICES; i++)
  {
    mx.transform(MD_MAX72XX::TSR);
    delay(DELAYTIME/2);
  }
  for (uint8_t i=0; i<ROW_SIZE; i++)
  {
    mx.transform(MD_MAX72XX::TSU);
    delay(DELAYTIME*2);
  }
  for (uint8_t i=0; i<ROW_SIZE; i++)
  {
    mx.transform(MD_MAX72XX::TSD);
    delay(DELAYTIME*2);
  }

  mx.wraparound(MD_MAX72XX::OFF);
}

void showCharset(void)
// Run through display of the the entire font characters set
{
  mx.clear();
  mx.update(MD_MAX72XX::OFF);

  for (uint16_t i=0; i<256; i++)
  {
    mx.clear(0);
    mx.setChar(COL_SIZE-1, i);

    if (MAX_DEVICES >= 3)
    {
      char hex[3];

      sprintf(hex, "%02X", i);

      mx.clear(1);
      mx.setChar((2*COL_SIZE)-1,hex[1]);
      mx.clear(2);
      mx.setChar((3*COL_SIZE)-1,hex[0]);
    }

    mx.update();
    delay(DELAYTIME*2);
  }
  mx.update(MD_MAX72XX::ON);
}

void setup()
{
#if  DEBUG
  Serial.begin(115200);
#endif
  PRINTS("\n[MD_MAX72XX Test & Demo]");

  if (!mx.begin())
    PRINTS("\nMD_MAX72XX initialization failed");
}

void loop()
{
// #if 1
  scrollText("display messages on a MAX7219 dot matrix with the help of an ESP8266 and WiFiManager for configuration, you can follow the steps below.");
//   wrapText();
//   showCharset();
// #endif
}

