# Cluster 13 - Buoy Group
Team Members: Milan S, Daniel MS, Isabelle G, Giovanni M, Emily L

## Description:
During the COSMOS 2022 Summer Program, we created two buoys and a capsule responsible for the collection and distribution of data. Both buoys are towed by an autonomous boat and will collect data at certain intervals. 

---

## Buoy #1:
### Objectives:
* Collect data via sensors that would be attached to the exterior of the buoy
* Communicate with base station in order to send data back to be analyzed

### Procedures:
For the body of our buoy, we used the CreekKooler floating cooler, which had the capacity to store the electronics necessary to accomplish the objectives listed above. 

![CreekKooler](https://user-images.githubusercontent.com/70926137/182679093-25eaa8e0-e32a-462e-97bf-209f75be90be.png)

For our sensors, we used a pH probe sensor, a temperature sensor, and a total-dissolved-solids (TDS) sensor

![ph sensor](https://user-images.githubusercontent.com/70926137/182680141-5dc7bae6-08c7-4c90-97dc-01ce8c73e659.png) ![temp sensor](https://user-images.githubusercontent.com/70926137/182680225-b472e310-0f4d-4d31-a4b0-945bbe007790.png) ![tds sensor](https://user-images.githubusercontent.com/70926137/182680311-7f11f9d8-bcc3-4146-9aea-f16d3ca534b1.png)

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



