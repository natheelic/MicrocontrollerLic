const int ledPins[] = {17, 16, 4, 0}; // Pins connected to the LEDs

void setup()
{
    // Set the LED pins as OUTPUT
    for (int i = 0; i < 4; i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
    Serial.begin(115200);
}

void loop()
{
    int delayTime = analogRead(13);                 // Read the value of the POT connected to analog pin A0
    delayTime = map(delayTime, 0, 1023, 100, 1000); // Map the analog value to the desired delay range

    // Loop through the LED pins and set the brightness using analogWrite
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            analogWrite(ledPins[j], i * 16);
            Serial.println(i * 16);

            delay(delayTime);
        }
    }
    // Loop through the LED pins and set the brightness using analogWrite
    for (int i = 0; i < 16; i++)
    {
        for (int j = 4; j >= 0; j--)
        {
            analogWrite(ledPins[j], 255 - i * 16);
            Serial.println(255 - i * 16);
            delay(delayTime);
        }
    }
}
