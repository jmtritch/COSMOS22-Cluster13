#include <ArduinoJson.h>

// Dummy variables
int boat = 1;
float lat = 33.123456;
float lon = -117.123456;
char* tim = "2022-07-22 13:07:55";
float tds = 303.5;
float ph = 7.08;
float temp = 30.15;

// Json document object
StaticJsonDocument<200> json;

void setup() {
  // Enter serial communication at 9600
  Serial.begin(9600);
}

void loop() {
  while(true) {
    // set json parameters to dummy variables
    json["boat"] = boat;
    json["lat"] = lat;
    json["lon"] = lon;
    json["time"] = tim;
    json["tds"] = tds;
    json["ph"] = ph;
    json["temp"] = temp;
    // print json, then newline
    serializeJson(json, Serial);
    Serial.println("");
    // Increment latitude, longitude
    lat += 1;
    lon += 1;
    delay(1000);
  }
}
