/*
  Project: Dot matrix clock with NTP server using ESP32
  Board: ESP32 Dev Module (Node32 Lite)
  
  Connections:
  ESP32 | Dot Matrix
    RAW - VCC
    GND - GND
     27 - DIN
     26 - CS
     25 - CLK
  
  External libraries:
  - MD_MAX72XX by majicDesigns Version 3.2.1 (Manager)
  - MD_Parola by majicDesigns Version 3.3.0 (Manager)
  - NTPClient by Fabrice Weinberg Version 3.1.0 (Zip)
    https://github.com/taranais/NTPClient/archive/master.zip
 */

#include <WiFi.h>
#include <WiFiClient.h>
const char ssid[] = ".@LIC Student"; // WiFi name
const char password[] = ""; // WiFi password

#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

//#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define HARDWARE_TYPE MD_MAX72XX::ICSTATION_HW
#define MAX_DEVICES 8
#define CLK_PIN   18  // or SCK
#define DATA_PIN  23  // or MOSI
#define CS_PIN    21  // or SS

MD_Parola DotMatrix = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 50; // default frame delay value
textEffect_t scrollEffect = PA_SCROLL_LEFT;
textPosition_t scrollAlign = PA_LEFT;
uint16_t scrollPause = 3000; // in milliseconds

long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
String formattedDate;
String timeStamp, hour, minute, second;
String dateStamp, year, month, date;
char dateBuffer[] = "";
String monthArray[12] = {
  " Jan ", " Feb ", " Mar ", " Apr ", " May ", " Jun ",
  " Jul ", " Aug ", " Sep ", " Oct ", " Nov ", " Dec "
};
enum {TIME, DATE};
boolean displayMode = TIME;

void setup()
{
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  DotMatrix.begin();
  DotMatrix.setIntensity(0);

  timeClient.begin();
  timeClient.setTimeOffset(25200); // Set offset time in seconds, GMT+8 = 28800

  DotMatrix.displayText("NTP Clock by Idris", scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
  displayMode = DATE;
}

void loop()
{
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }

  if (displayMode == DATE && DotMatrix.displayAnimate()) {
    DotMatrix.displayReset();
    displayMode = TIME;
  }

  currentMillis = millis();
  if (currentMillis - previousMillis > interval &&
      displayMode == TIME) {
    previousMillis = millis();

    // The formattedDate comes with the following format:
    // 2018-05-28T16:00:13Z
    formattedDate = timeClient.getFormattedTime();
    Serial.println(formattedDate);

    // Extract date
    year = formattedDate.substring(0, 4);
    month = formattedDate.substring(5, 7);
    month = monthArray[month.toInt() - 1];
    date = formattedDate.substring(8, 10);
    date = String(date.toInt());
    dateStamp = year + ", " + date + month;
    dateStamp.toCharArray(dateBuffer, dateStamp.length()+1);
    
    // Extract time
    hour = formattedDate.substring(11, 13);
    minute = formattedDate.substring(14, 16);
    second = formattedDate.substring(17, 19);

    if (hour.toInt() == 0) {
      hour = String(hour.toInt() + 12);
    }
    else if (hour.toInt() < 13) {
      hour = String(hour.toInt());
    }
    else {
      hour = String(hour.toInt() - 12);
    }

    if (second.toInt() == 0) {
      displayMode = DATE;
      DotMatrix.displayClear();
      DotMatrix.displayText(dateBuffer, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
      return;
    }
    else if (second.toInt() % 2) {
      timeStamp = hour + ":" + minute;
    }
    else {
      timeStamp = hour + " " + minute;
    }
    
    DotMatrix.setTextAlignment(PA_CENTER);
    DotMatrix.print(timeStamp);
  }
}