// Pin definitions for the LEDs
const int LED1_PIN = 2;
const int LED2_PIN = 3;
const int LED3_PIN = 4;
const int LED4_PIN = 5;

// Patterns for the LEDs
const int pattern1[] = {HIGH, LOW, LOW, LOW};
const int pattern2[] = {LOW, HIGH, LOW, LOW};
const int pattern3[] = {LOW, LOW, HIGH, LOW};
const int pattern4[] = {LOW, LOW, LOW, HIGH};

// Function to set the LED states based on the pattern
void setLEDs(const int pattern[])
{
    digitalWrite(LED1_PIN, pattern[0]);
    digitalWrite(LED2_PIN, pattern[1]);
    digitalWrite(LED3_PIN, pattern[2]);
    digitalWrite(LED4_PIN, pattern[3]);
}

void setup()
{
    // Initialize the LED pins as outputs
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);
}

void loop()
{
    // Set the LEDs to pattern 1
    setLEDs(pattern1);
    delay(1000);

    // Set the LEDs to pattern 2
    setLEDs(pattern2);
    delay(1000);

    // Set the LEDs to pattern 3
    setLEDs(pattern3);
    delay(1000);

    // Set the LEDs to pattern 4
    setLEDs(pattern4);
    delay(1000);
}
