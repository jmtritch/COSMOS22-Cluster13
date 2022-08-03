# **Boat Team**

**Team Members:**  Josh, Justin, Deon, Ty, Daisy

We worked on converting a Traxxas high-speed RC Boat into an autonomous boat: integrated a flight controller, GPS, and a radio for communicating with an autopilot software on a base station computer, designed and printed enclosures for protecting the electronics from water damage, and modified the steering system to be more agile.

## **CAD files**

[PixhawkEnclosure](https://cad.onshape.com/documents/f0dcd2dc360e6153a8aceb5b/w/83c42524679d51935942d68b/e/775b05789a6a2d5d23418cd0?renderMode=0&uiState=62e99a547c7bdb392fe305ba)

[TGY-IA6BReceiverEnclosure](https://cad.onshape.com/documents/975f2f7a7f84f6e907830d6b/w/4012b4122810d31c85e447a8/e/c716113e8b8c94d3e3576a56?renderMode=0&uiState=62e99a12a0feaa2881a1f3e0)

[SikRadioEnclosure1](https://cad.onshape.com/documents/c3391ed66584119709134aad/w/9b98b19a87cd1257f25d6579/e/9a0190f613e11171d804b727?renderMode=0&uiState=62e80763123a4c48368da3a0)

[SikRadioEnclosure2](https://cad.onshape.com/documents/cbe6cff6ed3df61fe2a0e150/w/ee1321990144475658df51f7/e/609a2fe643e35127236df8c1?renderMode=0&uiState=62e99a79c21ec068bef4b431)

[Rudders](https://cad.onshape.com/documents/341f0bfbb7fd9b8641d10de2/w/ccba5a872075a3eeead7d582/e/0432abc8975b2662196b00e9?renderMode=0&uiState=62e99aa0a5f5c9114d3c53d3)

[ExtendedServoArm](https://cad.onshape.com/documents/2f5a1ff8fc77d09ff0f33b28/w/96a95d3afae6904bacc3db46/e/c4438d96de7ada338bfaa74e?renderMode=0&uiState=62e99ac00266bb7317baedc6)

[GPSStand](https://drive.google.com/file/d/1A_vzA1YP445HYMUqo_vrnWkr_7P-FACy/view?usp=sharing)

[FailedPropeller](https://cad.onshape.com/documents/2230b25d323cfa670fe3c34e/w/6c635d2fb56808e4df65ce90/e/1931b7b725fc2400243ae572)

## **Documentation used**

[LUX HD H7](https://getfpv-media.s3.amazonaws.com/wysiwyg/files/LUX-H7-User_Manual_v1.pdf)

[Pixhawk](https://ardupilot.org/copter/docs/common-pixhawk-overview.html)

## **Resources we created**

[FinalProjectPresentation](https://docs.google.com/presentation/d/17up9BzliWYm42svsFPQnfsFhXZzlgkU9WlSPDdMP5Go/edit?usp=sharing)

## **Timeline**

### **Installing ArduPilot and Mission Planner**

* After we unboxed the flight controllers (Lux HD H7), we flashed ArduPilot, an open-source autopilot system for RC vehicles, onto the board. Initially, the flight controllers were not detected by the computer, so we had to install virtual com ports and DFU drivers. After connecting the board to STM32cube, we wiped the device and successfully flashed the firmware. 
* Ardupilot is the firmware for the flight controller, and Mission Planner is a ground control system for controlling the vehicle remotely. This software proved to be a large hurdle for the group, since the maze-like UI, hundreds of customizable functions, and parameters hid the basic features required to run the boat. After extensive research on RC forums and several Youtube videos, we became familiar with the program and changed specific parameters to fit our boat. ArduPilot is meant for drones and land vehicles, so all the features of ardupilot are meant to fit these machines. Instead, we built what is called an “arduboat:” a boat with ardupilot firmware. This allows for automation and all the same features as a drone. After installing and connecting the board, we moved onto the auxiliary hardware of the boat.

### **Electronics**

#### **Lux HD H7: Pin diagrams**

* After setting up the flight controllers, we looked at the specific pinout diagrams for our board. These diagrams explained what each pin was used for which allowed us to connect the flight controller to each of the devices correctly.

#### **Soldering**

* After a week of making unsecure connections with tape, Ivan taught us how to solder, which allowed us to solder pin headers to the flight controller and female headers to external components, so we could easily plug in components into the flight controller.

#### **Sik radio connection**

* We used 2 Sik radios, with one of the radios connected to a laptop and another radio hooked up to the flight controller. The sik radios link up to each other and flash different colors to tell the user its connection status. For example, blinking green lights represent 2 radios searching for a connection, while solid green means they have established a connection with one another. Initially, the radios were not connecting, with one of the radios always turning red. However, we later discovered that the connection between the radios depended on their air speed, net ID, and firmware. In order to configure these settings, we paired the radios by changing the net ID, airspeed, and firmware to match in qgroundcontrol. We used only one pair of radios in our test, but using multiple pairs would require different net IDs to avoid interference.

#### **GPS**

* Initially, wiring the GPS proved to be a challenge. Two of the GPS wires were black, with only one as ground. After opening the GPS, we found that the thicker black wire represented ground. Later, we wired the GPS to the board but made the mistake of connecting Rx to Rx and Tx to Tx rather than connecting respective receiving and transmitting wires together. After solving this problem, the GPS functioned properly. While troubleshooting, we made a few unfortunate mistakes and burnt two GPSs.

#### **Burning flight controllers**

* Instead of stepping down the voltage of one of our batteries to 7.4 volts before connecting it to the flight controller, one of our teammates accidentally plugged our flight controller directly into the 12.6 volt output of the lipo, instantly overloading the board.

#### **Batteries**

* We did not want to use expensive Traxxas batteries, so we instead soldered 3 cell lipo batteries. We also utilized plug-in battery monitors to alarm us if the batteries died.

### **Manual three-channel RC control**

* We decided to use another RC controller (TGY-i6S) instead of the default Traxxas controller because we needed more channels in order to override autonomous control and switch to manual control. We first tested manual control by pairing the receiver, which uses PWM to control the servo and ESC, with the RC controller. This was a fairly straightforward process, but we had to ensure that the joysticks and switch on the controller were configured to the right channels. We could manually test which channels corresponded to the servo and throttle by navigating to the menu and individually testing each motor. On a side note, we could only pair the default Traxxas controllers outside the classroom, likely due to interference.

### **3D-printed water resistant enclosures for electronics**

* For all of our electronics, we printed water-resistant enclosures:
    * For the radio and receiver, we printed cases with tight lids and holes for external wires to pass through. These holes were sealed with hot glue although we would have preferred to use silicon as a more professional solution.
    * For the flight controller, we designed and printed a watertight enclosure and a mount for the enclosure which interfaced with holes already present on the boat.
    * In the end these enclosures proved advantageous with no damaged electronics while testing the boat.

### **First pool test!**

* After our first boat test in the pool, we decided to 3D-print larger propellers because it seemed like the boat did not have enough power to comfortably pull the load (buoy). We decided to design and print propellers around twice the size of the original propeller and made a few versions, each with a varied number of blades (two, three, and four). However, because we used PLA, a fairly brittle plastic, and didn’t add reinforcements to our design, the propellers broke in the water when the throttle was pushed too far. We later realized that the propeller was not the problem at all; if the boat was just operated at a low speed, not displacing the water too much, it could easily pull the load.
* We also found that the turning provided by the included rudder was far too slow with a really large turning radius. We suspected that this was due to the small surface area of the included rudder. We also noticed that though the servo had 180 degrees of freedom, the rudder only had about 90 degrees of freedom. 
* With these observations in mind, we set out to design our own rudders and servo attachment to improve turning agility.

### **Second pool test!**

* In our second pool test, we tested our new steering system, which worked better than we expected, allowing us to make very tight turns and easily maneuver within the skinny pool lane we had access to. This was a result of two modifications to the original steering system:
    * Reorienting the servo to accommodate a longer custom 3D printed lever arm 
        * This increased the linear motion of the linkage that connects the servo to the rudder thereby increasing the rudder’s range of motion from ~90 degrees to almost 180 degrees
    * Designing a larger rudder which provided more surface area
        * This also helped reduce the turning radius; however, our first design was excessively large which both looked clumsy and produced unwanted drag even at our slow operating speeds, so we iterated on the design making smaller sizes when we got back to the classroom
        * Our rudder designs also have a hole for water to pass through to the cooling system within the boat.

### **Third pool test!**

* In our third pool test, we compared how the boat performed with different rudder sizes and found that the smaller rudder we tested didn’t sacrifice the turning radius and caused less drag than the larger rudder. We ultimately settled on the medium sized rudder we designed
* NOTE: we also designed and printed an even smaller rudder but didn’t have time to test it. It likely would’ve performed comparably to the rudder we settled on, but we didn’t want to use it in our final trial because we didn’t test it and already knew the medium sized rudder performed well.

### **Pivot to PixHawk and autonomous navigation**

* After two weeks and four days of struggling with the Lux HD H7 flight controller, Jack gave us two Pixhawk 2.4.8s. This specific type of flight controller is loved by hobbyists for its functionality, robustness, and ease of use. We quickly researched the basics of the device and started anew. After a day and a half, we managed to make more progress with it than we had with the Lux HD H7. 
* One of the 2 Pixhawks broke in an accident where power was plugged into the wrong spot, causing the board to short
* To simulate autonomous navigation with the boat without having to go in the water, we used Mission Planner to map points near the lab and run the autonomous mission while walking the boat around. This allowed us to see how the throttle and steering reacted as we moved it off-track. Through our testing, we noticed that the rudder was not moving and suspected that the channels were incorrectly configured. We were further convinced when we noticed that the throttle motor appeared to be modulating its speed in an attempt to steer. After experimenting with channel and motor configurations in Mission Planner, we realized that the PixHawk was wired incorrectly, and we changed the throttle from main out 1 to main out 2 and the servo from main out 8 to main out 3, which solved the problem. 

### **Lake day!**

* In the first test, we created a simple autonomous path, but when we ran it, the boat acted sporadically, going in circles, and we suspected that it was because of the rudder, so we inverted the servo rotation direction in Mission Planner and the autonomous navigation started working well. We then mapped a 27 waypoint grid-patterned path for the final mission, so the boat could stop 27 times to collect data from the lake and cover more area. 
* After adding the buoy though, the boat was not able to maintain its heading and started straying away from its path. Unfortunately, we ran out of time before we could get a chance to troubleshoot the issue, but we had our suspicions as to why it didn’t work:
    * The propeller possibly wasn’t generating enough thrust to pull the additional load (buoy)
    * The Sik radio which communicated with Mission Planner to get navigation instructions had the same frequency as the LoRa radio on the buoy and they may have been interfering with one another
    * For manual control: the radio receiver’s antennas were mounted very near water level and may have even been beneath water level in the boat, and since the radio communication only works in line of sight, there may have been complete loss of communication with the water blocking the signal
