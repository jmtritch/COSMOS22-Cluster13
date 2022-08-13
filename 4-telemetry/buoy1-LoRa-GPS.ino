#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
/*
   This sample sketch demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 32, TXPin = 33;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);


#include "heltec.h"
#define BAND    915E6

int counter = 0;
int startTime = millis();
String gpstime;
String hour, minute, second;
String timeStr;

String zero = "0";

void setup()
{
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, false /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);

  Serial.begin(115200); //for gps
  while(!Serial);
  ss.begin(GPSBaud);
  while(!ss);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPSPlus with an attached GPS module"));
  Serial.print(F("Testing TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (ss.available() > 0)
    if (gps.encode(ss.read()))
      displayInfo();

//  if(millis()-startTime>1000){
//    startTime = millis();
//    sendLora();
//  }

  if (millis()>15000 && gps.charsProcessed()<10){
    Serial.println("No GPS Detected");
    while(true);
  }


  if (gps.location.isValid())
  {
    gpstime += String(gps.location.lat(), 6); 
    gpstime += "," + String(gps.location.lng(), 6);
  }
  else
  {
    gpstime += "N/A";
    gpstime += ",N/A";
  }
  
  if (gps.time.hour() < 10) {
    hour = zero + String(gps.time.hour());
  }
  else {
    hour = String(gps.time.hour());
  }

  if (gps.time.minute() < 10) {
    minute = zero + String(gps.time.minute());
  }
  else {
    minute = String(gps.time.minute());
  }

  if (gps.time.second() < 10) {
    second = zero + String(gps.time.second());
  }
  else {
    second = String(gps.time.second());
  }

  if (gps.date.isValid() && gps.time.isValid()) {
    timeStr = String(gps.date.year()) + "-" + String(gps.date.month()) + "-" + String(gps.date.day()) + " " + hour + ":" + minute + ":" + second;
    gpstime += "," + timeStr + ",";
  }
  else {
    Serial.println("NA");
  }

  if(Serial.available()){
      LoRa.beginPacket();
      LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
      LoRa.print(gpstime + Serial.readStringUntil('\n') + ",1,0");
      Serial.print(gpstime);
      LoRa.endPacket(); 
  }

  //boat 2 = odd seconds
//  if(gps.time.second()%2 == 1){
//    if(Serial.available()){
//      LoRa.beginPacket();
//      LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
//      LoRa.print(gpstime + Serial.readStringUntil('\n') + ",2");
//      Serial.print(gpstime);
//      LoRa.endPacket(); 
//   }
//  }
  

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }

  
}

void sendLora(){
//  Serial.print();
//  Serial.println("-------------------------------------------");
//  LoRa.beginPacket();
//  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
//  LoRa.print();
//  LoRa.endPacket(); 
 }

  
void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(String(gps.location.lat(), 6));
    Serial.print(F(","));
    Serial.print(String(gps.location.lng(), 6));
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
