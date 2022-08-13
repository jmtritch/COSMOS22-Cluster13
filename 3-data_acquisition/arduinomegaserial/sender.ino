#include <SoftwareSerial.h>

SoftwareSerial portOne(4, 5); // RX, TX

int LEDpin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial);
//
//  portOne.begin(9600);

  pinMode(LEDpin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.write("hello\n");
  delay(500);

  }
