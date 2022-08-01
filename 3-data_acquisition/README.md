## UCSD COSMOS 2022
### cluster13 - DAQ
***
#### Team Members
Charlie Wright, Sannie Wan, Isabella Lu

<img width="400" alt="Screen Shot 2022-08-01 at 10 14 09 AM" src="https://user-images.githubusercontent.com/98288767/182205438-cabe9342-86b9-47fa-8be7-d52cbd639ce0.png">

***
#### Project and Purpose
Cluster 13 H4O plans to build an autonomous boat that'll tug a buoy along. The buoy will collect data (pH, temperature, tds) using a capsule that'll drop down into the water and send it back to the database via LoRa.

Group 6 DAQ's role in this project is to assure accurate data readings and program the necessary hardware to send capsule data back to the buoy, in order for the buoy to be able to send the data to the database.

***
#### Tasks and Responsibilities
- Hardware: Sensors (calibration, wiring, programming)
- Software: Serial communication (ESP32 - Arduino Uno)
<img width="400" alt="Screen Shot 2022-08-01 at 10 35 17 AM" src="https://user-images.githubusercontent.com/98288767/182208779-105195eb-0233-4483-9548-88205e36d9cb.png">

***
#### Materials
Hardware:
- Arduino UNO, MEGA, and NANO
- ESP32
- Jumper wires, wires
- Protoboard, breadboard
- Solder
- Hall effect sensor (to pull capsule back up)
- Sensors: pH, TDS (total dissolved solids), and temperature
- Calibration solutions: [pH](https://www.amazon.com/Atlas-Scientific-Electrode-Calibration-Solution/dp/B0063MVU5S/ref=sr_1_2_sspa?crid=LED7BUK1NYP2&keywords=potassium+chloride+storage+solution&qid=1658250704&sprefix=potassium+chloride+storagesolution%2Caps%2C111&sr=8-2-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUEyVVhRT1dUNFI3WFVNJmVuY3J5cHRlZElkPUEwMzc3MzExMzJVWTJLQjAzWkM5VSZlbmNyeXB0ZWRBZElkPUEwNTY5NzczWVZISkNQUllaMFRKJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==), [tds](https://www.amazon.com/HM-Digital-1000ppm-Calibration-Solution/dp/B001FD6WZ8/ref=sr_1_3?crid=1MKJVGSDON4SL&keywords=tds+calibration+solution+1000+ppm&qid=1658167608&sprefix=tds+calibration+solution%2Caps%2C115&sr=8-3)
- [Thermometer](https://www.amazon.com/Yacumama-Instant-Thermometer-WATERPROOF-Grilling/dp/B087XBXFM6/ref=sr_1_1_sspa?crid=1ZI7NBGGZ0YM0&keywords=water+temperature+thermometer&qid=1658167757&sprefix=water+tempera%2Caps%2C157&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExVk9NRDJTVkhOWTNWJmVuY3J5cHRlZElkPUEwNTUzMDk5QUw2R1ZDU1ZVU0EwJmVuY3J5cHRlZEFkSWQ9QTA0NTQyMTUzNEJJNzJOR0ZHWTImd2lkZ2V0TmFtZT1zcF9hdGYmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl) (temp sensor calibration)

Software:
- Arduino IDE
- Github
- Google Photos
- Discord
- Onshape
<img width="400" alt="Screen Shot 2022-08-01 at 10 51 04 AM" src="https://user-images.githubusercontent.com/98288767/182211223-1b56824c-7c58-463b-803d-c1d5286bc7ce.png">

***
#### Github Navigation
- find older codes in the "old" folder, most of these are not being used
- for basic serial communication between two arduinos, check out the arduinomegaserial folder
- basic serial communication between esp 32 and arduino is in esp32-serial folder
- finalized codes are the following files
<img width="899" alt="Screen Shot 2022-08-01 at 9 54 59 AM" src="https://user-images.githubusercontent.com/98288767/182202442-91adfa5f-bfee-48e5-af5b-348008c43159.png">
