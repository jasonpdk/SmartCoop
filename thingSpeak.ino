/* SmartCoop: ThingSpeak
 * Uploads a passed value to ThingSpeak.
 * Jason Keane
*/

void uploadToThingSpeak(float value1, int value2, int value3)
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
      client.print("&field1");
      client.print("=");
      client.print(value1);
      client.print("&field2");
      client.print("=");
      client.print(value2);
      client.print("&field3");
      client.print("=");
      client.print(value3);
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
