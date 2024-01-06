#define LED1 17
#define LED2 16
#define LED3 4
#define LED4 0
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
    pinMode(LED4, OUTPUT);      // Set LED4 pin as output
    pinMode(SW1, INPUT_PULLUP); // Set SW1 pin as input
    pinMode(SW2, INPUT_PULLUP); // Set SW2 pin as input
    pinMode(SW3, INPUT_PULLUP); // Set SW3 pin as input
    pinMode(SW4, INPUT_PULLUP); // Set SW4 pin as input
}

void loop()
{
    static bool previousSw1State = true; // Variable to store the previous state of SW1
    static bool previousSw2State = true; // Variable to store the previous state of SW2
    static bool previousSw3State = true; // Variable to store the previous state of SW3
    static bool previousSw4State = true; // Variable to store the previous state of SW4

    bool currentSw1State = digitalRead(SW1); // Read the current state of SW1
    bool currentSw2State = digitalRead(SW2); // Read the current state of SW2
    bool currentSw3State = digitalRead(SW3); // Read the current state of SW3
    bool currentSw4State = digitalRead(SW4); // Read the current state of SW4

    if (currentSw1State != previousSw1State) // Check if SW1 state has changed
    {
        if (currentSw1State == LOW) // Check if SW1 is pressed
        {
            digitalWrite(LED1, !digitalRead(LED1)); // Toggle the state of LED1
        }
        Serial.println("SW1 is pressed");
        previousSw1State = currentSw1State; // Update the previous state of SW1
    }

    if (currentSw2State != previousSw2State) // Check if SW2 state has changed
    {
        if (currentSw2State == LOW) // Check if SW2 is pressed
        {
            digitalWrite(LED2, !digitalRead(LED2)); // Toggle the state of LED2
        }
        Serial.println("SW2 is pressed");
        previousSw2State = currentSw2State; // Update the previous state of SW2
    }

    if (currentSw3State != previousSw3State) // Check if SW3 state has changed
    {
        if (currentSw3State == LOW) // Check if SW3 is pressed
        {
            digitalWrite(LED3, !digitalRead(LED3)); // Toggle the state of LED3
        }
        Serial.println("SW3 is pressed");
        previousSw3State = currentSw3State; // Update the previous state of SW3
    }

    if (currentSw4State != previousSw4State) // Check if SW4 state has changed
    {
        if (currentSw4State == LOW) // Check if SW4 is pressed
        {
            digitalWrite(LED4, !digitalRead(LED4)); // Toggle the state of LED4
        }
        Serial.println("SW4 is pressed");
        previousSw4State = currentSw4State; // Update the previous state of SW4
    }
}