//***************************************************
//thunderNokia - by Andrew Nava-Juarez anava014@ucr.edu
//this code compiles for the Arduino Nano V3.0
//and is suffice to be considered the main code of the system
//***************************************************

#include "U8glib.h"
#include "PID.h"
#include <Servo.h>

#define APPROACHING_WALL 115
#define FRONT_LIMIT 300
#define COUNTERCLOCKWISE 1600
#define CLOCKWISE 1400
#define LEFT_TURN_DELAY 430
#define RIGHT_TURN_DELAY 448
#define ONE_STEP_DELAY 1060

Servo leftServo;
Servo rightServo;

//***************************************************
//PID
//***************************************************
double leftSetpoint, rightSetpoint, rightInput, leftInput, leftOutput, rightOutput;

//double Kp=.35, Ki=0, Kd=.15;
double Kp=.5, Ki=0, Kd=0;
PID leftPid(&leftInput, &leftOutput, &leftSetpoint, Kp, Ki, Kd, DIRECT);
PID rightPid(&rightInput, &rightOutput, &rightSetpoint, Kp, Ki, Kd, DIRECT);

//****************************************************

int left_wall_missing = 999;
int right_wall_missing = 999;


unsigned long int lastTime = 0;

unsigned char brightness = 3;

unsigned char middleLed = 9;
unsigned char leftLed = 12;
unsigned char rightLed = 13;

unsigned char leftSensor = A5;
unsigned char rightSensor = A3;
unsigned char middleSensor = A4;

int speaker = 5;

double errorL, errorR, errorM, skewL, skewR, skewM;

int leftrightSensoreading, rightrightSensoreading, middlerightSensoreading;

////////////////////////////////////////////////////////////////////

//LCD Initialization
U8GLIB_PCD8544 u8g(8, 4, 7, 2, 6);  // CLK=8, DIN=4, CE=7, DC=2, RST=6
 
void setup()
{
  Serial.begin(9600);
  pinMode(leftSensor, INPUT);
  pinMode(rightSensor, INPUT);
  pinMode(middleSensor, INPUT);
  
  pinMode(leftLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  pinMode(middleLed, OUTPUT);
  pinMode(brightness, OUTPUT);
  
  leftServo.attach(11);
  rightServo.attach(10);

  halt();
  bootMelody();

  liftOff();
  liftOffMelody();
  delay(1000);

  //IR Sensors Environment Calibration
  leftInput = analogRead(leftSensor);
  leftSetpoint = leftInput;
  rightInput = analogRead(rightSensor);
  rightSetpoint = rightInput;

  
  left_wall_missing = leftInput/1.289;
  right_wall_missing = rightInput/1.289;

  //turn the PID on
  leftPid.SetMode(AUTOMATIC);
  rightPid.SetMode(AUTOMATIC);
  
  u8g.setColorIndex(1); // pixel on 
  u8g.setRot90(); 
  drawSmallString("Waiting..");
}

//***************************************************
//This function utilizes the millis() arduino function to
//traverse one cell. Also detects front wall interrupt
//in case a wall occurs before the timer ends
//***************************************************
void mouseOneStep(){
  lastTime = millis();

  while(1){
    pidControl(); 
    
    if(millis() - lastTime >= ONE_STEP_DELAY){ //Once Cell Traversed
      break;
    }
    if(analogRead(middleSensor) > FRONT_LIMIT){ //Interrupted by Wall in front
      break;
    }
  }
  tone(speaker, 700, 100);
}


//***************************************************
//Main instructions
//1. Waits for either set or get from rPi
//2. Counts x iterations of cell traversals
//3. Counts x iterations of cell traversals
//4. If set was set, the character to be displayed on the lcd
//5. Drive home using walls as points of detection until 2 
// iterations of turning left
//***************************************************
void loop()
{
  while(1){
    if(Serial.available()){
      char input;
      int xCoor;
      int yCoor;
      String memory;  
  
      input = Serial.read();
      if(input == 's'){ //Setting memory
        backlightOn();
        //ALGORITHM ITSELF
        while(!Serial.available()){} 
        int xCoor = int(Serial.read()) - 48;
        if(xCoor < 0 || xCoor > 2){
          Serial.println("Invalid input");
          break;
        }
        while(!Serial.available()){} 
        int yCoor = int(Serial.read()) - 48;
        if(yCoor < 0 || yCoor > 2){
          Serial.println("Invalid input");
        }
        while(!Serial.available()){} 
        memory = char(Serial.read());
        u8g.setRot90();
        drawString(memory);
        for(int i = 0; i < xCoor; ++i){
          mouseOneStep();
        }
        leftTurn();
        u8g.setRot180();
        drawString(memory);
  
        for(int i = 0; i < yCoor; ++i){
          mouseOneStep();
        }
        leftPointTurn();
        halt();
        liftOffMelody();
        festiveLightShow();
        Serial.print('1');
        drawSmallString("Returning Home");
        rightPointTurn();
  
        while(analogRead(middleSensor) < FRONT_LIMIT){
          mouseOneStep();
        }
        leftTurn();

        while(analogRead(middleSensor) < FRONT_LIMIT){
          mouseOneStep();
        }
        leftTurn();
        u8g.undoRotation();
        drawSmallString("Returning Home");

        while(analogRead(middleSensor) < FRONT_LIMIT){
          mouseOneStep();
        }
        leftTurn();
        
        halt();
        liftOffMelody();
        backlightOff();
        u8g.setRot90(); 
        drawSmallString("Waiting..");
      }

      
      else if (input == 'g'){ //Getting Memory
        drawSmallString("Getting Memory..");
        liftOffMelody();
        backlightOn();
        while(!Serial.available()){} 
        int xCoor = int(Serial.read()) - 48;
        if(xCoor < 0 || xCoor > 2){
          Serial.println("Invalid input");
          break;
        }
        while(!Serial.available()){} 
        int yCoor = int(Serial.read()) - 48;
        if(yCoor < 0 || yCoor > 2){
          Serial.println("Invalid input");
        }
        for(int i = 0; i < xCoor; ++i)
          mouseOneStep();
  
        leftTurn();
        u8g.setRot180(); 
        drawSmallString("Getting Memory..");
  
        for(int i = 0; i < yCoor; ++i)
          mouseOneStep();
  
        leftPointTurn();
        halt();
        liftOffMelody();
        festiveLightShow();
        Serial.print('1');
        while(!Serial.available()){} 
        memory = char(Serial.read());
        drawString(memory);
        rightPointTurn();
  
        while(analogRead(middleSensor) < FRONT_LIMIT){
          mouseOneStep();
        }
        leftTurn();
        u8g.setRot270();
        drawString(memory);

        while(analogRead(middleSensor) < FRONT_LIMIT){
          mouseOneStep();
        }
        leftTurn();
        u8g.undoRotation();
        drawString(memory);

        while(analogRead(middleSensor) < FRONT_LIMIT){
          mouseOneStep();
        }
        leftTurn();
        u8g.setRot90();
          
        halt();
        liftOffMelody();
        backlightOff();
//        u8g.undoRotation();
        drawSmallString("Waiting..");
      }
    }
  }
}






