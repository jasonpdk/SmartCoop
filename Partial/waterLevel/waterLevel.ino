void setup()
{
	Serial.begin(9600);
	pinMode(0, INPUT);
}

void loop()
{
	if (digitalRead(0) == LOW)
	{
		Serial.println("WATER!");
	}
	else
	{
		Serial.println("NO WATER!");
	}

	delay(1000);
}

