#include <SoftwareSerial.h>

#define BT_RX 11  // Bluetooth TX to Arduino RX
#define BT_TX 10  // Bluetooth RX to Arduino TX

SoftwareSerial BT(BT_TX, BT_RX); 

int motor2Pin1 = 4; // pin 6 on L293D IC
int motor2Pin2 = 5; // pin 7 on L293D IC
int motor2EnablePin = 7; // pin 10 on L293D IC

int motor1Pin1 = 2; // pin 4 on L293D IC
int motor1Pin2 = 3; // pin 5 on L293D IC
int motor1EnablePin = 6; // pin 9 on L293D IC

int state;
int Speed = 130;

void setup() {
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(motor1EnablePin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(motor2EnablePin, OUTPUT);

    Serial.begin(9600);
    BT.begin(9600); // Setting the baud rate of Software Serial Library  
    delay(500);
}

void loop() {
    // if some data is sent, reads it and saves in state
    if (BT.available() > 0) {
        state = BT.read();
        Serial.println(state);
        if (state > 10) {
            Speed = state;
        }
    }

    analogWrite(motor1EnablePin, Speed);
    analogWrite(motor2EnablePin, Speed);

    // if the state is '1' the DC motor will go forward
    if (state == F) { forword(); Serial.println("Go Forward!"); }

    // if the state is '2' the motor will reverse
    else if (state == B) { backword(); Serial.println("Reverse!"); }

    // if the state is '3' the motor will turn left
    else if (state == L) { turnLeft(); Serial.println("Turn LEFT"); }

    // if the state is '4' the motor will turn right
    else if (state == R) { turnRight(); Serial.println("Turn RIGHT"); }

    // if the state is '5' the motor will stop
    else if (state == S) { Stop(); Serial.println("STOP!"); }

    delay(1);
}

void forword() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void backword() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void turnRight() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
}

void turnLeft() {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
}

void Stop() {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
}
