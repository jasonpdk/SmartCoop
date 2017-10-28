/*
  Smart Coop: An Automated Chicken Coop
  Jason Keane
  24/10//17
*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include "smartCoop.h"
#include "DHT.h"

EthernetClient client;
EthernetServer server(80);

/* GLOBAL VARIABLES - These will not always be here */
String currentLine = "";
String sunrise = "";
String sunset = "";

bool doorStatus = 0;
bool Connected = 0;
bool getTimes = true;

float temperature;
float humidity;
float insideTemperature;

// DHT11 Object
DHT dht(DHTIN,DHTOUT, DHTTYPE);

// CSS File
File css;

void setup()
{
 //Open serial and wait
  Serial.begin(9600);
  while (!Serial)
  {}

  // start the Ethernet connection:
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  IPAddress ip(192,168,41,100);
  Ethernet.begin(mac, ip);

  // give the Ethernet a second
  delay(1000);

  server.begin();
  Serial.print("The server is at ");
  Serial.println(Ethernet.localIP());
  system("ntpdate -u pool.ntp.org"); // set the system time using NTP

  // dht11 begin
  dht.begin();

  // SD
  SD.begin(4);


  // set pins
  pinMode(heatLamp, OUTPUT);
  pinMode(lightPin, OUTPUT);
  pinMode(doorMotorEN, OUTPUT);
  pinMode(doorMotorPin1, OUTPUT);
  pinMode(doorMotorPin2, OUTPUT);
  pinMode(doorReadSwitch1, INPUT);
  pinMode(doorReadSwitch2, INPUT);
  pinMode(fan, OUTPUT);
  digitalWrite(doorMotorEN, HIGH);

}

void loop()
{
  connectForGET(); // this will be run once every day
  checkDoor();
  temperatureCheckTiming();
}
