/*
  Tds sensor to A0, 3.3V with esp32, 5V with Arduino Mega (either Voltage should be fine), Gnd
  Ph sensor to A1, 5V, Gnd
  Temperature sensor to digital 2, 5V, Gnd
*/

/*
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
}

void loop()
{
  float temp = getTemp();
  float ph = getPh();
  float tds = getTds();

  Serial.println(String(temp) + "," + String(tds) + "," + String(ph));
  delay(800);
}

float getPh() {
  static unsigned long samplingTime = millis();
  static float pHValue, voltage;

  if (millis() - samplingTime > samplingInterval) {
    pHArray[pHArrayIndex++] = analogRead(SensorPin);
    if (pHArrayIndex == ArrayLength)pHArrayIndex = 0;
    voltage = avergearray(pHArray, ArrayLength) * 5.0 / 1024;
    pHValue = -5.553016453 * voltage + 28.69378428;
    samplingTime = millis();
  }
  return pHValue;
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
  delay(800);
  return tdsValue;
}

double avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if (number < 5) {
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0]; max = arr[1];
    }
    else {
      min = arr[1]; max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;
          max = arr[i];
        } else {
          amount += arr[i];
        }
      }
    }
    avg = (double)amount / (number - 2);
  }
  return avg;
}
