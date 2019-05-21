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

int trig= D1;            // membuat varibel trig yang di set ke-pin 3
int echo= D2;            // membuat variabel echo yang di set ke-pin 2 
int led1 = D3;
int led2 = D4;

long durasi, jarak;     // membuat variabel durasi dan jarak

void setup() {
pinMode(trig, OUTPUT);    // set pin trig menjadi OUTPUT
pinMode(echo, INPUT);     // set pin echo menjadi INPUT
pinMode(led1,OUTPUT);   //led1 sebagai OUTPUT
pinMode(led2,OUTPUT);   //led2 sebagai OUTPUT

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
digitalWrite(trig, LOW);
delayMicroseconds(8);
digitalWrite(trig, HIGH);
delayMicroseconds(8);
digitalWrite(trig, LOW);
delayMicroseconds(8);

 
 
durasi= pulseIn(echo, HIGH);  // menerima suara ultrasonic
jarak= (durasi/2) / 29.1;     // mengubah durasi menjadi jarak (cm)
Serial.println(jarak);        // menampilkan jarak pada Serial Monitor

if(jarak > 30) {
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
  Serial.println("Kejauhan");

}else {
  digitalWrite(led1, LOW);
  digitalWrite(led2, HIGH);
  Serial.println("Kedekatan");
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

 String payload = "{\"d\":{\"jarak\":";
 //payload += ",\"counter\":";
 payload += jarak;
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
