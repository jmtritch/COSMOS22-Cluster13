## Capsule

### Objectives:
* Create a capsule that can be easily lowered beneath the water
* Capsule has the capacity to collect data via sensors
* Capsule can send data back to buoy via serial communication

### Procedure:
For the body of the capsule, we used the Zulkit Junction Box, which was watertight and could thus protect the electronics inside. 
![image](https://user-images.githubusercontent.com/70926137/182709478-85e05dbd-a2c3-4f56-ade9-f501deb7ffae.png)
Inside of the capsule, we used an Arduino nano to control the sensors and a battery pack to power the Arduino. 
![image](https://github.com/jmtritch/COSMOS22-Cluster13/blob/buoy/2-buoy/Capsule/20220803_135547.jpg)
In order to allow the sensors to protrude from the capsule while also preventing water leakage, the sensors are threaded through cable grommets and secured in place using epoxy.
![image](https://user-images.githubusercontent.com/70926137/182903068-d9c2d733-baae-4e38-951e-a7a9b8f721f3.png)
A telephone wire is used to establish serial communication between the microcontroller in the buoy and the arduino nano inside the capsule. 
![image](https://user-images.githubusercontent.com/70926137/182903595-28e5a9de-63e3-41d6-b682-5aa00ea15be5.png)
To reel the capsule back up and lower it into the water, a strong fishing line is wrapped around the spool and tied to the capsule. 
![image](https://user-images.githubusercontent.com/70926137/182903745-21ffde39-6640-40e5-8894-fe2402aac0bd.png)
Finally, weights are tied to the exterior of the capsule to make it heavy enough to sink in the water. 
![image](https://user-images.githubusercontent.com/70926137/182903913-d5692f4a-29f6-433a-9198-568cfb2edc3d.png)

### Final Product:
![image](https://user-images.githubusercontent.com/70926137/182904012-c394ebfd-dd2a-4212-9b70-3a3644fd2001.png)
![image](https://user-images.githubusercontent.com/70926137/182904428-8a0eb9d4-5f30-4ceb-8788-622fd5c63b79.png)
![image](https://user-images.githubusercontent.com/70926137/182904569-da04a9a2-df51-49e9-9940-fb6951fed0a4.png)

We successfully created a watertight capsule that was capable of sinking below the surface of the water to collect data. However, the external weights added too much weight to the capsule, causing some difficulties when reeling it back up. Additionally, there were some problems when communicating the data attained from the capsule sensors to the base station. To avoid these issues, the weights should be inside the capsule, and the telephone wire should be shortened to avoid data loss. 
