void leftServoClockwise(){
  leftServo.writeMicroseconds(CLOCKWISE);
}

void rightServoClockwise(){
  rightServo.writeMicroseconds(CLOCKWISE);
}

void leftServoCounterClockwise(){
  leftServo.writeMicroseconds(COUNTERCLOCKWISE);
}

void rightServoCounterClockwise(){
  rightServo.writeMicroseconds(COUNTERCLOCKWISE);
}

void leftPointTurn(){
  delay(300);
  leftServoClockwise();
  rightServoClockwise();
  delay(200);
  reverse();
  delay(300);
  leftServoClockwise();
  rightServoClockwise();
  delay(250);
}

void rightPointTurn(){
  leftServoCounterClockwise();
  rightServoCounterClockwise();
  delay(200);
  forward();
  delay(150);
  leftServoCounterClockwise();
  rightServoCounterClockwise();
  delay(350);
}

void reverse(){
  leftServoClockwise();
  rightServoCounterClockwise();
}

void forward(){
  leftServoCounterClockwise();
  rightServoClockwise();
}

void forward(int leftSpeed, int rightSpeed){
  leftServo.writeMicroseconds(leftSpeed);
  rightServo.writeMicroseconds(rightSpeed);
}

void rightTurn(){
  leftServoCounterClockwise();
  rightServoCounterClockwise();
  delay(RIGHT_TURN_DELAY);
}

void leftTurn(){
  leftServoClockwise();
  rightServoClockwise();
  delay(LEFT_TURN_DELAY);
//  halt();
}

void halt(){
  leftServo.writeMicroseconds(1500);
  rightServo.writeMicroseconds(1500);
}




