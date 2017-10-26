/* SmartCoop: Temperature
 * Reads the temperature from the TMP36 and returns the value in celsius. If this goes below X degrees
 * the heat lamp will turn on.
 * Feature to add: If temperature goes above X turn on the fan.
 *
 * Jason Keane
*/


void temperatureCheckTiming()
{
  // Check temperature ever 25 seconds
<<<<<<< HEAD
  const unsigned long sampleTime = 5 * 1000UL;
=======
  const unsigned long sampleTime = 60 * 1000UL;
>>>>>>> develop
  static unsigned long lastSampleTime = 0 - sampleTime;

  unsigned long now = millis();

  if (now - lastSampleTime >= sampleTime)
  {
    lastSampleTime += sampleTime;
    temperature = temperatureStuff();
<<<<<<< HEAD
=======
    // commented out to save requests, this will probably need to be run less often than the temperature check
    //uploadToThingSpeak(temperature, 1);
    updateWebTemp = true;
>>>>>>> develop
    Serial.println(temperature);
  }

  runServer();
}

float temperatureStuff()
{
  float reading = analogRead(TMP36Pin);
  temperature = (((reading) * (5000 / 1024.0)) - 500) / 10;
  //Serial.print("The temperature is ");
  //Serial.print(temperature);
  //Serial.println();

  // turn on light if temperature goes below x
  if (temperature < 20.0)
  {
    digitalWrite(heatLamp, HIGH);
    digitalWrite(fan, LOW);
  }
  else if (temperature > 20.0)
  {
    digitalWrite(fan, HIGH);
    digitalWrite(heatLamp, LOW);
  }


  return temperature;
}
