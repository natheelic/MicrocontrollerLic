
// Define the pins for the switches
const int switch1Pin = 2;
const int switch2Pin = 3;
const int switch3Pin = 4;

// Define the pins for the LEDs
const int led1Pin = 5;
const int led2Pin = 6;
const int led3Pin = 7;
const int led4Pin = 8;
const int led5Pin = 9;
const int led6Pin = 10;
const int led7Pin = 11;
const int led8Pin = 12;

void setup()
{
    // Set the switch pins as inputs
    pinMode(switch1Pin, INPUT);
    pinMode(switch2Pin, INPUT);
    pinMode(switch3Pin, INPUT);

    // Set the LED pins as outputs
    pinMode(led1Pin, OUTPUT);
    pinMode(led2Pin, OUTPUT);
    pinMode(led3Pin, OUTPUT);
    pinMode(led4Pin, OUTPUT);
    pinMode(led5Pin, OUTPUT);
    pinMode(led6Pin, OUTPUT);
    pinMode(led7Pin, OUTPUT);
    pinMode(led8Pin, OUTPUT);
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
