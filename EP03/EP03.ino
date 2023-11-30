
// Define the pins for the switches
byte switchPins[] = {2, 3, 4};

// Define the pins for the LEDs
byte ledPins[] = {5, 6, 7, 8, 9, 10, 11, 12};

void setup()
{
    Serial.begin(115200);
    // Set the switch pins as inputs
    for (int i = 0; i < 3; i++)
    {
        pinMode(switchPins[i], INPUT_PULLUP);
        Serial.print("Switch ");
        Serial.print(i + 1);
    }
    // Set the LED pins as outputs
    for (int i = 0; i < 8; i++)
    {
        pinMode(ledPins[i], OUTPUT);
        Serial.print("LED ");
        Serial.print(i + 1);
    }
}

void loop()
{
    // Read the state of the switches
    int switch1State = digitalRead(switch1Pin);
    int switch2State = digitalRead(switch2Pin);
    int switch3State = digitalRead(switch3Pin);

    // Control the LEDs based on the switch states
    if (switch1State == HIGH)
    {
        digitalWrite(led1Pin, HIGH);
        digitalWrite(led2Pin, HIGH);
        digitalWrite(led3Pin, HIGH);
    }
    else
    {
        digitalWrite(led1Pin, LOW);
        digitalWrite(led2Pin, LOW);
        digitalWrite(led3Pin, LOW);
    }

    if (switch2State == HIGH)
    {
        digitalWrite(led4Pin, HIGH);
        digitalWrite(led5Pin, HIGH);
        digitalWrite(led6Pin, HIGH);
    }
    else
    {
        digitalWrite(led4Pin, LOW);
        digitalWrite(led5Pin, LOW);
        digitalWrite(led6Pin, LOW);
    }

    if (switch3State == HIGH)
    {
        digitalWrite(led7Pin, HIGH);
        digitalWrite(led8Pin, HIGH);
    }
    else
    {
        digitalWrite(led7Pin, LOW);
        digitalWrite(led8Pin, LOW);
    }
}
