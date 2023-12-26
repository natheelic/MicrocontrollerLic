#include <WiFiManager.h>  // https://github.com/tzapu/WiFiManager
// OLED
#include <Wire.h>         // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h"  // legacy: #include "SSD1306.h"

#define TRIGGER_PIN 0

SSD1306Wire display(0x3c, 4, 15);  // กำหนดตำแหน่ง address และขา SDA , SCL ของจอ OlED
String msg = "";

void setup() {

  pinMode(16, OUTPUT);
  digitalWrite(16, 1);  // กำหนดขา Reset ของ OLED

  // Initialising the UI will init the display too.
  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  WiFi.mode(WIFI_STA);  // explicitly set mode, esp defaults to STA+AP
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  delay(3000);
  Serial.println("\n Starting");

  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  msg = "Starting";
  display.drawString(0, 0, msg);
  display.display();

  pinMode(TRIGGER_PIN, INPUT);

  if (wm_nonblocking) wm.setConfigPortalBlocking(false);

  // add a custom input field
  int customFieldLength = 40;

  // test custom html(radio)
  const char* custom_radio_str = "<br/><label for='customfieldid'>Custom Field Label</label><input type='radio' name='customfieldid' value='1' checked> One<br><input type='radio' name='customfieldid' value='2'> Two<br><input type='radio' name='customfieldid' value='3'> Three";
  new (&custom_field) WiFiManagerParameter(custom_radio_str);  // custom html input

  wm.addParameter(&custom_field);
  wm.setSaveParamsCallback(saveParamCallback);

  // custom menu via array or vector
  std::vector<const char*> menu = { "wifi", "info", "param", "sep", "restart", "exit" };
  wm.setMenu(menu);

  // set dark theme
  wm.setClass("invert");
  wm.setConfigPortalTimeout(30);  // auto close configportal after n seconds

  bool res;
  // res = wm.autoConnect(); // auto generated AP name from chipid
  // res = wm.autoConnect("AutoConnectAP"); // anonymous ap
  res = wm.autoConnect("AutoConnectAP", "password");  // password protected ap

  if (!res) {
    Serial.println("Failed to connect or hit timeout");
    msg = "Failed to connect or hit timeout";
    // ESP.restart();
  } else {
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    msg = "connected...yeey :)";
  }
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 15, msg);
  display.display();
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
  display.drawString(0, 0, "Hello ALL");
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 10, "Hello ALL");
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 26, "EN 2023");
}

void loop() {
  if (wm_nonblocking) wm.process();  // avoid delays() in loop when non-blocking and other long running code
  checkButton();

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
