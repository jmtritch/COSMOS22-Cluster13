#define outputA 3
#define outputB 4
#define pulsesPerRot 20

int counter = 0;
int rot = 0;
int aState;
int aLastState;
unsigned long lastMillis = 0;

void setup() {
  pinMode (outputA, INPUT);
  pinMode (outputB, INPUT);

  Serial.begin (9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
}

void loop() {
  // If the previous and the current state of the outputA are different, that means a Pulse has occured

  if (millis() - lastMillis > 0) {
    lastMillis = millis();
    aState = digitalRead(outputA); // Reads the "current" state of the outputA
    if (aState != aLastState) {
      /*// If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
        if (digitalRead(outputB) != aState) {
        counter ++;
        } else {
        counter --;
        }
        Serial.print("Position: ");
        Serial.println(counter);*/
       counter++;
      
      
      if (counter % 40 == 0) {
        rot +=1;
        Serial.print("Rotation ");
        Serial.println(rot);
      }
    }

    /*if (counter >= pulsesPerRot) {
      static int rots = 0;
      counter = 0;
      Serial.print("          Rotations: ");
      Serial.println(++rots);
      }*/
    aLastState = aState; // Updates the previous state of the outputA with the current state
  }
}
