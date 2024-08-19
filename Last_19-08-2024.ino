#define light_FR  14    // LED Front Right   pin A0 for Arduino Uno
#define light_FL  15    // LED Front Left    pin A1 for Arduino Un
#define horn_Buzz 18    // Horn Buzzer       pin A4 for Arduino Uno

#define ENA 6           // Enable/speed motor Right
#define ENB 7           // Enable/speed motor Left

#define IN1  2          // L298N in1 motor Right
#define IN2  3          // L298N in2 motor Right
#define IN3  4          // L298N in3 motor Left
#define IN4  5          // L298N in4 motor Left

const int MAX_SPEED = 255;
const int MIN_SPEED = 0;
const int SPEED_INCREMENT = 10;
const int speed_Coeff = 4;

int command = 0;       // Int to store app command state.
int speedCar = 75;     // Initial speed at 75
boolean lightFront = false;
boolean horn = false;

void setup() {
  pinMode(light_FR, OUTPUT);
  pinMode(light_FL, OUTPUT);
  pinMode(horn_Buzz, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(9600); // Initialize serial communication for Bluetooth at 9600 baud
}

void sendSpeedToApp() {
  Serial.print("SPEED:");
  Serial.println(speedCar);  // Send the speed with a prefix "SPEED:"
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
  analogWrite(ENA, speedCar / speed_Coeff); // Slower speed for right side

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedCar); // Full speed for left side
}

void goAheadLeft() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, speedCar); // Full speed for right side

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, speedCar / speed_Coeff); // Slower speed for left side
}

void goBackRight() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedCar / speed_Coeff); // Slower speed for right side

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speedCar); // Full speed for left side
}

void goBackLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, speedCar); // Full speed for right side

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, speedCar / speed_Coeff); // Slower speed for left side
}

void stopRobot() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);

  digitalWrite(light_FR, LOW);  // Turn off lights
  digitalWrite(light_FL, LOW);
  digitalWrite(horn_Buzz, LOW); // Turn off horn
}

void updateLightsAndHorn() {
  digitalWrite(light_FR, lightFront ? HIGH : LOW);
  digitalWrite(light_FL, lightFront ? HIGH : LOW);
  digitalWrite(horn_Buzz, horn ? HIGH : LOW);
}

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();

    switch (command) {
      case 'F': goAhead(); break;
      case 'B': goBack(); break;
      case 'L': goLeft(); break;
      case 'R': goRight(); break;
      case 'I': goAheadRight(); break;
      case 'G': goAheadLeft(); break;
      case 'J': goBackRight(); break;
      case 'H': goBackLeft(); break;
      case 'S': stopRobot(); break;

      // Increase speed
      case '+':
        speedCar = min(speedCar + SPEED_INCREMENT, MAX_SPEED);
        sendSpeedToApp();
        break;

      // Decrease speed
      case '-':
        speedCar = max(speedCar - SPEED_INCREMENT, MIN_SPEED);
        sendSpeedToApp();
        break;

      case 'W': lightFront = true; updateLightsAndHorn(); break;
      case 'w': lightFront = false; updateLightsAndHorn(); break;
      case 'V': horn = true; updateLightsAndHorn(); break;
      case 'v': horn = false; updateLightsAndHorn(); break;
    }
  }
}
