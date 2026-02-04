# 🤖 Gesture Controlled Robot Car

## 📌 Overview
A gesture-controlled robotic car that moves based on hand gestures detected using an **MPU6050 accelerometer & gyroscope**.  
The system communicates wirelessly using **NRF24L01 PA + LNA modules**, enabling real-time and responsive control.

## 📖 Project Description
The project uses hand tilt and motion data captured by the MPU6050 sensor to determine movement directions.  
These signals are transmitted wirelessly to a receiver unit, which processes the data and controls the motors of the robotic car accordingly.

## 🔧 Components Used
- Arduino Nano (x2)
- MPU6050 Accelerometer & Gyroscope
- NRF24L01 PA + LNA Module (x2)
- NRF Adapter (HW-200 Model) (x2)
- L298N Motor Driver
- DC Motors (x4)
- Car Chassis
- Li-ion Batteries (x6)
  - Transmitter Unit: 2 batteries
  - Receiver Unit: 4 batteries

## 📂 Folder Structure
```
gesture-controlled-car/
│
├── Transmitter/
│   └── Arduino code for gesture-based transmitter using MPU6050
│
├── Receiver/
│   └── Arduino code for robot car receiver and motor control
│
├── Circuit Diagrams/
│   ├── transmitter_circuit_gcc.png
│   └── receiver_circuit_gcc.png
│
├── README.md
└── LICENSE
```
## 👨‍💻 Author
Mehedi Hasan Sifat

## 📄 License
This project is licensed under the MIT License.
