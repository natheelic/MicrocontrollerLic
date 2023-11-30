
// Define the pins for the switches
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
        Serial.print("Switch ");
        Serial.println(i + 1);
    }
    // Set the LED pins as outputs
    for (int i = 0; i < 8; i++)
    {
        pinMode(ledPins[i], OUTPUT);
        Serial.print("LED ");
        Serial.println(i + 1);
    }
}

void loop()
{
    // Read the state of the switches
    int switch1State = digitalRead(switchPins[0]);
    int switch2State = digitalRead(switchPins[1]);
    int switch3State = digitalRead(switchPins[2]);

    // Control the LEDs based on the switch states
    if (switch1State == LOW)
    {
        digitalWrite(ledPins[0], HIGH);
        digitalWrite(ledPins[1], HIGH);
        digitalWrite(ledPins[2], HIGH);
        // for(int i = 0; i < 3; i++){
        //     digitalWrite(ledPins[i], HIGH);
        // }
    }
    else
    {
        digitalWrite(ledPins[0], LOW);
        digitalWrite(ledPins[1], LOW);
        digitalWrite(ledPins[2], LOW);
        // for(int i = 0; i < 3; i++){
        //     digitalWrite(ledPins[i], LOW);
        // }
    }
}
