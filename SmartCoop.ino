/*
  Smart Coop: An Automated Chicken Coop
  Jason Keane
  04/11//17
*/

#include <Ethernet.h>
#include "smartCoop.h"
#include "DHT.h"
#include <time.h>

EthernetClient client;
EthernetServer server(8000);

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

void setup()
{
  //Open serial and wait
  Serial.begin(9600);
  while (!Serial)
  {}

  // start the Ethernet connection:
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  IPAddress ip(192,168,41,10);
  IPAddress dnsServer(8,8,8,8);
  IPAddress gateway(192,168,41,1);
  IPAddress subnet(255,255,255,0);
  //Ethernet.begin(mac, ip, dnsServer, gateway, subnet);
  Ethernet.begin(mac);

  // give the Ethernet a second
  delay(1000);

  server.begin();
  Serial.print("The server is at ");
  Serial.println(Ethernet.localIP());
  system("ntpdate -u pool.ntp.org"); // set the system time using NTP

  // dht11 begin
  dht.begin();

  // set pins
  pinMode(solenoidValve, OUTPUT);
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
  if (getTimes == true)
  {
    connectForGET();
  }

  checkDoor();
  checkWaterSensor();
  temperatureCheckTiming();
  getRealTime();
}
