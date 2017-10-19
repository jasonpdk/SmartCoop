/* Smart Coop Rev 3: Tmperature
 * Reads the temperature from the TMP36 and returns the value in celsius. If this goes below X degrees
 * the heat lamp will turn on.
 * Feature to add: If temperature goes above X turn on the fan.
 *
 * Jason Keane
*/

float temperatureStuff()
{
  float temperature;
  float reading = analogRead(TMP36Pin);
  temperature = (((reading) * (5000 / 1024.0)) - 500) / 10;
  Serial.print("The temperature is ");
  Serial.print(temperature);
  Serial.println();

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