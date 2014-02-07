#include <Arduino.h>

void setup();
void printReadings(int ls, int rs);
int calculateError(int reading);
int avg(int a, int b);
void adjustedForward(int leftSpeed, int rightSpeed);
void stop();
void loop();
#line 1 "src/sketch.ino"
/* MOTOR CONFIGURATION */
int leftMotor1 = 3;
int leftMotor2 = 5;
int rightMotor1 = 6;
int rightMotor2 = 9;

/* INPUT CONFIGURATION */
int onSwitch = 2;
int FL = A0;
int FR = A1;
int NL = A2;
int NR = A3;

unsigned int readFL;
unsigned int readFR;
unsigned int readNL;
unsigned int readNR;

/* VEHICLE CONFIGURATION */
int maxBrightness = 50;
int maxSpeed = 80;
int gain = 1;

void setup(){
  Serial.begin(9600);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);

  pinMode(FL, INPUT);
  pinMode(FR, INPUT);
  pinMode(NL, INPUT);
  pinMode(NR, INPUT);
}

/* HELPER FUNCTIONS */

void printReadings(int ls, int rs){
  Serial.print(readFL);
  Serial.print(" ");
  Serial.print(readNL);
  Serial.print(" ");
  Serial.print(readNR);
  Serial.print(" ");
  Serial.print(readFR);
  Serial.print("     ");
  Serial.print(ls);
  Serial.print("     ");
  Serial.print(rs);
  Serial.println();
}

int calculateError(int reading){
  int error = maxBrightness - reading;
  if (error < 5)
    return 0;
  return error;
}

int avg(int a, int b){
  return (a+b)/2;
}

void adjustedForward(int leftSpeed, int rightSpeed){
  analogWrite(leftMotor2, leftSpeed);
  analogWrite(leftMotor1, 0);
  analogWrite(rightMotor2, rightSpeed);
  analogWrite(rightMotor1, 0);
}

void stop(){
  analogWrite(leftMotor1, 0);
  analogWrite(leftMotor2, 0);
  analogWrite(rightMotor1, 0);
  analogWrite(rightMotor2, 0);
}

void loop(){
  readFL = analogRead(FL);
  readNL = analogRead(NL);
  readNR = analogRead(NR);
  readFR = analogRead(FR);

 
  // COMPARISON BASED CONTROL

  // int leftSpeed, rightSpeed;
  // int leftError, rightError;
  // if (readNL < (readNR - 5)){
  //   leftError = readNR - readNL;
  //   leftSpeed = maxSpeed - gain*leftError;
  //   if (leftSpeed < 10) leftSpeed = 0;

  //   rightSpeed = maxSpeed;
  // }
  // else if (readNL > (readNR + 5)){
  //   rightError = readNL - readNR;
  //   rightSpeed = maxSpeed - gain*rightError;
  //   if (rightSpeed < 10) rightSpeed = 0;

  //   leftSpeed = maxSpeed;
  // }

  // HARDCODED CONTROL

  // int leftError = calculateError(readNL);
  // int leftSpeed = maxSpeed - gain*leftError;
  // if (leftSpeed < 10)
  //   leftSpeed = 0;

  // int rightError = calculateError(readNR);
  // int rightSpeed = maxSpeed - gain*rightError;
  // if (rightSpeed < 10)
  //   rightSpeed = 0;

  // if (leftSpeed < rightSpeed){
  //   rightSpeed = maxSpeed;
  //   // leftSpeed = maxSpeed-gain*rightError;
  // }
  // else {
  //   // rightSpeed = maxSpeed - gain*leftError;
  //   leftSpeed = maxSpeed;
  // }

  // READING COMPARISON

  int leftSpeed = gain*readFL;
  int rightSpeed = gain*readFR;

  printReadings(leftSpeed, rightSpeed);

  if (digitalRead(onSwitch)==1){
    adjustedForward(leftSpeed, rightSpeed);
  }
  else {
    stop();
  }
}
