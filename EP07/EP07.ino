byte buttonPin[] = {21, 22, 23};
byte ledPin[] = {15, 2, 4, 16, 17, 5, 18, 19};

void setup()
{
    for (int i = 0; i < 3; i++)
    {
        pinMode(buttonPin[i], INPUT_PULLUP);
    }
    for (int i = 0; i < 8; i++)
    {
        pinMode(ledPin[i], OUTPUT);
    }
}

void loop()
{
    if (digitalRead(buttonPin[0]) == LOW)
    {
        delay(50);
        for (int i = 0; i < 8; i++)
        {
            digitalWrite(ledPin[i], HIGH);
        }
        while (true)
        {
            if (digitalRead(buttonPin[0]) == LOW)
            {
                delay(50);
                break;
            }
        }
    }
    else if (digitalRead(buttonPin[1]) == LOW)
    {
        delay(50);
        for (int i = 1; i < 8; i += 2)
        {
            digitalWrite(ledPin[i], HIGH);
        }
        while (true)
        {
            if (digitalRead(buttonPin[1]) == LOW)
            {
                delay(50);
                break;
            }
        }
    }
    else if (digitalRead(buttonPin[2]) == LOW)
    {
        delay(50);
        for (int i = 0; i < 8; i += 2)
        {
            digitalWrite(ledPin[i], HIGH);
        }
        while (true)
        {
            if (digitalRead(buttonPin[2]) == LOW)
            {
                delay(50);
                break;
            }
        }
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            digitalWrite(ledPin[i], LOW);
        }
    }
    delay(10);
}