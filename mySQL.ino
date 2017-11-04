void mySQLAdd()
{
  char mySQLServer[] = "192.168.41.110";

  if (!client.connected())
  {
    if (client.connect(mySQLServer, 80))
    {
      client.print("GET /smartcoop/testadd.php?outsideTemp=");
      Serial.print("GET /smartcoop/testadd.php?outsideTemp=");

      client.print(temperature);
      Serial.print(temperature);

      client.print("&insideTemp=");
      Serial.print("&insideTemp=");

      client.print(insideTemperature);
      Serial.print(insideTemperature);

      client.print("&hum=");
      Serial.print("&hum=");

      client.print(temperature);
      Serial.print(temperature);

      client.println();
      Serial.println();


      client.println("Host: 192.168.41.110");

      client.println("Connection: close");

      client.println();

    }

    client.stop();
  }
}
