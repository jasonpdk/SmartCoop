void runServer()
{
  /* SERVER */
  String HTTPRequest;
  char req_index = 0;

  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)
  {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();

        HTTPRequest += c;

        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank)
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();

          if (HTTPRequest.indexOf("LEDOn") > -1)
          {
            digitalWrite(lightPin, HIGH);
            saveLightStatus(1);
          }
          else if (HTTPRequest.indexOf("LEDOff") > -1)
          {
            digitalWrite(lightPin, LOW);
            saveLightStatus(0);
          }

          if (HTTPRequest.indexOf("openDoor") > -1)
          {
            doorStatus = 1;
            saveDoorStatus();
          }
          else if (HTTPRequest.indexOf("closeDoor") > -1)
          {
            doorStatus = 0;
            saveDoorStatus();
          }
          else if (HTTPRequest.indexOf("feed") > -1)
          {
            feedStatus = 1;
            /*Serial.print("FEEDSTAT: ");
            Serial.print(feedStatus);
            Serial.println();*/
          }

          req_index = 0; // reset request index

          // finished with the HTTP request so clear it
          HTTPRequest = "";
          break;
        }
        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
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

void saveLightStatus(int status)
{
  FILE *lightStatusFile;

  lightStatusFile = fopen("/home/root/lightStatus.txt", "w");
  fprintf(lightStatusFile, "%d", status);

  fclose(lightStatusFile);
}
