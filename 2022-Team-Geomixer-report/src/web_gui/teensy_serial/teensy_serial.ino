//#define HWSERIAL Serial1
const int ledPin = 13;
int ledState = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
//  HWSERIAL.begin(9600);
}

void blinkLED() {
  if (ledState == LOW) {
    ledState = HIGH;
  } else {
    ledState = LOW;
  }
  digitalWrite(ledPin, ledState);
}

void loop() {
  if (Serial.available() > 0) {
    String msg = Serial.readString();
    blinkLED();
    Serial.println(msg);
//    HWSERIAL.println(msg, DEC);

  }
}
