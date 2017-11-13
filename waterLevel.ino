void checkWaterSensor()
{
	if (digitalRead(waterLevelSensor) == LOW) {
		// turn on solenoid valve
	} else {
		//turn off solenoid valve
	}
}
