#define outputA 13
#define outputB 12
#define pulsesPerRot 20
#define bruh 14
#define moment 13

unsigned long lastMillis = 0;
unsigned long lastMillis2 = 0;
int aState;
int aLastState;
int rot = 0;
int counter = 0;
int counter2 = 0;
bool measure = true;


//
void setup() {
  // put your setup code here, to run once:
  // Pins for motors
  pinMode(bruh, INPUT);
  pinMode(moment, INPUT);



  // Rotation stuff
  pinMode (outputA, OUTPUT);
  pinMode (outputB, OUTPUT);


  Serial.begin (9600);
  // Reads the initial state of the outputA
  aLastState = digitalRead(outputA);
}


void loop() {
  // put your main code here, to run repeatedly:
  rot = 0;
  counter = 0;
  counter2 = 0;
  // receive data from arduino in capsule
  // once received set measure to true

  // Change measure to true when you receiuve a command from the LoRa
  measure = true;

  // List of commands which will drop the capsule to depths 2, 4, 6m
  Serial.println("hi");
  if (measure) {
    Serial.println("First 10 rot");
    while (rot < 8) {
      if (millis() - lastMillis > 0) {
        lastMillis = millis();
        aState = digitalRead(bruh); // Reads the "current" state of the outputA
        digitalWrite(outputA, HIGH);
        digitalWrite(outputB, LOW);
        if (aState != aLastState) {
          Serial.println("Change");
          counter++;
          if (counter % 40 == 0) {
            Serial.print("ROTATION       X");
            Serial.println(rot);
            rot++;
          }
        }
        aLastState = aState; // Updates the previous state of the outputA with the current state
      }
    }
    digitalWrite(outputA, LOW);
    
//##############################################################    
//     Send command to capsule to collect data
//     Receive data from capsule. 
//     Wait until then
//     Then send that info to LoRa to send it out
//##############################################################    
    delay(10000);
Serial.println("second 20 rot");
    while (rot < 16) {


      if (millis() - lastMillis > 0) {
        lastMillis = millis();
        aState = digitalRead(bruh); // Reads the "current" state of the outputA
        digitalWrite(outputA, HIGH);
        digitalWrite(outputB, LOW);

        if (aState != aLastState) {
          counter++;

          if (counter % 40 == 0) {
            rot++;
            Serial.print("Rotation ");
            Serial.println(rot);
          }
        }
        aLastState = aState; // Updates the previous state of the outputA with the current state
      }
    }
    digitalWrite(outputA, LOW);


    
//##############################################################################################
//     Send command to capsule to collect data
//     Receive data from capsule. 
//     Wait until then
//     Then send that info to LoRa to send it out
//##############################################################################################

    
    
    delay(10000);
Serial.println("third 30 rot");
    while (rot < 24) {

      if (millis() - lastMillis > 0) {
        lastMillis = millis();
        aState = digitalRead(bruh); // Reads the "current" state of the outputA
        digitalWrite(outputA, HIGH);
        digitalWrite(outputB, LOW);
        if (aState != aLastState) {
          counter++;
          if (counter % 40 == 0) {
            rot++;
            Serial.print("Rotation ");
            Serial.println(rot);
          }
        }
        aLastState = aState; // Updates the previous state of the outputA with the current state
      }
    }
    digitalWrite(outputA, LOW);
    
/*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*
     Send command to capsule to collect data
     Receive data from capsule. 
     Wait until then
     Then send that info to LoRa to send it out
*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//*//**/
    
    delay(10000);
  }


/*
 * THE REELING IN FEATURE OF THE CODE. THIS PART SEEMS TO WORK.
 */

  rot = 0;
  aState = digitalRead(bruh);
  int change = 0;
  lastMillis2 = millis();
  Serial.println("Reeel up");
  while (rot < 26 || change > 4) {
    lastMillis = millis();
    digitalWrite(outputA, LOW);
    digitalWrite(outputB, HIGH);
    if (millis() - lastMillis >= 0) {
      lastMillis = millis();
      aState = digitalRead(bruh);
      if (aState != aLastState) {
        aLastState = digitalRead(bruh);
        counter++;
        if (counter % 40 == 0) {
          rot++;
          Serial.println(rot);
        }
      }

      //THIS PART MEASURES THE CHANGE IN NUMBER OF NOTCHES IN THE ROTARY ENCODER IN THE PAST 170 MS.
      // IF THIS CHANGE IS LESS THAN 4, AND THE THING HAS ROTATED A SET NUMBER OF TIMES, THE WHILE LOOP WILL BREAK AND THE ROTATION WILL STOP.
      if (millis() - lastMillis2 > 170) {
        lastMillis2 = millis();
        change = counter - counter2;
        counter2 = counter;
      }
    }
  }

  Serial.println("Loosen");
  digitalWrite(outputB, LOW);
  digitalWrite(outputA, HIGH);
  delay(100);
  Serial.println("stop");
  digitalWrite(outputA,LOW);
  delay(10000);
}
