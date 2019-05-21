int air=A0;       //inisial sensor ketinggian air masuk pin A0
int led1=D1;       //inisial led1 masuk pin d1 merah
int led2=D2;      //inisial led2 masuk pin d2 kuning
int led3=D3; //inisial led3 masuk pin d3 hijau

void setup() {
  // put your setup code here, to run once:
pinMode(air,INPUT);     //sensor suara sebagai INPUT
pinMode(led1,OUTPUT);   //led1 sebagai OUTPUT
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);//led3 sebagai OUTPUT
Serial.begin(115200);     //Serial komunikasi arduino

}

void loop() {
  // put your main code here, to run repeatedly:
int value= analogRead(air);      //membaca sensor ketinggian air
Serial.println(value);           //menampilkan nilai sensor ketinggian air di serial monitor
delay(1000);                     //waktu 1000 ms

if (value >350){                   //jika nilai sensor kurang dari 700
  digitalWrite(led1,HIGH);         //led1 nyala merah
  digitalWrite(led2,LOW); 
  digitalWrite(led3,LOW);       //led3 mati
  Serial.println("air penuh");     //menampilkan ke serial monitor bahwa air penuh
}
else if (value >100 && value <350){
  digitalWrite(led1,LOW);         
  digitalWrite(led2,HIGH);      //led2 nyala
  digitalWrite(led3,LOW);     //led3 mati
  Serial.println("air sedang");     //menampilkan ke serial monitor bahwa air penuh
}
else{                              //jika tidak
  digitalWrite(led1,LOW);          //led1 mati
  digitalWrite(led2,LOW);
  digitalWrite(led3,HIGH);        //led3 nyala
  Serial.println("air kosong");    //menampilkan ke serial monitor bahwa air kosong
  }
}
