//tds sensor
/*
 Tds sensor to A0, 3.3V with esp32, 5V with Arduino Mega (either Voltage should be fine), Gnd
 Ph sensor to A1, 5V, Gnd
 Temperature sensor to digital 2, 5V, Gnd
 */

#include <EEPROM.h>
#include "GravityTDS.h"

//tds sensor pin
#define TdsSensorPin A1

//ph sensor pin
#define SensorPin A0          // the pH meter Analog output is connected with the Arduino's Analog


//temp stuff
/********************************************************************/
// First we include the libraries
#include <OneWire.h> 
#include <DallasTemperature.h>
/********************************************************************/
// Data wire is plugged into pin 2 on the Arduino 
#define ONE_WIRE_BUS 2
/********************************************************************/
// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 
/********************************************************************/
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);
/********************************************************************/ 



unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10], temp;
float temperature = 25, tdsValue = 0;
int tempValue;
GravityTDS gravityTds;


void setup()
{
    //for tds
    Serial.begin(115200);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(3.3);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization

    //for ph
    pinMode(13,OUTPUT);

    //for temp
    sensors.begin();
    
}

void loop()
{

  float temp=getTemp();
  float ph = getPh();
  float tds=getTds();
  
  Serial.println(String(temp) + "," + String(tds) + "," + String(ph));
  delay(100);

}

float getPh(){
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
    { 
      buf[i]=analogRead(SensorPin);
      delay(10);
    }
  
  for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorPin);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp=buf[i];
        buf[i]=buf[j];
        buf[j]=temp;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue/6; //convert the analog into millivolt
  phValue=-0.027*phValue + 28.6;                      //convert the millivolt into pH value
  return phValue;

}

float getTemp(){
      // variables sent back: phValue, temperature, tdsValue
    sensors.requestTemperatures(); // Send the command to get temperature readings
    float temperature = sensors.getTempCByIndex(0);
    return temperature;
}

float getTds(){
      //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value, tds value is in ppm
    delay(1000);
    return tdsValue;
}
