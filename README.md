# Pinball Machine Prototype

## Overview
This project was meant to demonstrate knowledge in mechanical and electrical engineering by applying knowledge of both to create a pinball machine from scratch.
An Arduino Mega 2560 implements the game's control loop. The machine automatically tracks losses, displays scores, and includes motorized effects for visually stimulating gameplay.

## Gameplay Flow
1. **Start Game**:
   - Power on machine
   - Press yellow **START** button
   - Startup song plays
   - Servo gate opens, DC motor starts spinning
2. **Play**:
   - Score points by passing through scoring areas or triggering bumper
   - Avoid losing the ball
3. **Game Over**:
   - After 3 losses, servo gate closes
   - Final score flashes on display

---

## Mechanical Design Notes
- The **playfield** is removable for easy maintenance
- Electrical components are **mounted underneath** the playfield
- Separate flipper designs for left and right sides
<img width="447" height="598" alt="Screenshot 2025-08-09 171218" src="https://github.com/user-attachments/assets/91775556-a96b-4d0b-90ce-80c3f6b3f601" />
<img width="504" height="691" alt="Screenshot 2025-08-09 171356" src="https://github.com/user-attachments/assets/d47f96fb-5a60-477a-b7b3-f976e852b77b" />

---

## Features
- **Multiple Scoring Mechanisms**
  - **IR Sensor – Tunnel**: +2 points
  - **IR Sensor – Basketball Hoop**: +3 points
  - **Piezoelectric Bumper**: Triggers a solenoid bumper and adds points
- **Game State Tracking**
  - IR sensor detects when the ball exits the playfield
  - Player gets 3 lives before the game ends
- **Flippers**
  - Left and right flippers controlled by push buttons, powered by solenoids
  - Separate designs for symmetry and mechanical integrity
![IMG_0637-ezgif com-cut](https://github.com/user-attachments/assets/749389a4-6346-47ac-9ed8-d51877121b97)
- **Display**
  - 2 7-segment displays show score and flashes final score at game over
  - Implemented single Shift Register + NPN BJT to control both displays
![IMG_8091-ezgif com-optimize](https://github.com/user-attachments/assets/9661989d-3636-497e-aad0-ad898bbd5095)
- **Actuator Playfield Effects**
  - **DC motor** spins a basketball obstacle
  - **Servo motor** acts as a gate to start the game
  - **Solenoid** facilitates bumper movement when triggered by piezoelectric device 

---

## Hardware Used
- **Arduino** (x1)
- **IR LEDs** (x4)
- **Phototransistors** (x4)
- **Piezoelectric sensor** (x2)
- **LM358P Op-Amp** (x1)
- **N-channel MOSFET** (x5)
- **Solenoid** (x3)
- **Power resistor** (x4)
- **Electrolytic capacitor** (x2)
- **DC motor** (x1)
- **Servo motor** (x1)
- **Push buttons** (x3)
- **Multiple power supplies**
- **Wood and 3D printed plastic** for structure and components

---

## Circuit Design
### Scoring Circuits
- **IR sensor circuits**
<img width="317" height="210" alt="Screenshot 2025-08-09 172204" src="https://github.com/user-attachments/assets/e682fe37-d586-48d7-a5cd-d91e2bb1092e" />

- **Piezoelectric bumper circuit**:
  - Piezo signal buffered by LM358P Op-Amp (low output impedance)
  - Buffered signal to Arduino interrupt pin
  - Arduino sends digital signal to nMOS circuit to power the solenoid
<img width="323" height="206" alt="Screenshot 2025-08-09 172851" src="https://github.com/user-attachments/assets/4e98e622-6243-4b4e-a042-4232efbe446e" />

### Actuator Circuits
- **DC/Servo motor**: Powered via MOSFET with diode protection, using PWM from Arduino
<img width="200" height="200" alt="Screenshot 2025-08-09 173259" src="https://github.com/user-attachments/assets/301c071b-6133-4bf9-95f1-ef4d3b9ce544" />

- **Solenoid Circuit**: Controlled via Arduino PWM
<img width="200" height="200" alt="Screenshot 2025-08-09 173821" src="https://github.com/user-attachments/assets/aaea73eb-6282-42d1-8789-71f20b9f95a8" />

### 7-segment Display Circuit
<img width="529" height="291" alt="Screenshot 2025-08-09 173951" src="https://github.com/user-attachments/assets/2f2e7e9e-a63e-4b34-97e1-b9d69fc9dba8" />
<img width="249" height="309" alt="Screenshot 2025-08-09 174040" src="https://github.com/user-attachments/assets/54107e84-1113-4a93-aa22-1f71b6f9d62a" />

---

## First Prototype Gameplay
![IMG_09501-ezgif com-optimize](https://github.com/user-attachments/assets/b2f31020-c78a-4f81-9c5f-7753867caad5)
[Full Video](https://drive.google.com/file/d/1_mbPmkRjFcmYeiSPWysJYVk0tYINZYB5/view?usp=sharing)

