/*
  Tds sensor to A0, 3.3V with esp32, 5V with Arduino Mega (either Voltage should be fine), Gnd
  Ph sensor to A1, 5V, Gnd
  Temperature sensor to digital 2, 5V, Gnd



  Credits: https://how2electronics.com/ph-meter-using-ph-sensor-arduino-oled/ ;
  https://create.arduino.cc/projecthub/TheGadgetBoy/ds18b20-digital-temperature-sensor-and-arduino-9cc806;
  https://wiki.dfrobot.com/Gravity__Analog_TDS_Sensor___Meter_For_Arduino_SKU__SEN0244
*/

#include <EEPROM.h>
#include "GravityTDS.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define TdsSensorPin A0 // tds
#define SensorPin A1    // the pH meter Analog output is connected with the Arduino's Analog
#define ONE_WIRE_BUS 2  // temp
#define Offset 0.00
#define samplingInterval 20
#define ArrayLength 40

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
GravityTDS gravityTds;

unsigned long int avgValue;
float temperature = 25, tdsValue = 0;
int tempValue;
int pHArray[ArrayLength];
int pHArrayIndex = 0;
int pHValue = 7;
int buf[10], temp;

void setup()
{
  Serial.begin(115200);
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);

  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.setAdcRange(1024);
  gravityTds.begin();

  //temp
  sensors.begin();

  delay(100);
}

void loop()
{
  float temp = getTemp();
  float ph = getPh();
  float tds = getTds();

  Serial.println(String(temp) + "," + String(tds) + "," + String(ph));
  delay(1000);
}



float getTemp() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  return temperature;
}

float getTds() {
  temperature = getTemp();
  gravityTds.setTemperature(temperature);
  gravityTds.update();
  tdsValue = gravityTds.getTdsValue();
  return tdsValue;
}

float getPh(){
  
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
  float pHValue=(float)avgValue/6; //convert the analog into millivolt
  pHValue=-0.0268*pHValue + 26.7;                      //convert the millivolt into pH value
  return pHValue;

}
