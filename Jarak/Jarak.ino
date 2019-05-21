int trig= D1;            // membuat varibel trig yang di set ke-pin 1
int echo= D2;            // membuat variabel echo yang di set ke-pin 2 
long durasi, jarak;     // membuat variabel durasi dan jarak

void setup() {
  // put your setup code here, to run once:
pinMode(trig, OUTPUT);    // set pin trig menjadi OUTPUT
pinMode(echo, INPUT);     // set pin echo menjadi INPUT
Serial.begin(115200);
Serial.println();
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trig, LOW);
delay(8);

durasi= pulseIn(echo, HIGH);  // menerima suara ultrasonic
jarak= (durasi/2);
int jarak2 = jarak/29.1;// mengubah durasi menjadi jarak (cm)
delay(1000);
Serial.println(jarak);  
Serial.println(jarak2);// menampilkan jarak pada Serial Monito
Serial.println(durasi);
}
