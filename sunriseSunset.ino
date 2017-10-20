/* Smart Coop Rev 3: Sunrise and Sunset
 * Connects to api.sunrise-sunset.org, fetches the sunrise and sunset times, and prints them out.
 *
 * Jason Keane
*/

/* Fetches the sunrise and sunset times */
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

  // converts the strings into separate integers for hours and minutes (unfinished)
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


/* Connects to the server api.sunrise-sunset.org */
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