int LED = 4;
int buzz = 5;
int sensor = 13;
int state = LOW;             
int val = 0;


void setup() {
  pinMode(LED, OUTPUT);
  pinMode(sensor, INPUT);
  Serial.begin(9600);

}

void loop() {

  val = digitalRead(sensor);

  if(val == HIGH){
    digitalWrite(LED, HIGH);
    tone(buzz, 1000);
    delay(5000);

    digitalWrite(LED, LOW);
    noTone(buzz);
  }else if(val == LOW){
     digitalWrite(LED, LOW);
    noTone(buzz);
  }
}
