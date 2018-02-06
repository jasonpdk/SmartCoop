
void checkWaterSensor()
{
	if (digitalRead(waterLevelSensor) == LOW) {
		digitalWrite(solenoidValve, LOW);
	} else {
		digitalWrite(solenoidValve, HIGH);
	}
}
