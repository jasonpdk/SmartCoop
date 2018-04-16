char mySQLServer[] = "192.168.41.11";

void mySQLAdd()
{
  if (!client.connected())
  {
	 if (client.connect(mySQLServer, 80))
    {
      client.print("GET /smartcoop/add.php?outsideTemp=");
      //Serial.print("GET /smartcoop/add.php?outsideTemp=");

      client.print(temperature);
    //  Serial.print(temperature);

      client.print("&insideTemp=");
    //  Serial.print("&insideTemp=");

      client.print(insideTemperature);
    //  Serial.print(insideTemperature);

      client.print("&hum=");
      //Serial.print("&hum=");

      client.print(humidity);
    //  Serial.print(humidity);

      client.println();
      //Serial.println();

      client.println("Host: 192.168.41.11");
      client.println("Connection: close");
      client.println();
    }

    client.stop();
  }
}

void mySQLAddTimes() // this needs testing
{
  if (!client.connected())
  {
    Serial.println("!CONNECT");
    if (client.connect(mySQLServer, 80))
    {
      client.print("GET /smartcoop/addTimes.php?sunrise=");
      client.print(sunrise);
      client.print("&sunset=");
      client.print(sunset);

      client.println();
      client.println("Host: 192.168.41.110");
      client.println("Connection: close");
      client.println();
    }

    client.stop();
  }
}
