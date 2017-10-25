/* SmartCoop: ThingSpeak
 * Uploads a passed value to ThingSpeak.
 * Jason Keane
*/

void uploadToThingSpeak(float value)
{
  char thingSpeakServer[] = "api.thingspeak.com";
  String APIKey = "5LA2APGVOBKKBW4C";

  if (client.connect(thingSpeakServer, 80))
  {
    // Make a HTTP request:
    client.print("GET /update?api_key=");
    client.print(APIKey);
    client.print("&field1=");
    client.print(value);
    client.print("HTTP/1.1");
    client.println();

    client.println("Host: api.thingspeak.com");
    client.println("Connection: close");
    client.println();
  }
}
