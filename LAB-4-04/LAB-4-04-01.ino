#define LED1 16
#define LED2 4
#define LED3 0
#define SW1 32
#define SW2 33
#define SW3 25
#define SW4 26

void setup()
{
    Serial.begin(115200);       // Initialize Serial communication
    pinMode(LED1, OUTPUT);      // Set LED1 pin as output
    pinMode(LED2, OUTPUT);      // Set LED2 pin as output
    pinMode(LED3, OUTPUT);      // Set LED3 pin as output
    pinMode(SW1, INPUT_PULLUP); // Set SW1 pin as input
    pinMode(SW2, INPUT_PULLUP); // Set SW2 pin as input
    pinMode(SW3, INPUT_PULLUP); // Set SW3 pin as input
    pinMode(SW4, INPUT_PULLUP); // Set SW4 pin as input
}

void loop()
{
    if (digitalRead(SW1) == LOW)
    {                             // If SW1 is pressed
        digitalWrite(LED1, HIGH); // Turn on LED1
        Serial.println("SW1 is pressed & LED1 is on");
    }
    if (digitalRead(SW2) == LOW)
    {                             // If SW2 is pressed
        digitalWrite(LED2, HIGH); // Turn on LED2
        Serial.println("SW2 is pressed & LED2 is on");
    }
    if (digitalRead(SW3) == LOW)
    {                             // If SW3 is pressed
        digitalWrite(LED3, HIGH); // Turn on LED3
        Serial.println("SW3 is pressed & LED3 is on");
    }
    if (digitalRead(SW4) == LOW)
    {                            // If SW4 is pressed
        digitalWrite(LED1, LOW); // Turn off LED1
        digitalWrite(LED2, LOW); // Turn off LED2
        digitalWrite(LED3, LOW); // Turn off LED3
        Serial.println("SW4 is pressed & all LEDs are off");
    }
}
