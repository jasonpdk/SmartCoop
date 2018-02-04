
void checkWaterSensor()
{
	if (digitalRead(waterLevelSensor) == LOW) {
		Serial.println("LOW");
		digitalWrite(solenoidValve, LOW);
	} else {
		Serial.println("HIGH");
		digitalWrite(solenoidValve, HIGH);
	}
}
