/*
Credits: https://how2electronics.com/ph-meter-using-ph-sensor-arduino-oled/ ; 
https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806;
https://wiki.dfrobot.com/Gravity__Analog_TDS_Sensor___Meter_For_Arduino_SKU__SEN0244
*/

//tds sensor
#include <EEPROM.h>
#include "GravityTDS.h"

//tds sensor pin
#define TdsSensorPin A0

//ph sensor pin
#define SensorPin A1          // the pH meter Analog output is connected with the Arduino's Analog


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
    Serial.begin(9600);
    gravityTds.setPin(TdsSensorPin);
    gravityTds.setAref(3.3);  //reference voltage on ADC, default 5.0V on Arduino UNO
    gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
    gravityTds.begin();  //initialization

    Serial.println("tds sensor begin");
    
    //for ph
    pinMode(13,OUTPUT);
    Serial.println("Ready");    //Test the serial monitor

    //for temp
    sensors.begin();
    
}

void loop()
{
    //temperature = readTemperature();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value, tds value is in ppm
    delay(1000);
    
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
    float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
    phValue=3.5*phValue;                      //convert the millivolt into pH value
    // variables sent back: phValue, temperature, tdsValue
    sensors.requestTemperatures(); // Send the command to get temperature readings
    Serial.println("Temperature: " + String(sensors.getTempCByIndex(0)) + " \npH: " + String(phValue) + " \nTDS: " +  String(tdsValue));
    
    Serial.println();
    Serial.println();

    digitalWrite(13, HIGH);       
    delay(800);
    digitalWrite(13, LOW);
}
//send as json to esp32
