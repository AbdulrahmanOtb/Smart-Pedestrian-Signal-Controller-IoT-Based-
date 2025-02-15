# Smart Pedestrian Signal Controller (IoT-Based)

## Overview
The **Smart Pedestrian Signal Controller** is an intelligent traffic management system that optimizes pedestrian crossing times using IoT technology. The system utilizes a microcontroller and UART communication to control traffic signals efficiently based on real-time inputs.

## Features
- **Microcontroller-Based Control**: Uses PIC18F4580 microcontroller for signal management.
- **UART Communication**: Enables real-time data exchange.
- **LCD Display Integration**: Provides visual feedback to pedestrians.
- **Countdown Timer**: Displays remaining time for safe crossing.
- **Interrupt-Driven System**: Ensures quick response to signal changes.
- **Configurable Timing**: Adjustable pedestrian wait and crossing times.

## Getting Started

### Prerequisites
To run the project, you will need:
- **Microcontroller**: PIC18F4580
- **MPLAB X IDE**: For programming the microcontroller
- **Proteus**: For simulation
- **Arduino ESP-01**: For IoT functionalities (optional)

### Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/Smart-Pedestrian-Signal-Controller-IoT-Based/Smart-Pedestrian-Signal-Controller.git
   ```
2. Navigate to the project directory:
   ```sh
   cd Smart-Pedestrian-Signal-Controller
   ```
3. Open the project in **MPLAB X IDE** and configure the **PIC18F4580**.
4. Load the provided hex file `EE366-PROJECT.X.production.hex` into Proteus for simulation.

## Running the Simulation
1. Open the `EE366_Project.pdsprj` file in Proteus.
2. Load the `EE366-PROJECT.X.production.hex` file into the microcontroller.
3. Start the simulation to observe pedestrian signal control behavior.

## Usage
1. The system starts in **default mode**, displaying "Not Allowed for Walking".
2. When a pedestrian press signal is detected (`'G'` command via UART):
   - A countdown is shown: **"Allowed after : X sec"**.
   - The pedestrian light turns green, displaying **"Allowed For : X sec"**.
   - Once the countdown expires, the light returns to red, and the default message is restored.
3. The system handles interrupts to respond to UART commands in real time.

## Project Structure
- **`main.c`**: Contains the core logic for pedestrian signal management.
- **`lcd.h`**: LCD display functions.
- **`config.h`**: Microcontroller configuration settings.
- **`uart_pic18f4580.h`**: UART communication functions.
- **`ESP-01.ino`**: ESP-01 microcontroller script (for IoT functionality).

  
- ## Proteus Simulation Files :
  
  **Default Mode (No Pedestrian Request) , Simulation ( 1 )** : 
  - ![Simulation Default](https://github.com/AbdulrahmanOtb/Smart-Pedestrian-Signal-Controller-IoT-Based-/blob/main/Pedestrian_Signal_Project/Simulation_Default.jpg?raw=true)

 
  **Pedestrian Request Received (Yellow Signal Activation for 5 seconds) , Simulation ( 2 )** 
  - ![Simulation 2](https://github.com/AbdulrahmanOtb/Smart-Pedestrian-Signal-Controller-IoT-Based-/blob/main/Pedestrian_Signal_Project/Simulation_YellowSignal.png?raw=true)
 
  **(Pedestrian Signal in Process (Green Signal Activation) , Simulation ( 3 )**
  - ![Simulation 3](https://github.com/AbdulrahmanOtb/Smart-Pedestrian-Signal-Controller-IoT-Based-/blob/main/Pedestrian_Signal_Project/Simulation_GreenPedestrianSignal.png?raw=true)
 
##
## Project Hardware Prototype : 

  - ![1](https://github.com/AbdulrahmanOtb/Smart-Pedestrian-Signal-Controller-IoT-Based-/blob/main/Pedestrian_Signal_Project/Hardware_1.jpg?raw=true)
  - ![2](https://github.com/AbdulrahmanOtb/Smart-Pedestrian-Signal-Controller-IoT-Based-/blob/main/Pedestrian_Signal_Project/Hardware_2.jpg?raw=true)


##
## Project Video : 

https://drive.google.com/file/d/1IGHWjSNdJ7iQLTD6_HcwIXAZzxv_cCbG/view?usp=drive_link


## Contributing
Contributions are welcome! Fork the repository and create a pull request with your improvements.

## License
This project is open-source and available under the MIT License.

---

