// OLED
#include <Wire.h>         // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"  // legacy: #include "SSD1306.h"

SSD1306Wire display(0x3c, 4, 15);  // กำหนดตำแหน่ง address และขา SDA , SCL ของจอ OlED

#define DEMO_DURATION 3000

void setup() {

  pinMode(16, OUTPUT);
  digitalWrite(16, 1);  // กำหนดขา Reset ของ OLED

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
}

void drawFontFaceDemo() {
  // Font Demo1
  // create more fonts at http://oleddisplay.squix.ch/
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, "Hello ALL");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, "Hello ALL");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 26, "EN 2023");
}

void loop() {
  // clear the display
  display.clear();
  // draw the current demo method
  drawFontFaceDemo();

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();
  delay(10);
}
