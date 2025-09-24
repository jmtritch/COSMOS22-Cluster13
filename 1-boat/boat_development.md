# Autonomous Boat Development

This document summarizes the engineering process for converting a Traxxas high-speed RC Boat into an autonomous surface vehicle. It highlights key technical challenges, design iterations, and solutions.

---

## Flight Controller and Software Setup

- Installed **ArduPilot firmware** on Lux HD H7 flight controllers using STM32Cube. Encountered driver/port issues that required reflashing and configuring DFU drivers.  
- Used **Mission Planner**, an open-source ground control system, to configure autonomous navigation. Since ArduPilot is primarily designed for drones and land vehicles, we adapted it for use as an "ArduBoat."  
- After extensive tuning, we transitioned from Lux HD H7 boards to **Pixhawk 2.4.8**, which proved more robust and easier to configure.  

---

## Electronics and Wiring

- Studied pinout diagrams to ensure proper connections to servos, ESC, GPS, and radios.  
- Added headers and connectors via soldering to improve reliability over temporary taped connections.  
- Implemented **Sik radio modules** for ground-to-boat communication; configured IDs, firmware, and baud rates for stable pairing.  
- Integrated GPS, troubleshooting wiring mistakes and verifying proper Tx/Rx connections.  

---

## Power Systems

- Built and soldered **3-cell LiPo battery packs** as an alternative to stock Traxxas batteries.  
- Incorporated battery monitors to provide low-voltage alarms and prevent controller overload.  
- Learned the importance of voltage regulation after accidentally overloading one flight controller with direct 12.6V input.  

---

## RC and Manual Override

- Configured a 3-channel **TGY-i6S RC controller** for manual control and autonomous override.  
- Verified PWM signals for servo and throttle through Mission Planner.  
- Ensured correct channel mapping for seamless switching between manual and autonomous modes.  

---

## Mechanical Design and 3D Printing

- Designed and printed **water-resistant enclosures** for flight controllers, radios, and receivers. Enclosures successfully prevented damage during water testing.  
- Iterated through **3D-printed propeller designs** (2-, 3-, and 4-blade) to improve thrust. PLA proved brittle, and larger propellers broke under load. Ultimately determined that the boat could handle pulling loads at reduced throttle without oversized propellers.  
- Designed custom **rudders and servo linkages** to improve maneuverability. Iterations increased rudder range of motion from ~90° to ~180°, dramatically improving turning radius.  

---

## Testing and Iterations

### Pool Tests
- Verified basic propulsion and turning.  
- Identified rudder surface area and servo linkage as limiting factors, then refined designs for improved handling.  

### Autonomous Trials
- Configured Pixhawk outputs to correct miswired throttle and servo channels.  
- Successfully simulated autonomous navigation using Mission Planner paths.  

### Lake Test
- Conducted field test with a 27-waypoint grid path to enable data collection stops.  
- Initial autonomous runs were successful, but pulling the buoy introduced challenges:  
  - Possible insufficient thrust for load.  
  - Potential interference between **Sik radio** (control) and **LoRa radio** (telemetry).  
  - Manual RC signals may have been blocked when antenna tips were near/below water level.  

---

## Lessons Learned

- Robust **power regulation** is essential for protecting sensitive controllers.  
- Iterative **mechanical design** (rudders, enclosures, propellers) was critical to reliable performance.  
- **Autonomous navigation** worked reliably when the boat was unloaded, but load and radio interference remain open challenges for future work.  
