#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>  //ประกาศใช้งาน จอแบบ i2c

LiquidCrystal_I2C LCD = LiquidCrystal_I2C(0x27, 16, 2);  //กำหนด ตำแหน่ง และขนาดจอ

#define NTP_SERVER "3.th.pool.ntp.org"
#define UTC_OFFSET 25200
#define UTC_OFFSET_DST 25200

void spinner() {
  static int8_t counter = 0;
  const char* glyphs = "\xa1\xa5\xdb";
  LCD.setCursor(15, 1);
  LCD.print(glyphs[counter++]);
  if (counter == strlen(glyphs)) {
    counter = 0;
  }
}

void printLocalTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    LCD.setCursor(0, 1);
    LCD.println("Connection Err");
    return;
  }

  LCD.setCursor(8, 0);
  LCD.println(&timeinfo, "%H:%M:%S");

  LCD.setCursor(0, 1);
  LCD.println(&timeinfo, "%d/%m/%Y   %Z");
}

void setup() {
  Serial.begin(115200);

  LCD.init();       //เริ่มต้นใช้งาน LCD
  LCD.backlight();  //เปิดใช้ไฟพื้นหลัง
  LCD.setCursor(0, 0);
  LCD.print("Connecting to ");
  LCD.setCursor(0, 1);
  LCD.print("WiFi ");

  WiFi.begin("LIC-WIFI", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    spinner();
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.println("Online");
  LCD.setCursor(0, 1);
  LCD.println("Updating time...");

  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
}

void loop() {
  printLocalTime();
  delay(250);
}
