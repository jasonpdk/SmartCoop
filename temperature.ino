/* SmartCoop: Temperature
 * Reads the temperature from the TMP36 and returns the value in celsius. If this goes below X degrees
 * the heat lamp will turn on. If temperature goes above X turn on the fan.
 *
 * Jason Keane
*/

void temperatureCheckTiming()
{
  // Check temperature every 30 seconds
  const unsigned long sTime = (30) * 1000UL;
  static unsigned long lSTime = 0 - sTime;

  unsigned long now = millis();

  if (now - lSTime >= sTime) {
    lSTime += sTime;
    temperature = getTemperature(OTMP36Pin);

    Serial.print("OTEMP: ");
    Serial.println(temperature);

    insideTemperature = getTemperature(ITMP36Pin);
    Serial.print("ITEMP: ");
    Serial.println(insideTemperature);

    // humidity
    humidity = getHumidity(HIH4030Pin);

    Serial.println(humidity);

    // turn on heat lamp if temperature goes below 1 degree
    if (insideTemperature <= 1) {
      digitalWrite(heatLamp, HIGH);
      digitalWrite(fan, HIGH);
    }
    else if (insideTemperature > 26) {
      digitalWrite(fan, LOW);
      digitalWrite(heatLamp, LOW);
    }
    else
    {
      // turn both off
      digitalWrite(heatLamp, LOW);
      digitalWrite(fan, HIGH);
    }

    uploadToThingSpeak(insideTemperature, temperature, humidity);

    Serial.println("MYSQL");
    mySQLAdd();
  }

  runServer();
}

float getTemperature(int pin)
{
  float reading = analogRead(pin);
  float temp = (((reading) * (5000 / 1024.0)) - 500) / 10;

  return temp;
}

float getTempTemp(int pin)
{
  float reading = analogRead(pin);
  float temp = ((reading) * (5000 / 1024.0)) / 10;

  return temp;
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
