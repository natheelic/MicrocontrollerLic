const int ldrPin = 13;
const int ledPins[] = {21, 19, 18, 5, 17, 16, 4, 0, 2, 15}; // Pins connected to the LEDs
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

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
    int ledCount = map(ldrValue, 0, 1023, 0, numLeds);

    for (int i = 0; i < numLeds; i++)
    {
        if (i < ledCount)
        {
            digitalWrite(ledPins[i], HIGH);
        }
        else
        {
            digitalWrite(ledPins[i], LOW);
        }
    }
}
