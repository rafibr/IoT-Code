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


int sensorSuara = A0;
int led1 = D2;

void setup() {
 
 pinMode(led1, OUTPUT);

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

 String payload = "{\"d\":{\"tinggi\":";
 payload += sensorValue;
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
