// Program to control the brightness of an LED using a potentiometer
const int ldrPin = 13;
const int ledPins[] = {21, 19, 18, 5, 17, 16, 4, 0, 2, 15}; // Pins connected to the LEDs
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);
void ledControl(byte pin);

void setup()
{
    Serial.begin(115200);
    pinMode(ldrPin, INPUT);
    for (int i = 0; i < numLeds; i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
    Serial.println(numLeds);
}

void loop()
{
    int ldrValue = analogRead(ldrPin);
    Serial.println(ldrValue);
    int ledCount = map(ldrValue, 0, 4095, 0, numLeds);
    Serial.println(ledCount);
    ledControl(ledCount);
}

void ledControl(byte pin)
{
    for (int i = 0; i < numLeds; i++)
    {
        digitalWrite(ledPins[i], LOW);
    }
    digitalWrite(ledPins[pin], HIGH);
}
// Path: LAB-4-07/LAB-4-07-03.ino