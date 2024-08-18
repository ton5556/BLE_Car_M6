char state;
//String state = "";
int Speed=50; 

//MOTOR CONTROLLER
int ENA = 11;
int IN1 = 13;
int IN2 = 12;
int IN3 = 9;
int IN4 = 8;
int ENB = 3;

void setup() {
pinMode(ENA,OUTPUT);   //Speed_A
pinMode(IN1,OUTPUT);   //left motors forward
pinMode(IN2,OUTPUT);   //left motors reverse
pinMode(IN3,OUTPUT);   //right motors forward
pinMode(IN4,OUTPUT);   //right motors reverse
pinMode(ENB,OUTPUT);   //Speed_B

Serial.begin(9600);
}
 
void loop() {
 state = Serial.read(); 

  switch(state){
  case '1':
     Speed=25;   // 0-255
  break;
  case '2':
     Speed=50;   // 0-255
  break;
  case '3':
     Speed=75;   // 0-255
  break;
  case '4':
     Speed=100;   // 0-255
  break;
  case '5':
     Speed=125;   // 0-255
  break;
  case '6':
     Speed=175;   // 0-255
  break;
  case '7':
     Speed=200;   // 0-255
  break;
  case '8':
     Speed=225;   // 0-255
  break;
  case '9':
     Speed=255;   // 0-255
  break;
  case 'F':
        digitalWrite(IN1,HIGH);
        digitalWrite(IN3,HIGH);
        break; 
  case 'G':
        digitalWrite(IN2,HIGH);
        digitalWrite(IN4,HIGH);
        break; 
  case 'L':
        digitalWrite(IN3,HIGH);
        digitalWrite(IN2,HIGH);
        break; 
  case 'R':
        digitalWrite(IN1,HIGH);
        digitalWrite(IN4,HIGH);
        break; 
  case 'S':
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,LOW);
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,LOW);
        break; 
  }
        analogWrite(ENA,Speed);
        analogWrite(ENB,Speed);
delay(5);
}

//******************************************************
