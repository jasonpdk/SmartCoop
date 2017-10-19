
/*
  Smart Coop Revision 4
  Jason Keane
  7/10//17
*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include "smartCoop.h"

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
EthernetServer server(80);

String currentLine = "";
String sunrise = "";
String sunset = "";

String HTTPRequest;

bool doorStatus = 0;

bool getTimes = true;
bool Connected = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");

  }
  // give the Ethernet a second
  delay(1000);

  server.begin();
  Serial.print("The server is at ");
  Serial.println(Ethernet.localIP());
  system("ntpdate -u pool.ntp.org"); // set the system time using NTP

  // set pins
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(doorMotorEN, OUTPUT);
  pinMode(doorMotorPin1, OUTPUT);
  pinMode(doorMotorPin2, OUTPUT);
  pinMode(doorReadSwitch1, INPUT);
  pinMode(doorReadSwitch2, INPUT);
  pinMode(fan, OUTPUT);
  digitalWrite(doorMotorEN, HIGH);
}

void loop() {
  connectForGET();

  // this block will be moved
  if ((doorStatus == 1) && (digitalRead(doorReadSwitch1) == HIGH)) // door open
  {
      digitalWrite(doorMotorPin1, HIGH);
      digitalWrite(doorMotorPin2, LOW);
    
  }
  else if ((doorStatus == 0) && (digitalRead(doorReadSwitch2) == HIGH))
  {         
      digitalWrite(doorMotorPin1, LOW);
      digitalWrite(doorMotorPin2, HIGH);
  }
  else
  {
    digitalWrite(doorMotorPin1, LOW);
    digitalWrite(doorMotorPin2, LOW);
  }

  runServer();
}



void runServer()
{
  /* SERVER */
  
  
  char req_index = 0;

  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        HTTPRequest += c;

        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          // client.println("Refresh: 3");  // refresh the page automatically every 5 sec
          client.println();


            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>Smart Coop Site Test</title>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Smart Coop Site Test</h1>");
            client.print("<p>The temperature is ");

           
            // this is not the right place to run this function, will have to be run using a timer interrupt
            client.print(temperatureStuff());
            client.print(" degrees Celsius</p>");
            client.println();
            client.println("The sunrise time today is: " + sunrise + " UTC");
            client.println("<br />");
            client.println("The sunset time today is: " + sunset + " UTC");

            // Light Stuff
            client.println("<p>Click to turn LED on and off.</p>");


            client.println("<a href=\"?LEDOn\"><button type=\"button\">On</button></a>");
            client.println("<a href=\"?LEDOff\"><button type=\"button\">Off</button></a>");
            
            if (HTTPRequest.indexOf("LEDOn") > -1)
            {
              digitalWrite(6, HIGH);
            }
            else if (HTTPRequest.indexOf("LEDOff") > -1)
            {
              digitalWrite(6, LOW);
            }

            
            // Door Stuff
            client.println("<p>Click to open/close door.</p>");
           
           client.println("<a href=\"?openDoor\"><button type=\"button\">Open</button></a>");
           client.println("<a href=\"?closeDoor\"><button type=\"button\">Close</button></a>");

           if (HTTPRequest.indexOf("openDoor") > -1)
           {
            doorStatus = 1;
           }
           else if(HTTPRequest.indexOf("closeDoor") > -1)
           {
            doorStatus = 0;
           }

            client.println("</body>");
            client.println("</html>");


          req_index = 0; // reset request index

          // finished with the HTTP request so clear it
          HTTPRequest = ""; 
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}


