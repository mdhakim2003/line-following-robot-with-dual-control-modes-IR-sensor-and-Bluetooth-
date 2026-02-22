#include <SoftwareSerial.h>

// Pin definitions for IR sensors
const int irSensorRight = A0;
const int irSensorLeft = A1;

// Pin definitions for L298N motor driver
const int enA = 10;   // Speed control for motor A
const int in1 = 9;    // Direction control for motor A
const int in2 = 8;    // Direction control for motor A
const int in3 = 7;    // Direction control for motor B
const int in4 = 6;    // Direction control for motor B
const int enB = 5;    // Speed control for motor B

// Push button pin
const int buttonPin = 4;

// Buzzer pin
const int buzzerPin = 13;

// LED pins
const int ledPin1 = 11;
const int ledPin2 = 12;

// Speed settings
const int motorSpeed = 120; // Adjust the speed as needed (0-255)

// Bluetooth setup
SoftwareSerial BTSerial(2, 3); // RX, TX (2 -> RX, 3 -> TX)

// Mode variable
enum Mode {IR_SENSOR, BLUETOOTH};
Mode currentMode = IR_SENSOR;

// Button state variables
bool lastButtonState = HIGH;
bool currentButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  // Initialize IR sensor pins
  pinMode(irSensorRight, INPUT);
  pinMode(irSensorLeft, INPUT);

  // Initialize motor driver pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Initialize button pin with internal pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);

  // Initialize buzzer pin
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW); // Start with buzzer off

  // Initialize LED pins
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin1, LOW); // Start with LEDs off
  digitalWrite(ledPin2, LOW); // Start with LEDs off

  // Set initial motor speed
  analogWrite(enA, motorSpeed);
  analogWrite(enB, motorSpeed);

  // Start with motors stopped
  stopMotors();

  // Initialize Bluetooth serial communication
  BTSerial.begin(9600);
}

void loop() {
  // Check for button press to switch mode
  int reading = digitalRead(buttonPin);

  // If the switch changed, due to noise or pressing
  if (reading != lastButtonState) {
    lastDebounceTime = millis(); // reset the debouncing timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // Whatever the reading is at, it's been there for longer than the debounce delay
    // so take it as the actual current state

    // If the button state has changed
    if (reading != currentButtonState) {
      currentButtonState = reading;

      // Only toggle the mode if the new button state is LOW (button pressed)
      if (currentButtonState == LOW) {
        toggleMode();
      }
    }
  }

  // Save the reading. Next time through the loop, it'll be the lastButtonState
  lastButtonState = reading;

  // Execute actions based on current mode
  if (currentMode == IR_SENSOR) {
    // Read IR sensor values
    int rightSensorValue = digitalRead(irSensorRight);
    int leftSensorValue = digitalRead(irSensorLeft);

    // Determine robot action based on sensor input
    if (rightSensorValue == LOW && leftSensorValue == LOW) {
      // Both sensors detect black line
      moveForward();
    } else if (rightSensorValue == HIGH && leftSensorValue == LOW) {
      // Right sensor off line, turn left
      turnRight();
    } else if (rightSensorValue == LOW && leftSensorValue == HIGH) {
      // Left sensor off line, turn right
      turnLeft();
    } else {
      // Both sensors off line, stop
      stopMotors();
    }
  } else if (currentMode == BLUETOOTH) {
    // Check for Bluetooth commands
    if (BTSerial.available()) {
      char command = BTSerial.read();
      handleBluetoothCommand(command);
    }
  }
}

void toggleMode() {
  if (currentMode == IR_SENSOR) {
    currentMode = BLUETOOTH;
    BTSerial.println("Mode switched to BLUETOOTH");
  } else {
    currentMode = IR_SENSOR;
    BTSerial.println("Mode switched to IR_SENSOR");
  }
}

void handleBluetoothCommand(char command) {
  switch (command) {
    case 'F':
      moveForwardBT();
      break;
    case 'L':
      turnLeft();
      break;
    case 'R':
      turnRight();
      break;
    case 'S':
      stopMotors();
      break;
    case 'V':
      honk();
      break;
    case '1':
      turnOnLeds();
      break;
    case '0':
      turnOffLeds();
      break;
    case 'W':
      turnOnLed1();
      break;
    case 'U':
      turnOnLed2();
      break;
    case 'w':
      turnOffLed1();
      break;
    case 'u':
      turnOffLed2();
      break;
    default:
      break;
  }
}

void moveForward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 80);
  analogWrite(enB, 80);
}

void turnLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void moveForwardBT() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, 255);
  analogWrite(enB, 255);
}

void honk() {
  digitalWrite(buzzerPin, HIGH); // Turn on the buzzer
  delay(1000);                   // Honk duration
  digitalWrite(buzzerPin, LOW);  // Turn off the buzzer
}

void turnOnLeds() {
  digitalWrite(ledPin1, HIGH); // Turn on LED 1
  digitalWrite(ledPin2, HIGH); // Turn on LED 2
}

void turnOffLeds() {
  digitalWrite(ledPin1, LOW); // Turn off LED 1
  digitalWrite(ledPin2, LOW); // Turn off LED 2
}



void turnOnLed1() {
  digitalWrite(ledPin1, HIGH); // Turn on LED 1
}

void turnOnLed2() {
  digitalWrite(ledPin2, HIGH); // Turn on LED 1
}

void turnOffLed1() {
  digitalWrite(ledPin1, LOW); // Turn on LED 1
}

void turnOffLed2() {
  digitalWrite(ledPin2, LOW); // Turn on LED 1
}


