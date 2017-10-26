int temperatureSensorPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A5, INPUT);
  //analogReadResolution(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(temperatureSensorPin);
  //int temp = (lm35Reading * 5000)/(1024*10);
  float temperature = (((reading) * (5000 / 1024.0)) - 500) / 10;

  Serial.print(temperature);
  Serial.println();
  delay(3000);

}
