## Buoy 2 
### Objectives:
Drop capsule into water using winch system to accurately measure pH, temperature, and total dissolved solids/salinity under the water’s surface
Communicate and distribute data to base station consistently

### Procedure

#### Winch System

We used a DC motor attached to a spool to unwind and wind fishing line, precisely moving the capsule above and below the water’s surface.

We used a rotary encoder in order to document the amount of rotations to figure out the depth of the capsule (each rotation accounting for 20cm of line). 

![dfghjk](https://user-images.githubusercontent.com/73302110/182684151-29b68780-01c8-4524-92e2-1b8f6ac715de.jpeg)

The body of the second buoy was also a CreekKooler cooler.

#### Communication

Arduino collects data in capsule (pH, temperature, TDS)-> Serial Communication with Capsule through telephone wire -> esp32 sends signal to base station through LoRa antenna

![IMG_4692](https://user-images.githubusercontent.com/73302110/182684288-334ee714-ad2c-401f-95b4-82dbfd4d6adc.jpg)


