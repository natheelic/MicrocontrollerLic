/**
 * WiFiManager advanced demo, contains advanced configurartion options
 * Implements TRIGGEN_PIN button press, press for ondemand configportal, hold for 3 seconds for reset settings.
 */
// OLED
#include <Wire.h>         // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"  // legacy: #include "SSD1306.h"

#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager

#include <ESP32Ping.h>

#include <TridentTD_LineNotify.h>

#define LINE_TOKEN  ""
const IPAddress remote_ip();
// const IPAddress remote_ip();
#define TRIGGER_PIN 0

SSD1306Wire display(0x3c, 4, 15);  // กำหนดตำแหน่ง address และขา SDA , SCL ของจอ OlED
String msg = "";
String chkip = "";

// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long previousMillis = 0;  // will store last time LED was updated
unsigned long ttime = 0;
// constants won't change:
const long interval = 1800000;  // interval at which to blink (milliseconds)

// wifimanager can run in a blocking mode or a non blocking mode
// Be sure to know how to process loops with no delay() if using non blocking
bool wm_nonblocking = false;  // change to true to use non blocking

WiFiManager wm;                     // global wm instance
WiFiManagerParameter custom_field;  // global param ( for non blocking w params )

void setup() {
  WiFi.mode(WIFI_STA);  // explicitly set mode, esp defaults to STA+AP
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(3000);
  Serial.println("\n Starting");

  pinMode(16, OUTPUT);
  digitalWrite(16, 1);  // กำหนดขา Reset ของ OLED
  // กำหนด Line Token
  LINE.setToken(LINE_TOKEN);
  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  msg = "Starting";
  display.drawString(0, 0, msg);
  display.display();
  delay(2000);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 17, "Waiting for Connect.");
  display.display();

  pinMode(TRIGGER_PIN, INPUT);

  if (wm_nonblocking) wm.setConfigPortalBlocking(false);
  int customFieldLength = 40;

  const char* custom_radio_str = "<br/><label for='customfieldid'>Custom Field Label</label><input type='radio' name='customfieldid' value='1' checked> One<br><input type='radio' name='customfieldid' value='2'> Two<br><input type='radio' name='customfieldid' value='3'> Three";
  new (&custom_field) WiFiManagerParameter(custom_radio_str);  // custom html input

  wm.addParameter(&custom_field);
  wm.setSaveParamsCallback(saveParamCallback);

  std::vector<const char*> menu = { "wifi", "info", "param", "sep", "restart", "exit" };
  wm.setMenu(menu);

  // set dark theme
  wm.setClass("invert");

  wm.setConfigPortalTimeout(30);

  bool res;

  res = wm.autoConnect("ESP-NOOKNICK", "password");  // password protected ap


  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.clear();

  if (!res) {
    Serial.println("Failed to connect or hit timeout");
    // msg = "Failed to connect , Press Reset Button.";
    display.drawString(0, 17, "Failed to connect");
    display.drawString(0, 27, "Press Reset Button.");
    display.display();
    while (1)
      ;
    // ESP.restart();
  } else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    msg = "connected...yeey :)";
    display.drawString(0, 17, msg);
    display.display();
    msg = "IP : " + WiFi.localIP().toString();
    pingIPadd();
  }
  delay(3000);
}

void pingIPadd() {
  Serial.print("Pinging ip ");
  Serial.println(remote_ip);

  if (Ping.ping(remote_ip)) {
    Serial.println("Pass!!");
    chkip = "Pass!!";
  } else {
    Serial.println("Error :(");
    chkip = "Error :(";
  }
  LINE.notify(chkip);
}


void checkButton() {
  // check for button press
  if (digitalRead(TRIGGER_PIN) == LOW) {
    // poor mans debounce/press-hold, code not ideal for production
    delay(50);
    if (digitalRead(TRIGGER_PIN) == LOW) {
      Serial.println("Button Pressed");
      // still holding button for 3000 ms, reset settings, code not ideaa for production
      delay(3000);  // reset delay hold
      if (digitalRead(TRIGGER_PIN) == LOW) {
        Serial.println("Button Held");
        Serial.println("Erasing Config, restarting");
        wm.resetSettings();
        ESP.restart();
      }

      // start portal w delay
      Serial.println("Starting config portal");
      wm.setConfigPortalTimeout(120);

      if (!wm.startConfigPortal("OnDemandAP", "password")) {
        Serial.println("failed to connect or hit timeout");
        delay(3000);
        // ESP.restart();
      } else {
        //if you get here you have connected to the WiFi
        Serial.println("connected...yeey :)");
      }
    }
  }
}


String getParam(String name) {
  //read parameter from server, for customhmtl input
  String value;
  if (wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback() {
  Serial.println("[CALLBACK] saveParamCallback fired");
  Serial.println("PARAM customfieldid = " + getParam("customfieldid"));
}

void drawFontFaceDemo() {
  // Font Demo1
  // create more fonts at http://oleddisplay.squix.ch/
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 0, msg);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, chkip);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 26, "Ping : ");
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 36, "Wait : "+ String(ttime));
}

void loop() {
  if (wm_nonblocking) wm.process();  // avoid delays() in loop when non-blocking and other long running code
  checkButton();
  // put your main code here, to run repeatedly:
  // clear the display
  display.clear();
  // draw the current demo method
  drawFontFaceDemo();

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();
  delay(10);
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    pingIPadd();
  }
  ttime =(currentMillis - previousMillis)/1000;
}
