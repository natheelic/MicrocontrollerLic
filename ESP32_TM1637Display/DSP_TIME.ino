#include <WiFi.h>
#include <TM1637Display.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#define CLK 19
#define DIO 18

// Initialize the TM1637 display
TM1637Display display(CLK, DIO);

const char* ssid = "LIC-WIFI";
const char* password = "";

// Define NTP Server
const char* ntpServerName = "pool.ntp.org";
// Initialize UDP client for NTP
WiFiUDP ntpUDP;
// Define time zone (GMT+7 for Bangkok, Thailand)
const long utcOffsetInSeconds = 7 * 3600;
NTPClient timeClient(ntpUDP, ntpServerName, utcOffsetInSeconds);

void setup() {
  Serial.begin(115200);

  // Initialize the TM1637 display
  display.setBrightness(0x0a); // Set the brightness (0x00 to 0x0f)

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  // Initialize the time client
  timeClient.begin();
  timeClient.setTimeOffset(utcOffsetInSeconds);
}


void loop() {
  // Update the time from the NTP server
  timeClient.update();
  // Get the current time
  uint8_t hours = timeClient.getHours();
  uint8_t minutes = timeClient.getMinutes();
 
  if (hours >= 7 && hours < 18) {
    display.setBrightness(0x0f); // Set the brightness to high
  } else {
    display.setBrightness(0x07); // Set the brightness to medium
  }
  // Display the time on the TM1637 display
  display.showNumberDecEx(hours * 100 + minutes, 0b11100000, true); //Flash every 2 seconds
  
  uint8_t seconds = timeClient.getSeconds();
  Serial.println((String)hours + ":" + minutes + ":" + seconds);
  delay(1000); // Update the display every second
  
}
