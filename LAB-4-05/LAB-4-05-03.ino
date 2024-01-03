const int potPin = 13;
const int ledPins[] = {21, 19, 18, 5, 17, 16, 4, 0, 2, 15}; // Pins connected to the LEDs
const int numLeds = sizeof(ledPins) / sizeof(ledPins[0]);

void setup()
{
    // Set the LED pins as output
    for (int i = 0; i < numLeds; i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
}

void loop()
{
    // Read the analog value from the potentiometer
    int potValue = analogRead(potPin);

    // Map the analog value to a range suitable for controlling the LEDs
    int ledCount = map(potValue, 0, 4095, 0, numLeds);

    // Set the LED pins based on the mapped value
    for (int i = 0; i < 10; i++)
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
