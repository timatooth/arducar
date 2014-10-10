#define HORN_PIN 8
#define FORWARD_PIN 12
#define BACKWARD_PIN 11
#define LEFT_PIN 10
#define RIGHT_PIN 9
#define DELAY 35

char incomingByte = 0;

void setup(){
  Serial.begin(9600);
  pinMode(HORN_PIN, OUTPUT);
  pinMode(FORWARD_PIN, OUTPUT);
  pinMode(BACKWARD_PIN, OUTPUT);
  pinMode(LEFT_PIN, OUTPUT);
  pinMode(RIGHT_PIN, OUTPUT);
}

void horn(){
  digitalWrite(HORN_PIN, HIGH);
  delay(DELAY);
  digitalWrite(HORN_PIN, LOW);
}

void forward(){
  digitalWrite(FORWARD_PIN, HIGH);
  delay(DELAY);
  digitalWrite(FORWARD_PIN, LOW);
}

void forward_l(){
  digitalWrite(LEFT_PIN, HIGH);
  digitalWrite(FORWARD_PIN, HIGH);
  delay(DELAY);
  digitalWrite(FORWARD_PIN, LOW);
  digitalWrite(LEFT_PIN, LOW);
}

void forward_r(){
  digitalWrite(RIGHT_PIN, HIGH);
  digitalWrite(FORWARD_PIN, HIGH);
  delay(DELAY);
  digitalWrite(FORWARD_PIN, LOW);
  digitalWrite(RIGHT_PIN, LOW);
}

void backward(){
  digitalWrite(BACKWARD_PIN, HIGH);
  delay(DELAY);
  digitalWrite(BACKWARD_PIN, LOW);
}

void backward_l(){
  digitalWrite(LEFT_PIN, HIGH);
  digitalWrite(BACKWARD_PIN, HIGH);
  delay(DELAY);
  digitalWrite(BACKWARD_PIN, LOW);
  digitalWrite(LEFT_PIN, LOW);
}

void backward_r(){
  digitalWrite(RIGHT_PIN, HIGH);
  digitalWrite(BACKWARD_PIN, HIGH);
  delay(DELAY);
  digitalWrite(BACKWARD_PIN, LOW);
  digitalWrite(RIGHT_PIN, LOW);
}

void left(){
  digitalWrite(LEFT_PIN, HIGH);
  delay(DELAY);
  digitalWrite(LEFT_PIN, LOW);
}

void right(){
  digitalWrite(RIGHT_PIN, HIGH);
  delay(DELAY);
  digitalWrite(RIGHT_PIN, LOW);
}


void loop(){
  if(Serial.available() > 0){
    incomingByte = Serial.read();
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
    }
  }
}
