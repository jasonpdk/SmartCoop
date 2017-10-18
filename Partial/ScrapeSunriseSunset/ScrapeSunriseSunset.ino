/*
  Web client

 This sketch connects to a website (http://www.google.com)
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe, based on work by Adrian McEwen

 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(74,125,232,128);  // numeric IP for Google (no DNS)
char server[] = "api.sunrise-sunset.org";    // name address for Google (using DNS)

// Set the statihwc IP address to use if the DHCP fails to assign
IPAddress ip(192, 168, 41, 177);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

String currentLine = "";
String sunrise = "";
String sunset = "";

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /json?lat=53.2706680&lng=-9.0567910&date=today HTTP/1.1");
    //client.println("GET /json?lat=53.2706680&lng=-9.0567910&date=2017-06-30 HTTP/1.1");
    client.println("Host: api.sunrise-sunset.org");
    client.println("Connection: close");
    client.println();
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
}

void loop() {
  // if there are incoming bytes available
  // from the server, read them and print them:
  if (client.available()) {
    char c = client.read();
    currentLine += c;

    
    if (c == '\n')
    {
      if (currentLine.startsWith("{\"results\":"))
      {
        int i;
        for (i = 23; i < 33; i++)
        {
          sunrise += currentLine[i];
        }

       for (i = 45; i < 55; i++)
       {
        sunset += currentLine[i];
       }
       
       Serial.println("The sunrise time is: " + sunrise);
       Serial.println("The sunset time is: " + sunset);
       client.stop();
      }
      else
      {
        currentLine = "";
      }
    }
  }

  int sunriseHours, sunriseMinutes;
    String stringRiseHours = "", stringRiseMinutes = "";
    
    int i;
    for (i = 0; i < sunrise.indexOf(':'); i++)
    {
        stringRiseHours += sunrise[i]; 
    }
    sunriseHours = stringRiseHours.toInt();
    
    for (i = sunrise.indexOf(':') + 1; i < sunrise.lastIndexOf(':'); i++)
    {
        stringRiseMinutes += sunrise[i]; 
    }
    sunriseMinutes = stringRiseMinutes.toInt();

  
  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();

    // do nothing forevermore:
    while (true);
  }
}

