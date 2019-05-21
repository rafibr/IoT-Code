
#include <DHT.h>

//Constants
#define DHTPIN D1     // what pin we're connected to
#define DHTTYPE DHT11   // DHT11

DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor for normal 16mhz Arduino

//Variables
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() 
{
  //Initialize serial port
  Serial.begin(9600);

  Serial.println("DHT11 sensor testing");
  
  //Initialize the DHT sensor
  dht.begin();  
}

void loop() 
{ 
    float converted = 0.00;
    
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

    //2000mS delay between reads
    delay(2000);
}
