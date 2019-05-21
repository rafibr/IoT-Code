#include <ESP8266WiFi.h>
#include <PubSubClient.h> 
 
//-------- Customise these values -----------
const char* ssid = "trixtear";
const char* password = "rafi456987";

int trig= D4;   
int echo= D3;
int led=D7;
long durasi, jarak;

#define ORG "3gl80y"
#define DEVICE_TYPE "HC-SR04"
#define DEVICE_ID "Ultrasonic_Sensor"
#define TOKEN "ultrasonic"
//-------- Customise the above values --------
  
char server[] = ORG".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;
PubSubClient client(server, 1883, NULL, wifiClient);

void setup() {
  
 pinMode(echo,INPUT);   //led1 sebagai OUTPUT
pinMode(trig,OUTPUT);//set pin13 as OUTPUT
pinMode(led, OUTPUT);
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


void loop() {
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
  digitalWrite(led, HIGH);
}else{
  digitalWrite(led,LOW);
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

 String payload = "{\"d\":{\"jarak\":";
 payload += jarak;
 payload += "}}";

 
 Serial.print("Sending payload: ");
 Serial.println(payload);
 
 if (client.publish(topic, (char*) payload.c_str())) {
 Serial.println("Publish ok");
 } else {
 Serial.println("Publish failed");
 }

 delay(500);
}
