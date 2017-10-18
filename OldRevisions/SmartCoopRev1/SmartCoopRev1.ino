
/*
  Smart Coop Revision 1
  Jason Keane
  7/10//17
*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>



// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;
EthernetServer server(80);

String currentLine = "";
String sunrise = "";
String sunset = "";




//String clientHTTP_request;


File webFile;

int TMP36Pin = A5;


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
    // try to congifure using IP address instead of DHCP:
    //Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);

  server.begin();
  Serial.print("The server is at ");
  Serial.println(Ethernet.localIP());
  system("ntpdate -u pool.ntp.org"); // set the system time using NTP

  pinMode(2, OUTPUT);

}

void loop() {
  runServer();

  connectForGET();
}

float temperatureStuff()
{
  float temperature;
  float reading = analogRead(TMP36Pin);
  temperature = (((reading) * (5000 / 1024.0)) - 500) / 10;
  Serial.print("The temperature is ");
  Serial.print(temperature);
  Serial.println();

  // turn on light if temperature goes below x
  if (temperature < 20)
  {
    digitalWrite(2, HIGH);
  }
  else
  {
    digitalWrite(2, LOW);
  }

  return temperature;
}

void runServer()
{
  /* SERVER */
  char serverHTTP_request[20] = {0};
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
        if (req_index < (20 - 1)) {
          serverHTTP_request[req_index] = c;          // save HTTP request character
          req_index++;
        }

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
          if (StrContains(serverHTTP_request, "GET / ")
              || StrContains(serverHTTP_request, "GET /index")) {
            //webFile = SD.open("index.html");        // open web page file

            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>Smart Coop Site Test</title>");
            client.println("</head>");
            client.println("<body>");
            client.println("<h1>Smart Coop Site Test</h1>");
            client.println(" <p>Go to <a href=\"page2\">page 2</a>.</p>");
            client.print("<p>The temperature is ");

           
            // this is not the right place to run this function, will have to be run using a timer interrupt
            client.print(temperatureStuff());
            client.print(" degrees Celsius</p>");
            client.println();
            client.println("The sunrise time today is: " + sunrise + " UTC");
            client.println("<br />");
            client.println("The sunset time today is: " + sunset + " UTC");
            client.println("</body>");
            client.println("</html>");
          }
          else if (StrContains(serverHTTP_request, "GET /page2")) {
            webFile = SD.open("page2.html");        // open web page file

          }

          // if file is opened send it to client
          if (webFile) {
            while (webFile.available()) {
              client.write(webFile.read());
            }
            webFile.close();
          }

          req_index = 0; // reset request index

          // clear serverclientHTTP_requestuest String
          for (int i = 0; i < 20; i++) {
            serverHTTP_request[i] = 0;
          }
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

void getSunrise()
{
  int sunriseHours, sunriseMinutes;
  /* FETCH */
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
    Connected = false;
    getTimes = false;

  }
}

void connectForGET()
{

  // will need to run this block every day using RTC on Galileo
  if (getTimes)
  {
    if (Connected == false)
    {
      /* CONNECT */
      char serverToScrape[] = "api.sunrise-sunset.org";
      // if you get a connection, report back via serial:
      if (client.connect(serverToScrape, 80)) {
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

      Connected = true;
    }
    else
    {
      getSunrise();
    }
  }

}

char StrContains(char *str, char *sfind)
{
  char found = 0;
  char index = 0;
  char len;

  len = strlen(str);

  if (strlen(sfind) > len) {
    return 0;
  }
  while (index < len) {
    if (str[index] == sfind[found]) {
      found++;
      if (strlen(sfind) == found) {
        return 1;
      }
    }
    else {
      found = 0;
    }
    index++;
  }

  return 0;
}
