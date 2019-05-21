#include <ESP8266WiFi.h>
#include <PubSubClient.h> 
#include <DHT.h>

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


int suhu = D7;
DHT dht(D7, DHT11); //Pin, Jenis DHT
int led1=D1;       
int led2=D2;
int led3=D3; 

void setup() {
  
dht.begin();
pinMode(led1,OUTPUT);   //led1 sebagai OUTPUT
pinMode(led2,OUTPUT);
pinMode(led3,OUTPUT);//led2 sebagai OUTPUT

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
  
float kelembaban = dht.readHumidity();
 float suhu = dht.readTemperature();
 
 Serial.print("kelembaban: ");
 Serial.print(kelembaban);
 Serial.print(" ");
 Serial.print("suhu: ");
 Serial.println(suhu);
 if (suhu >35){                   //jika nilai sensor lebih besar dari 35
  digitalWrite(led3,HIGH);         //led3 nyala
  digitalWrite(led2,LOW); 
  digitalWrite(led1,LOW);//
  Serial.println("panas");     //menampilkan ke serial monitor bahwa suhu panas
}
else if (suhu >12 && suhu <=35){
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
  delay(1500);

 if (!client.connected()) {
 Serial.print("Reconnecting client to ");
 Serial.println(server);
 while (!client.connect(clientId, authMethod, token)) {
 Serial.print(".");
 delay(500);
 }
 Serial.println();
 }

 String payload = "{\"d\":{\"suhu\":";
 payload += suhu;
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
