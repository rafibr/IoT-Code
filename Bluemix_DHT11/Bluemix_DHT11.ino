#include <ESP8266WiFi.h>
#include <PubSubClient.h> 
#include <DHT.h>
 
//-------- Customise these values -----------
const char* ssid = "trixtear";
const char* password = "rafi456987";



//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value
#define DHTPIN D1     // what pin we're connected to
#define DHTTYPE DHT11   // DHT11
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

int led=D7;

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
  
  dht.begin();  
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
  //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();

    Serial.print("Celsius = ");
    Serial.print(temp);
    //Print degree symbol
    Serial.write(176); 
    Serial.println("C");

    Serial.print("Humidity =");
    Serial.println(hum);

  
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
 payload += temp;
 payload += "},\"b\":{\"kelembapan\":";
 payload += hum;
 payload+="}}";

 
 Serial.print("Sending payload: ");
 Serial.println(payload);
 
 if (client.publish(topic, (char*) payload.c_str())) {
 Serial.println("Publish ok");
 } else {
 Serial.println("Publish failed");
 }


 delay(500);
}
