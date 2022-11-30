#define HWSERIAL Serial1

void setup() {
  Serial.begin(9600);
  //HWSERIAL.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String msg = Serial.readString();
    Serial.println(msg);
    //HWSERIAL.println(msg, DEC);
  }
}
