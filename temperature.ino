/* SmartCoop: Temperature
 * Reads the temperature from the TMP36 and returns the value in celsius. If this goes below X degrees
 * the heat lamp will turn on.
 * Feature to add: If temperature goes above X turn on the fan.
 *
 * Jason Keane
*/


void temperatureCheckTiming()
{
  bool updateWebTemp;
  // Check temperature ever 5 minutes
  const unsigned long sampleTime = (20) * 1000UL;
  static unsigned long lastSampleTime = 0 - sampleTime;

  unsigned long now = millis();

  if (now - lastSampleTime >= sampleTime) {
    lastSampleTime += sampleTime;
    temperature = temperatureStuff();

    updateWebTemp = true;
    Serial.println(temperature);

    // DHT11
    humidity = dht.readHumidity();
    Serial.println(humidity);


    insideTemperature = dht.readTemperature();
    Serial.println(insideTemperature);

    // commented out to save requests, this will probably need to be run less often than the temperature check
    //uploadToThingSpeak(insideTemperature, temperature, humidity);

    Serial.println("MYSQL");
    mySQLAdd();
  } else {
    updateWebTemp = false;
  }

  runServer(updateWebTemp);
}

float temperatureStuff()
{
  float reading = analogRead(TMP36Pin);
  temperature = (((reading) * (5000 / 1024.0)) - 500) / 10;

  // turn on light if temperature goes below x
  if (temperature < 20.0) {
    digitalWrite(heatLamp, HIGH);
    digitalWrite(fan, LOW);
  } else if (temperature > 20.0) {
    digitalWrite(fan, HIGH);
    digitalWrite(heatLamp, LOW);
  }

  return temperature;
}
