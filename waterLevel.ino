
void checkWaterSensor()
{
	if (digitalRead(waterLevelSensor) == LOW) {
		digitalWrite(solenoidValve, HIGH);
	} else {
		digitalWrite(solenoidValve, LOW);
	}
}
