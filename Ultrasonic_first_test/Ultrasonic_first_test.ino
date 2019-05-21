//int trig= 13;            // Arduino
//int echo= 7;            // Arduino
int trig= D4;            // NodeMCU
int echo= D3;            // NodeMcu
long durasi, jarak;     // membuat variabel durasi dan jarak

void setup() {
pinMode(trig, OUTPUT);    // set pin trig menjadi OUTPUT
pinMode(echo, INPUT);     // set pin echo menjadi INPUT
pinMode(D7, OUTPUT);
Serial.begin(115200);       // digunakan untuk komunikasi Serial dengan komputer
}

void loop() {

// program dibawah ini agar trigger memancarakan suara ultrasonic
digitalWrite(trig, LOW);
delayMicroseconds(8);
digitalWrite(trig, HIGH);
delayMicroseconds(8);
digitalWrite(trig, LOW);
delayMicroseconds(8);


durasi= pulseIn(echo, HIGH);  
jarak= (durasi/2) / 29.1;     
Serial.print("Jarak -->");
Serial.println(jarak);
if(jarak<=20){
  digitalWrite(D7, HIGH);
}else{
  digitalWrite(D7,LOW);
}
delay(300);

}
