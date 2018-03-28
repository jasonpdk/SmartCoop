const unsigned long feedSTime = (10) * 1000UL;
unsigned long feedLSTime = 0;

void feedCheck()
{
/*  Serial.print("feedStatus = ");
  Serial.print(feedStatus);
  Serial.println();*/
  if (feedStatus == 1)
  {
    // feed the chickens (run the motor for 5 seconds)
    digitalWrite(feederMotor, LOW); // turn on relay to turn on motor

    unsigned long now = millis();
    /*Serial.println(now);
    Serial.println(feedLSTime);
    Serial.println(feedSTime);
    Serial.println(timeSinceStart);*/
    if (now - feedLSTime > feedSTime)
    {
      feedLSTime = now;
      digitalWrite(feederMotor, HIGH); // turn off motor
      feedStatus = 0;
    }
  }
}
