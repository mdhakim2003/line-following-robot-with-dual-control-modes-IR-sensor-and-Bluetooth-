# Arduino Robot Car with IR Sensors and Bluetooth Control

## 📖 Overview
An Arduino-based robot car that operates in two modes: autonomous line-following using IR sensors, and manual control via Bluetooth commands. A push button allows switching between modes, while LEDs and a buzzer provide interactive feedback. The system uses an L298N motor driver for precise motor control.

---

## ✨ Features
- **Dual Mode Operation**: IR sensor line-following or Bluetooth manual control  
- **Line Following**: Detects black line using two IR sensors and adjusts direction  
- **Bluetooth Control**: Commands for forward, left, right, stop, horn, and LEDs  
- **Interactive Feedback**: Buzzer honk and LED indicators  
- **Debounce Logic**: Stable push-button mode switching  

---

## 🛠️ Hardware Used
- Arduino Uno (or compatible board)  
- L298N Motor Driver Module  
- DC Motors (x2)  
- IR Sensors (x2)  
- Bluetooth Module (HC-05 or HC-06)  
- Push Button  
- LEDs (x2)  
- Buzzer  
- Power supply  

---

## ⚙️ Circuit Connections
- **IR Sensors**: Right → A0, Left → A1  
- **Motor Driver (L298N)**:  
  - enA → Pin 10, in1 → Pin 9, in2 → Pin 8  
  - enB → Pin 5, in3 → Pin 7, in4 → Pin 6  
- **Button**: Pin 4 (with internal pull-up)  
- **Buzzer**: Pin 13  
- **LEDs**: Pin 11 and Pin 12  
- **Bluetooth Module**: RX → Pin 2, TX → Pin 3  

---

## 💻 Code Explanation
- **IR Mode**: Robot follows a line using sensor input.  
  - Both sensors on line → move forward  
  - Right off line → turn right  
  - Left off line → turn left  
  - Both off line → stop  
- **Bluetooth Mode**: Receives commands (`F`, `L`, `R`, `S`, `V`, `1`, `0`, `W`, `U`, `w`, `u`) to control movement, buzzer, and LEDs.  
- **Button**: Toggles between IR and Bluetooth modes with debounce logic.  
- **Motor Control**: PWM speed adjustment for smooth movement.  

---

## 🚀 Future Improvements
- Add obstacle detection with ultrasonic sensors  
- Integrate mobile app for advanced Bluetooth control  
- Include speed adjustment commands via Bluetooth  
- Add rechargeable battery monitoring system  
