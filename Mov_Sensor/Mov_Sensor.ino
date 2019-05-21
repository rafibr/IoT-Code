/*
 * PIR sensor tester
 */
 
int ledPin = 13;                // choose the pin for the LED
int inputPin = 4;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
 
void setup() {
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input
 
  Serial.begin(115200);
}
 
void loop(){
  val = digitalRead(inputPin);  // read input value
  Serial.print("value ");
  Serial.println(val);
  if (val == HIGH) {            // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
   
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
     }
  }
