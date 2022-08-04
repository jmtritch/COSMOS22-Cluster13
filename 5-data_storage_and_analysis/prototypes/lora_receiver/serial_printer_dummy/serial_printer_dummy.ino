#include <ArduinoJson.h>



void setup() {
  Serial.begin(9600);
}

void loop() {
  int i = 1;
  while(true) {
    Serial.print("Sussy ");
    Serial.println(i);

    i += 1;
    delay(1);
  }
}
