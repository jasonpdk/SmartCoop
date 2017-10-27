void runServer(bool updateTemp)
{
  /* SERVER */
  String HTTPRequest;
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
        if (c == '\n' && currentLineIsBlank)
        {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();

          if (HTTPRequest.indexOf("GET / ") > -1 || HTTPRequest.indexOf("GET /index") > -1 || HTTPRequest.indexOf("GET /?") > -1)
          {
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>SmartCoop</title>");

            css = SD.open("style.html");
            while (css.available())
            {
              client.write(css.read());
            }
            css.close();

            client.println("</head>");
            client.println("<body>");
            client.println("<div id=\"wrapper\">");
            client.println("<h1>Smart<span class=\"logoColour\">Coop</span></h1>");

            // site nav menu
            client.println("<div class=\"topnav\" id=\"myTopnav\">");
            client.println("<a class=\"active\" href=\"/\">Home</a>");
            client.println("<a href=\"/graphs\">Graphs</a>");
            client.println("</div>");


            client.println("<div id=\"mainContent\">");
            client.println("<div id=\"content\">");
            client.println("<h2>SENSOR READINGS</h2>");
            client.print("<p class=\"readings\">The outside temperature is ");
            client.print(temperature);
            client.print(" degrees Celsius<br />");
            client.print("The inside temperature is ");
            client.print(insideTemperature);
            client.print(" degrees celsius<br />");
            client.print("The humidity is ");
            client.print(humidity);
            client.println("%");
            client.println("<br /><a href=\"/graphs\">Click here to see the historical values on a graph.</a><br /><br /></p>");

            client.println("<h2>SUNRISE AND SUNSET TIMES</h2>");
            client.println("The sunrise time today is: " + sunrise + " UTC");
            client.println("<br />");
            client.println("The sunset time today is: " + sunset + " UTC");

            client.println("<h2>CONTROL</h2>");
            // Light Stuff
            client.println("<p>Click to turn LED on and off.</p>");

            client.println("<a href=\"?LEDOn\"><button type=\"button\">On</button></a>");
            client.println("<a href=\"?LEDOff\"><button type=\"button\">Off</button></a>");

            if (HTTPRequest.indexOf("LEDOn") > -1)
            {
              digitalWrite(lightPin, HIGH);
            }
            else if (HTTPRequest.indexOf("LEDOff") > -1)
            {
              digitalWrite(lightPin, LOW);
            }

            client.println("<p>Click to open/close door.</p>");

            client.println("<a href=\"?openDoor\"><button type=\"button\">Open</button></a>");
            client.println("<a href=\"?closeDoor\"><button type=\"button\">Close</button></a>");

            client.println("</div>"); // close content div
            if (HTTPRequest.indexOf("openDoor") > -1)
            {
              doorStatus = 1;
            }
            else if(HTTPRequest.indexOf("closeDoor") > -1)
            {
              doorStatus = 0;
            }

            client.println("</div>"); // close mainContent div

            client.println("<div id=\"footer\">");
            client.println("<p>SmartCoop: An Automated Chicken Coop - Jason Keane<p>");
            client.println("</div>"); // close footer div
            client.println("</div>"); // close wrapper div
            client.println("</body>");
            client.println("</html>");

          }
          else if(HTTPRequest.indexOf("GET /graphs") > -1)
          {
            client.println("<!DOCTYPE html>");
            client.println("<html>");
            client.println("<head>");
            client.println("<title>SmartCoop Graphs</title>");
            css = SD.open("style.html");
            while (css.available())
            {
              client.write(css.read());
            }
            css.close();
            client.println("</head>");
            client.println("<body>");
            client.println("<div id=\"wrapper\">");
            client.println("<h1>Smart<span class=\"logoColour\">Coop</span></h1>");

            // site nav menu
            client.println("<div class=\"topnav\" id=\"myTopnav\">");
            client.println("<a href=\"/\">Home</a>");
            client.println("<a class=\"active\" href=\"/graphs\">Graphs</a>");
            client.println("</div>");

            client.println("<div id=\"mainContent\">");
            client.println("<div id=\"content\">");
            client.println("<h2>GRAPHS</h2>");
            client.println("<iframe width=\"450\" height=\"260\" style=\"border: 1px solid #cccccc;\" src=\"https://thingspeak.com/channels/351486/charts/1?bgcolor=%23ffffff&color=%23d62020&dynamic=true&api_key=4FTN1ZL8P525S956&results=60&type=line&update=15\"></iframe>");
            client.println("<iframe width=\"450\" height=\"260\" style=\"border: 1px solid #cccccc;\" src=\"https://thingspeak.com/channels/351486/charts/2?bgcolor=%23ffffff&color=%23d62020&dynamic=true&api_key=4FTN1ZL8P525S956&results=60&type=line&update=15\"></iframe>");
            client.println("<iframe width=\"450\" height=\"260\" style=\"border: 1px solid #cccccc;\" src=\"https://thingspeak.com/channels/351486/charts/3?bgcolor=%23ffffff&color=%23d62020&dynamic=true&api_key=4FTN1ZL8P525S956&results=60&type=line&update=15\"></iframe>");

            client.println("</div>");
            client.println("</div>");

            client.println("<div id=\"footer\">");
            client.println("<p>SmartCoop: An Automated Chicken Coop - Jason Keane</p>");
            client.println("</div>"); // close footer div

            client.println("</div>");
            client.println("</body>");
            client.println("</html>");
          }
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
