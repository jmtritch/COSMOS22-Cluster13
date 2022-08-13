#define outputA 3
#define outputB 4
#define pulsesPerRot 20

unsigned long lastMillis = 0;
unsigned long lastMillis2 = 0;
int aState;
int aLastState;
int rot = 0;
int counter = 0;
int counter2 = 0;
bool measure = false;
float tds;
float temp;
float ph;
float data[3];

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode (outputA, INPUT);
  pinMode (outputB, INPUT);

  Serial.begin(9600);

  aLastState = digitalRead(outputA);
}

void loop() {
  rot = 0;
  counter = 0;
  counter2 = 0;

  // receiving data from arduino in capsule
  while (Serial.available() > 0) {
    String sensorDta = Serial.readStringUntil('\n');
    //Serial.println(sensorDta);
    if (sensorDta.length() > 1) {
      measure  = true;
    }
    //fillArray(sensorDta);
  }

  if (measure) {
    while (rot < 10) {
      if (millis() - lastMillis > 0) {
        lastMillis = millis();
        aState = digitalRead(outputA);
        digitalWrite(9, HIGH);
        digitalWrite(8, LOW);
        if (aState != aLastState) {
          counter++;
          if (counter % 40 == 0) {
            rot++;
          }
        }
        aLastState = aState;
      }
    }
    digitalWrite(9, LOW);

    while (rot < 20) {
      if (millis() - lastMillis > 0) {
        lastMillis = millis();
        aState = digitalRead(outputA);
        digitalWrite(9, HIGH);
        digitalWrite(8, LOW);
        if (aState != aLastState) {
          counter++;
          if (counter % 40 == 0) {
            rot++;
            Serial.print("Rotation ");
            Serial.println(rot);
          }
        }
        aLastState = aState;
      }
    }
    digitalWrite(9, LOW);

    // delay(10000);

    while (rot < 30) {
      if (millis() - lastMillis > 0) {
        lastMillis = millis();
        aState = digitalRead(outputA);
        digitalWrite(9, HIGH);
        digitalWrite(8, LOW);
        if (aState != aLastState) {
          counter++;
          if (counter % 40 == 0) {
            rot++;
            Serial.print("Rotation ");
            Serial.println(rot);
          }
        }
        aLastState = aState;
      }
    }
    digitalWrite(9, LOW);
  }

  rot = 0;
  aState = digitalRead(outputA);
  int change = 0;
  lastMillis2 = millis();


  while (rot < 29 || change > 4) {
    lastMillis = millis();
    digitalWrite(9, LOW);
    digitalWrite(8, HIGH);
    if (millis() - lastMillis >= 0) {
      lastMillis = millis();
      aState = digitalRead(outputA);
      if (aState != aLastState) {
        aLastState = digitalRead(outputA);
        counter++;
        if (counter % 40 == 0) {
          rot++;
        }
      }
      if (millis() - lastMillis2 > 170) {
        lastMillis2 = millis();
        change = counter - counter2;
        counter2 = counter;
      }
    }
  }
  digitalWrite(8, LOW);
  //delay(10000);
}

/*void fillArray(String txt) {
  int lastIndex = txt.length();
  int startIndex = 0;
  int commaIndex = txt.indexOf(",");

  for (int index = 0; index < 3; index++) {
    data[index] = txt.substring(startIndex, commaIndex).toFloat();
    startIndex = commaIndex + 1;
    commaIndex = txt.indexOf(",", startIndex);
  }
}*/
