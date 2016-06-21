void liftOff(){
  while(analogRead(middleSensor) < 100) {}
  Serial.println("Liftoff");
}

void lightLeft(){
  digitalWrite(leftLed, HIGH);
  digitalWrite(middleLed, LOW);
  digitalWrite(rightLed, LOW);
}

void lightMiddle(){
  digitalWrite(leftLed, LOW);
  digitalWrite(middleLed, HIGH);
  digitalWrite(rightLed, LOW);
}

void lightRight(){
  digitalWrite(leftLed, LOW);
  digitalWrite(middleLed, LOW);
  digitalWrite(rightLed, HIGH);
}

void lightNone(){
  digitalWrite(leftLed, LOW);
  digitalWrite(middleLed, LOW);
  digitalWrite(rightLed, LOW);
}

void festiveLightShow(){
  for(int i = 0; i < 4; ++i){
    lightLeft();
    delay(150);
    lightMiddle();
    delay(150);
    lightRight();
    delay(150);
  }
  
  lightNone();  
}

