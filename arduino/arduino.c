#define HORN_PIN 13

char incomingByte = 0;

void setup(){
  Serial.begin(9600);
  pinMode(HORN_PIN, OUTPUT);
}

void horn(){
  Serial.println("Blowing the horn");
  digitalWrite(HORN_PIN, HIGH);
  delay(1000);
  digitalWrite(HORN_PIN, LOW);
}

void loop(){
  if(Serial.available() > 1){
    incomingByte = Serial.read();
    switch(incomingByte){
    case 'H':
      horn();
      break;
    }
  }
}
