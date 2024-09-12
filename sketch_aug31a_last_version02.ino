#define ENA 10  // Enable/speed motor Right
#define ENB 11  // Enable/speed motor Left

#define IN1 3   // L298N in1 motor Right
#define IN2 5   // L298N in2 motor Right
#define IN3 6   // L298N in3 motor Left
#define IN4 9   // L298N in4 motor Left

const int MAX_SPEED = 255;
const int MIN_SPEED = 0;
const int SPEED_INCREMENT = 10;
const int SPEED_COEFF = 4;  // Coefficient for turning speed reduction
const unsigned long DEBOUNCE_DELAY = 50;  // 50 ms debounce delay

int speedCar = 75;  // Initial speed
unsigned long lastCommandTime = 0;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600);  // Initialize serial communication for Bluetooth at 9600 baud
}

void sendSpeedToApp() {
  Serial.print("SPEED:");
  Serial.println(speedCar);  // Send the speed with a prefix "SPEED:"
}

void updateSpeed(int targetSpeed) {
  if (speedCar < targetSpeed) {
    speedCar = min(speedCar + SPEED_INCREMENT, targetSpeed);
  } else if (speedCar > targetSpeed) {
    speedCar = max(speedCar - SPEED_INCREMENT, targetSpeed);
  }
  sendSpeedToApp();
}

void goAhead() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedCar);
}

void goBack() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speedCar);
}

void goRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedCar);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speedCar);
}

void goLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedCar);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedCar);
}

void goAheadRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedCar / SPEED_COEFF);  // Slower speed for right side

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedCar);  // Full speed for left side
}

void goAheadLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedCar);  // Full speed for right side

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedCar / SPEED_COEFF);  // Slower speed for left side
}

void goBackRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedCar / SPEED_COEFF);  // Slower speed for right side

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speedCar);  // Full speed for left side
}

void goBackLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedCar);  // Full speed for right side

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speedCar / SPEED_COEFF);  // Slower speed for left side
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void handleMovementCommand(char cmd) {
  switch (cmd) {
    case 'F': goAhead(); break;
    case 'B': goBack(); break;
    case 'L': goLeft(); break;
    case 'R': goRight(); break;
    case 'I': goAheadRight(); break;
    case 'G': goAheadLeft(); break;
    case 'J': goBackRight(); break;
    case 'H': goBackLeft(); break;
    case 'S': stopRobot(); break;
    default: Serial.println("Invalid Movement Command"); break;
  }
}

void handleControlCommand(char cmd) {
  switch (cmd) {
    case '+': updateSpeed(min(speedCar + SPEED_INCREMENT, MAX_SPEED)); break;
    case '-': updateSpeed(max(speedCar - SPEED_INCREMENT, MIN_SPEED)); break;
    default: Serial.println("Invalid Control Command"); break;
  }
}

void loop() {
  if (Serial.available() > 0) {
    unsigned long currentTime = millis();
    if (currentTime - lastCommandTime >= DEBOUNCE_DELAY) {
      char command = Serial.read();
      if (command == '+' || command == '-') {
        handleControlCommand(command);
      } else {
        handleMovementCommand(command);
      }
      lastCommandTime = currentTime;
    }
  }
}
