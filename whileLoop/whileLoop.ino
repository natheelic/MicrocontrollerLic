// Define the pins for the switches
// byte switchPins[] = {2, 3, 4};
byte switchPins[] = {13, 12, 14};

// Define the pins for the LEDs
// byte ledPins[] = {5, 6, 7, 8, 9, 10, 11, 12};
byte ledPins[] = {15, 2, 4, 16, 17, 5, 18, 19};

void setup()
{
    Serial.begin(115200);
    // Set the switch pins as inputs
    for (int i = 0; i < 3; i++)
    {
        pinMode(switchPins[i], INPUT_PULLUP);
    }
    // Set the LED pins as outputs
    for (int i = 0; i < 8; i++)
    {
        pinMode(ledPins[i], OUTPUT);
    }
}

void loop()
{
    byte switch1State = digitalRead(switchPins[0]);
    if (switch1State == LOW)
    {
        while (switch1State == HIGH)
        {
            for (byte j = 0; j < 8; j++)
            {
                digitalWrite(ledPins[j], HIGH);
            }
            switch1State = digitalRead(switchPins[0]);
            if (switch1State == LOW)
            {
                break;
            }
        }
    }

    for (byte j = 0; j < 8; j++)
    {
        digitalWrite(ledPins[j], LOW);
    }
}