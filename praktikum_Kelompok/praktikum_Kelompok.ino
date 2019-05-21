#define ECHOPIN 7
#define TRIGPIN 8

void setup() {

  Serial.begin(9600);
  pinMode(7, INPUT);
  pinMode(8, OUTPUT);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  
}

void loop() {

  digitalWrite(8, LOW);
  delayMicroseconds(2);
  digitalWrite(8, HIGH);
  delayMicroseconds(10);
  digitalWrite(8, LOW);

  int distance = pulseIn(7, HIGH);
  distance = distance/70;

  if(distance<=200 && distance>=170){
    digitalWrite(13, HIGH);
    
Serial.print(distance);
Serial.println(" cm ");
  }

  if(distance<=169 && distance>=30){
    digitalWrite(12, HIGH);
    
Serial.print(distance);
Serial.println(" cm ");
  }

  if(distance<=29 && distance>=0){
    digitalWrite(11, HIGH);
    
Serial.print(distance);
Serial.println(" cm ");
  }
  

delay(1000);

  
}
