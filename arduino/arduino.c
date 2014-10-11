#include <Servo.h>

#define HORN_PIN 8
#define FORWARD_PIN 12
#define BACKWARD_PIN 11
#define LEFT_PIN 10
#define RIGHT_PIN 9
#define DELAY 1

unsigned char incomingByte = 0;
Servo yawServo;
Servo pitchServo;
unsigned int yawAngle;
unsigned char yawByte;

void setup(){
  Serial.begin(9600);
  pinMode(HORN_PIN, OUTPUT);
  pinMode(FORWARD_PIN, OUTPUT);
  pinMode(BACKWARD_PIN, OUTPUT);
  pinMode(LEFT_PIN, OUTPUT);
  pinMode(RIGHT_PIN, OUTPUT);
  pitchServo.attach(6);
  delay(10);
  yawServo.attach(5);
  pitchServo.write(90);
  yawServo.write(90);
}

void horn(){
  digitalWrite(HORN_PIN, HIGH);
}

void forward(){
  digitalWrite(FORWARD_PIN, HIGH);
}

void forward_l(){
  digitalWrite(LEFT_PIN, HIGH);
  digitalWrite(FORWARD_PIN, HIGH);
}

void forward_r(){
  digitalWrite(RIGHT_PIN, HIGH);
  digitalWrite(FORWARD_PIN, HIGH);
}

void backward(){
  digitalWrite(BACKWARD_PIN, HIGH);
}

void backward_l(){
  digitalWrite(LEFT_PIN, HIGH);
  digitalWrite(BACKWARD_PIN, HIGH);
}

void backward_r(){
  digitalWrite(RIGHT_PIN, HIGH);
  digitalWrite(BACKWARD_PIN, HIGH);
}

void left(){
  digitalWrite(LEFT_PIN, HIGH);
}

void right(){
  digitalWrite(RIGHT_PIN, HIGH);
}

void reset(){
  digitalWrite(FORWARD_PIN, LOW);
  digitalWrite(BACKWARD_PIN, LOW);
  digitalWrite(LEFT_PIN, LOW);
  digitalWrite(RIGHT_PIN, LOW);
  digitalWrite(HORN_PIN, LOW);  
}

char get_char(){
  int counter = 0;
  char incoming_byte;
  /* 250ms wait? */
  while (counter < 30000){
    if(Serial.available() > 0){
      incoming_byte = Serial.read();
      return incoming_byte;
    }
    counter += 1;
  }
  return 0;
}

void loop(){
  incomingByte = get_char();
  switch(incomingByte){
  case 'H':
    horn();
    break;
  case 'F':
    forward();
    break;
  case 'B':
    backward();
    break;
  case 'L':
    left();
    break;
  case 'R':
    right();
    break;
  case 'D':
    forward_r();
    break;
  case 'G':
    forward_l();
    break;
  case 'V':
    backward_l();
    break;
  case 'N':
    backward_r();
    break;
  case 'Y':
    yawServo.write(get_char());
    break;
  case 0:
    reset();
    break;
  }
}
