#define light_FR  14    // LED Front Right   pin A0 for Arduino Uno
#define light_FL  15    // LED Front Left    pin A1 for Arduino Uno
#define horn_Buzz 18    // Horn Buzzer       pin A4 for Arduino Uno

#define ENA 6           // Enable/speed motor Right
#define ENB 7           // Enable/speed motor Left

#define IN1  2          // L298N in1 motor Right
#define IN2  3          // L298N in2 motor Right
#define IN3  4          // L298N in3 motor Left
#define IN4  5          // L298N in4 motor Left

int command;            // Int to store app command state.
int speedCar = 170;     // Fixed speed at 170
int speed_Coeff = 4;
boolean lightFront = false;
boolean horn = false;

unsigned long lastCommandTime = 0;       // Stores the time of the last received command
const unsigned long commandTimeout = 1000;  // Timeout duration in milliseconds (1 second)

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

void loop() {
  if (Serial.available() > 0) {
    command = Serial.read();
    delay(10);  // Add a small delay to debounce

    if (Serial.available() > 0) {
      command = Serial.read();  // Read the latest command
    }

    lastCommandTime = millis();  // Update the time of the last received command

    if (lightFront) {
      digitalWrite(light_FR, HIGH);
      digitalWrite(light_FL, HIGH);
    } else {
      digitalWrite(light_FR, LOW);
      digitalWrite(light_FL, LOW);
    }

    if (horn) {
      digitalWrite(horn_Buzz, HIGH);
    } else {
      digitalWrite(horn_Buzz, LOW);
    }

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
      case 'W': lightFront = true; break;
      case 'w': lightFront = false; break;
      case 'V': horn = true; break;
      case 'v': horn = false; break;
    }
  }
}
