#include <WiFi.h>
#include <WiFiClient.h>

#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMP-EN-LIC"
#define BLYNK_TEMPLATE_NAME "Nook-Device"
//**********************************************************
// #define BLYNK_AUTH_TOKEN "4nUhcFw1pNd1yf-dS4XUPDJ53WMrreyN"
#define BLYNK_AUTH_TOKEN "xagvO9HxZzFMFNeEXXzNQ9WE6MhHp_jA"
//**********************************************************
#define SERVER_IP "61.19.114.86"
#define SERVER_PORT 3007

#include <BlynkSimpleEsp32.h>

char ssid[] = "EN-LIC";
char pass[] = "ENLIC2023";

byte led[] = {13, 12, 14, 27, 26, 25, 33, 32};
int inPin = 34;
int reading = 0;
BLYNK_WRITE(V0)
{
  reading = param.asInt();
}

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, SERVER_IP, SERVER_PORT);

  for (int i = 0; i < 8; i++)
  {
    pinMode(led[i], OUTPUT);
  }
}

void loop()
{
  // int reading = analogRead(inPin);
  Serial.println(reading);
  if (reading > 0 && reading < 512)
  {
    digitalWrite(led[0], HIGH);
  }
  else if (reading >= 512 && reading < 1024)
  {
    digitalWrite(led[1], HIGH);
  }
  else if (reading >= 1024 && reading < 1536)
  {
    digitalWrite(led[3], HIGH);
  }
  else if (reading >= 2048 && reading < 2560)
  {
    digitalWrite(led[4], HIGH);
  }
  else if (reading >= 2560 && reading < 3072)
  {
    digitalWrite(led[5], HIGH);
  }
  else if (reading >= 3072 && reading < 3584)
  {
    digitalWrite(led[6], HIGH);
  }
  else if (reading >= 3584 && reading < 4096)
  {
    digitalWrite(led[7], HIGH);
  }
  else if (reading == 0)
  {
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(led[i], LOW);
    }
  }

  Blynk.run();
}