#include <ESP8266WiFi.h>
#include <PubSubClient.h> 

//-------- Customise these values -----------
const char* ssid = "Meratus99";
const char* password = "khansaferdi1999";



#define ORG "nt8y82"
#define DEVICE_TYPE "nodemcu"
#define DEVICE_ID "nodemcu55"
#define TOKEN "rahimanisa55"
//-------- Customise the above values --------

char server[] = ORG".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

int air=A0;       //inisial sensor ketinggian air masuk pin A0
int led1=D1;       //inisial led1 masuk pin d1 merah
int led2=D2;      //inisial led2 masuk pin d2 kuning
int led3=D3; //inisial led3 masuk pin d3 hijau

void setup() {
pinMode(air,INPUT);     //sensor suara sebagai INPUT
pinMode(led1,OUTPUT);   //led1 sebagai OUTPUT
pinMode(led2,OUTPUT);   //led2 sebagai OUTPUT
pinMode(led3,OUTPUT);   //led3 sebagai OUTPUT

 Serial.begin(115200);
 Serial.println();
 

 Serial.print("Connecting to "); Serial.print(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 } 
 Serial.println("");

 Serial.print("WiFi connected, IP address: "); Serial.println(WiFi.localIP());

 
}



int counter = 0;

void loop() {
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

 if (!client.connected()) {
 Serial.print("Reconnecting client to ");
 Serial.println(server);
 while (!client.connect(clientId, authMethod, token)) {
 Serial.print(".");
 delay(500);
 }
 Serial.println();
 }

 String payload = "{\"d\":{\"tinggi\":";
 payload += value;
 payload += "}}";
 
 Serial.print("Sending payload: ");
 Serial.println(payload);
 
 if (client.publish(topic, (char*) payload.c_str())) {
 Serial.println("Publish ok");
 } else {
 Serial.println("Publish failed");
 }

 delay(5000);
}
