void checkDoor()
{
  if ((doorStatus == 1) && (digitalRead(doorReadSwitch1) == HIGH)) // door open
  {
      digitalWrite(doorMotorPin1, HIGH);
      digitalWrite(doorMotorPin2, LOW);
    
  }
  else if ((doorStatus == 0) && (digitalRead(doorReadSwitch2) == HIGH))
  {         
      digitalWrite(doorMotorPin1, LOW);
      digitalWrite(doorMotorPin2, HIGH);
  }
  else
  {
    digitalWrite(doorMotorPin1, LOW);
    digitalWrite(doorMotorPin2, LOW);
  }
}

