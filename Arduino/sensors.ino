int normalizedRightReading(){
  int maxReading = 0;
  int reading;
  for(int i = 1; i <= 100; ++i){
    reading = analogRead(rightSensor);
    if(reading > maxReading){
      maxReading = reading;
    }
  }
  return maxReading;
}

int normalizedLeftReading(){
  int maxReading = 0;
  int reading;
  for(int i = 1; i <= 20; ++i){
    reading = analogRead(leftSensor);
    if(reading > maxReading){
      maxReading = reading;
    }
  }
  return maxReading;
}

void pidControl(){
  leftrightSensoreading = leftInput = normalizedLeftReading();
  rightrightSensoreading = rightInput = normalizedRightReading();
  
  
  if(rightrightSensoreading < right_wall_missing + 10  && leftrightSensoreading < left_wall_missing + 10){ //- 30
    forward(COUNTERCLOCKWISE, CLOCKWISE);
    return;
  }
   else if(rightrightSensoreading < right_wall_missing ){ // without right wall
    leftInput = normalizedLeftReading();
    leftPid.Compute();
    if(leftOutput <= -100){
      leftOutput = -100;
    }
    else if(leftOutput >= 100){
      leftOutput = 100;
    }
    forward(COUNTERCLOCKWISE - leftOutput, CLOCKWISE - leftOutput);
    return;
  }
  else if(leftrightSensoreading < left_wall_missing){ // without left wall
    rightInput = normalizedRightReading();
    rightPid.Compute();
    if(rightOutput <= -100){
      rightOutput = -100;
    }
    else if(rightOutput >= 100){
      rightOutput = 100;
    }

    forward(COUNTERCLOCKWISE + rightOutput, CLOCKWISE + rightOutput);
    return;
  }
  
  else{
    
    leftInput = normalizedLeftReading();
    leftPid.Compute();
    
    rightInput = normalizedRightReading();
    rightPid.Compute();

    if(leftOutput <= -100){
      leftOutput = -100;
    }
    else if(leftOutput >= 100){
      leftOutput = 100;
    }

    if(rightOutput <= -100){
      rightOutput = -100;
    }
    else if(rightOutput >= 100){
      rightOutput = 100;
    }
    forward(COUNTERCLOCKWISE - leftOutput, CLOCKWISE+ rightOutput);
  }
  
}
