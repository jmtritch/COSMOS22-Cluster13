void setup() {
  Serial.begin(9600);
}

void loop() {
  while(Serial.available() > 0) {
    String sensorDta = Serial.readStringUntil('\n');
    Serial.println(sensorDta);
  }
}
