int sensorSuara = A0;
int pinLED = D2;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
  pinMode(pinLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorValue = analogRead(sensorSuara);
  if ( sensorValue > 108 ) {
    digitalWrite(pinLED, HIGH);
  }
  else{
    digitalWrite(pinLED, LOW);
  }
  Serial.println(sensorValue);
  delay(1000);
}
