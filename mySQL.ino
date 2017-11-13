char mySQLServer[] = "192.168.41.110";

void mySQLAdd()
{

  if (!client.connected()) {
    if (client.connect(mySQLServer, 80)) {
      client.print("GET /smartcoop/add.php?outsideTemp=");
      client.print(temperature);
      client.print("&insideTemp=");
      client.print(insideTemperature);
      client.print("&hum=");
      client.print(temperature);

      client.println();

      client.println("Host: 192.168.41.110");
      client.println("Connection: close");
      client.println();
    }

    client.stop();
  }
}

void mySQLAddTimes() // this needs testing
{
  if (!client.connected()) {
    if (client.connect(mySQLServer, 80)) {
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
