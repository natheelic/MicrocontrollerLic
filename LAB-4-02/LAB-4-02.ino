const int ledPin1 = 2;
const int ledPin2 = 3;
const int ledPin3 = 4;
const int ledPin4 = 5;

void setup()
{
    Serial.begin(9600);
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);
}

void loop()
{
    if (Serial.available() > 0)
    {
        char data = Serial.read();
        if (data == '1')
        {
            digitalWrite(ledPin1, HIGH);
        }
        else if (data == '2')
        {
            digitalWrite(ledPin2, HIGH);
        }
        else if (data == '3')
        {
            digitalWrite(ledPin3, HIGH);
        }
        else if (data == '4')
        {
            digitalWrite(ledPin4, HIGH);
        }
        else if (data == '0')
        {
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, LOW);
            digitalWrite(ledPin4, LOW);
        }
    }
}
