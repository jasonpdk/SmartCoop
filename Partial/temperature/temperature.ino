int temperatureSensorPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A5, INPUT);
  //analogReadResolution(10);
}

void loop() {
  // put your main code here, to run repeatedly:
  int tempAnalogReading = analogRead(temperatureSensorPin);
  //int temp = (lm35Reading * 5000)/(1024*10);
  float mv = ((tempAnalogReading)*(5000/1024.0));

  Serial.print(tempAnalogReading); 
  Serial.print(" ");
  Serial.print((mv-500)/10);
  Serial.println();
  delay(3000);
  
}
