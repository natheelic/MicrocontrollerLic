byte potPin = 27;
byte ledPin[] = { 15, 2, 4, 16, 17, 5, 18, 19 };
void setup() {

    Serial.begin(115200);

    for (int i = 0; i < 8; i++) {
    pinMode(ledPin[i], OUTPUT);
  }
}

void loop() {
    int readPot = analogRead(potPin);
    Serial.print("READ POT : ");
    Serial.println(readPot);
    if(readPot > 0 && readPot <= 512){
        digitalWrite(ledPin[0], HIGH);
    }else if (readPot == 0){
        digitalWrite(ledPin[0],LOW);
    }
}
