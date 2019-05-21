const int sensor = 13;
const int alarm = 4;

void setup() {
pinMode(sensor,INPUT);
pinMode(alarm,OUTPUT);

Serial.begin(115200);

}

void loop() {
  int nilai = digitalRead(sensor);
  Serial.println(nilai);
  if (nilai == LOW)
  {
    digitalWrite(alarm,HIGH);
  }
  if (nilai == HIGH)
  {
    digitalWrite(alarm,LOW);
  }
  delay(300);

}
