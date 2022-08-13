//tds sensor
/*
 Tds sensor to A0, 3.3V with esp32, 5V with Arduino Mega (either Voltage should be fine), Gnd
 Ph sensor to A1, 5V, Gnd
 Temperature sensor to digital 2, 5V, Gnd
 */

#include <EEPROM.h>
#include "GravityTDS.h"
#include <OneWire.h> 
#include <DallasTemperature.h>

#define TdsSensorPin A0       // tds
#define SensorPin A1          // the pH meter Analog output is connected with the Arduino's Analog
#define ONE_WIRE_BUS 2        // temp
#define Offset 0.00
#define samplingInterval 20
#define ArrayLenth 40


// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(ONE_WIRE_BUS); 

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10], temp;
float temperature = 25, tdsValue = 0;
int tempValue;
GravityTDS gravityTds;
int pHArray[ArrayLenth];
int pHArrayIndex = 0;
float rawvalue = 0;

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
  static unsigned long samplingTime = millis();
  static float pHValue,voltage;

  if(millis()-samplingTime > samplingInterval) {
      pHArray[pHArrayIndex++]=analogRead(SensorPin);
      if(pHArrayIndex==ArrayLenth)pHArrayIndex=0;
      rawvalue = avergearray(pHArray, ArrayLenth);
      voltage = avergearray(pHArray, ArrayLenth)*5.0/1024;
      pHValue = -5.553016453*voltage + 28.69378428;
      //pHValue = 3.5*voltage+Offset;
      samplingTime=millis();
  }
  return pHValue;
}

float getTemp(){
      // variables sent back: phValue, temperature, tdsValue
    sensors.requestTemperatures(); // Send the command to get temperature readings
    float temperature = sensors.getTempCByIndex(0);
    return temperature;
}

float getTds(){
    temperature = getTemp();  //add your temperature sensor and read it
    gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
    gravityTds.update();  //sample and calculate
    tdsValue = gravityTds.getTdsValue();  // then get the value, tds value is in ppm
    delay(1000);
    return tdsValue;
}

double avergearray(int* arr, int number){
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0){
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5){   //less than 5, calculated directly statistics
    for(i=0;i<number;i++){
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }else{
    if(arr[0]<arr[1]){
      min = arr[0];max=arr[1];
    }
    else{
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++){
      if(arr[i]<min){
        amount+=min;        //arr<min
        min=arr[i];
      }else {
        if(arr[i]>max){
          amount+=max;    //arr>max
          max=arr[i];
        }else{
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}
