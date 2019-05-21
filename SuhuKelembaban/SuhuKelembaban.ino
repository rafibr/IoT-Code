#include <DHT.h>
int suhu = D2;
DHT dht(D2, DHT11); //Pin, Jenis DHT
int led1=D1;       
int led2=D2;
int led3=D3; 

void setup(){
  
Serial.begin(115200);
dht.begin();
pinMode(led1,OUTPUT);   //led1 sebagai OUTPUT
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);//led2 sebagai OUTPUT
}
 
void loop(){
 float kelembaban = dht.readHumidity();
 float suhu = dht.readTemperature();
 
 Serial.print("kelembaban: ");
 Serial.print(kelembaban);
 Serial.print(" ");
 Serial.print("suhu: ");
 Serial.println(suhu);
 if (suhu >25){                   //jika nilai sensor lebih besar dari 25
  digitalWrite(led3,HIGH);         //led3 nyala
  digitalWrite(led2,LOW); 
  digitalWrite(led1,LOW);//
  Serial.println("panas");     //menampilkan ke serial monitor bahwa suhu panas
}
else if (suhu >12 && suhu <=25){
  digitalWrite(led3,LOW);         
  digitalWrite(led2,HIGH);      //led2 nyala
  digitalWrite(led1,LOW);//
  Serial.println("sedang");     //menampilkan ke serial monitor bahwa suhu sedang
}
else{                              //jika tidak
  digitalWrite(led1,HIGH);          //led1 nyala
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);//
  Serial.println("dingin");    //menampilkan ke serial monitor bahwa suhu dingin
  }
  delay(1000);
}
