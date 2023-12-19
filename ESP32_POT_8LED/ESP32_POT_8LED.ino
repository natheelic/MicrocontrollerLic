byte potPin = 27;
byte ledPin[] = { 15, 2, 4, 16, 17, 5, 18, 19 };

void runLed(int _Loop) {
    int _off = 8 - _Loop;
    for (int i = 0; i < _Loop; i++) {
        digitalWrite(ledPin[i], HIGH);
    }
    for (int i = _off; i >= 0; i--) {
        digitalWrite(ledPin[i], LOW);
    }
}

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
        runLed(1);    
    }else if(readPot > 512 && readPot <= 1024){
        runLed(2);
    }else if(readPot > 1024 && readPot <= 1536){
        runLed(3);
    }else if(readPot > 1536 && readPot <= 2048){
        runLed(4);
    }else if(readPot > 2048 && readPot <= 2560){
        runLed(5);
    }else if(readPot > 2560 && readPot <= 3072){
        runLed(6);
    }else if(readPot > 3072 && readPot <= 3584){
        runLed(7);
    }else if(readPot > 3584){
        runLed(8);
    }else if (readPot == 0){
        runLed(0);
    }
}
