const int trigPin = 12;
const int echoPin = 13;
long duration;
int distanceCm, distanceInch;
int oldValue = 0 , newValue = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  distanceCm = duration * 0.0340 / 2;
  newValue = distanceCm;
  if(newValue != oldValue)
  {
    //Serial.print("Distance: ");
    Serial.print(distanceCm);
    //Serial.println(" cm");
    oldValue = newValue;
  }
  delay(2000);
}
