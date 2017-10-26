#include "DHT.h" // dht.cpp has been modified to get this to work


#define DHT11Pin 7
#define DHTTYPE DHT11Pin

DHT dht(DHT11Pin, DHTTYPE);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int chk = DHT.read11(DHT11Pin);
  Serial.println(DHT.temperature);
  Serial.println(DHT.humidity);
  delay(1000);
}
