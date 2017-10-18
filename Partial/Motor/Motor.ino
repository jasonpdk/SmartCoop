int input;

void setup() {
  // put your setup code here, to run once:
	pinMode(1, INPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4, 1);

	 

  if ((digitalRead(1) == HIGH) && (digitalRead(8) == HIGH))
  {
  	digitalWrite(2, HIGH);
  	digitalWrite(3, LOW);
  }
  else if ((digitalRead(1) == LOW) && (digitalRead(7) == HIGH))
  {
  	digitalWrite(2, LOW);
  	digitalWrite(3, HIGH);
  }
  else
  {
  	digitalWrite(2, LOW);
  	digitalWrite(3, LOW);
  }
  
  

}
