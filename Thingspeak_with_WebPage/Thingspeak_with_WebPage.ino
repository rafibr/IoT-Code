#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
#include <Servo.h>

Servo servo_test;
int angle = 0;

#define LED D7
#define INPUTPIN D2
#define SERV D3

char ssid[] = "trixtear";          //  your network SSID (name)
char pass[] = "rafi456987";   // your network password

int status = WL_IDLE_STATUS;
WiFiClient  client;
int readValue; // variable to save channel field reading

unsigned long myChannelNumber = 752868; // modify this with your own Channel Number
const char * myReadAPIKey = "ZJZYTBZ785Q4DPEG";

void setup() {
  Serial.begin(115200); // for debugging reasons
  Serial.println("START");
  WiFi.begin(ssid, pass);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.print("..");
  }
  Serial.println("CONNECTION SUCCESS!!");
  ThingSpeak.begin(client);
  pinMode(LED, OUTPUT);
  servo_test.attach(SERV);
}

void loop() {
  // Read the latest value from field 1 of your channel
  readValue = ThingSpeak.readIntField(myChannelNumber, 1, myReadAPIKey);
  int  val = digitalRead(INPUTPIN);  // read input value

  if ( readValue == 1) {


    Serial.print("value ");
    Serial.println(val);

    if (val == HIGH) {            // check if the input is HIGH
      digitalWrite(LED, HIGH);  // turn LED ON

    } else {
      digitalWrite(LED, LOW); // turn LED OFF
      Serial.println("Gerakan Berhenti");
      // We only want to print on the output change, not state
    }

    servo_test.write(180);
  } else {


    servo_test.write(0);
    digitalWrite(LED, LOW);
    val = LOW;
  }

}
