/* SmartCoop: ThingSpeak
 * Uploads a passed value to ThingSpeak.
 * Jason Keane
*/

void uploadToThingSpeak(float value, int field)
{
  char thingSpeakServer[] = "api.thingspeak.com";
  String APIKey = "5LA2APGVOBKKBW4C";

  if (!client.connected())
  {
    if (client.connect(thingSpeakServer, 80))
    {
      // Make a HTTP request:
      client.print("GET /update?api_key=");
      client.print(APIKey);
      client.print("&field");
      client.print(field);
      client.print("=");
      client.print(value);
      client.print("HTTP/1.1");
      client.println();

      client.println("Host: api.thingspeak.com");
      client.println("Connection: close");
      client.println();
    }
    else
    {
      Serial.println("FAILED THINGSPEAK");
    }

    client.stop();
  }
}
