/* SmartCoop: Temperature
 * Reads the temperature from the TMP36 and returns the value in celsius. If this goes below X degrees
 * the heat lamp will turn on. If temperature goes above X turn on the fan.
 *
 * Jason Keane
*/

void temperatureCheckTiming()
{
  float previousHumidity;

  // Check temperature every 5 minutes
  const unsigned long sTime = (5*60) * 1000UL;
  static unsigned long lSTime = 0 - sTime;

  unsigned long now = millis();

  if (now - lSTime >= sTime) {
    lSTime += sTime;
    temperature = getTemperature(OTMP36Pin);

    Serial.println(temperature);

    insideTemperature = getTemperature(ITMP36Pin);
    Serial.println(insideTemperature);

    // humidity
    humidity = getHumidity(HIH4030Pin);

    Serial.println(humidity);

    // turn on heat lamp if temperature goes below 1 degree
    if (insideTemperature < 26) {
      digitalWrite(heatLamp, HIGH);
      digitalWrite(fan, HIGH);
  } else if (insideTemperature > 26) {
      digitalWrite(fan, LOW);
      digitalWrite(heatLamp, LOW);
    }
    // commented out to save requests, this will probably need to be run less often than the temperature check
    uploadToThingSpeak(insideTemperature, temperature, humidity);

    Serial.println("MYSQL");
    mySQLAdd();
  }

  runServer();
}

float getTemperature(int pin)
{
  float reading = analogRead(pin);
  temperature = (((reading) * (5000 / 1024.0)) - 500) / 10;

  return temperature;
}

float getHumidity(int pin)
{
  int sensorReading = analogRead(pin);
  float voltage = (sensorReading/1023.0) * 5.0;

  // the following formulas are derived from page 2 of the HIH 4030 datasheet
  float sensorRH = 161.0 * voltage / 5.0 - 25.8;
  //float sensorRH = (voltage - 0.958) / 0.307;

  // true humidiy including temperature compensation
  float trueRH = sensorRH / (1.0546 - 0.0026 * insideTemperature);
  return trueRH;
}
