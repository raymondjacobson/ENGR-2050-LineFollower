#include <Arduino.h>

void setup();
void startstop();
int aInToOut(int number);
void forward(int speed);
void adjustedForward(int leftSpeed, int rightSpeed);
void reverse(int speed);
void left(int speed);
void right(int speed);
void stop();
void loop();
#line 1 "src/sketch.ino"
/* MOTOR CONFIGURATION */
int leftMotor1 = 3;
int leftMotor2 = 5;
int rightMotor1 = 6;
int rightMotor2 = 9;

/* INPUT CONFIGURATION */
int pushbutton = 2;
int lastPBState = LOW;
bool on = false;

/* VEHICLE CONFIGURATION */
int speed = 200; // out of 255
int leftSpeed;
int rightSpeed;

int leftPhotoTransistor = A3;
int rightPhotoTransistor = A2;

void setup(){
  Serial.begin(9600);
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);
}

/* HELPER FUNCTIONS */

void startstop(){
  on = !on;
}

int aInToOut(int number){
  return (((number*40)/1024.0)*255);
}

void forward(int speed){
  analogWrite(leftMotor2, speed);
  analogWrite(leftMotor1, 0);
  analogWrite(rightMotor2, speed);
  analogWrite(rightMotor1, 0);
}

void adjustedForward(int leftSpeed, int rightSpeed){
  analogWrite(leftMotor2, leftSpeed);
  analogWrite(leftMotor1, 0);
  analogWrite(rightMotor2, rightSpeed);
  analogWrite(rightMotor1, 0);
}

void reverse(int speed){
  analogWrite(leftMotor1, speed);
  analogWrite(leftMotor2, 0);
  analogWrite(rightMotor1, speed);
  analogWrite(rightMotor2, 0);
}

void left(int speed){
  analogWrite(leftMotor2, speed);
  analogWrite(leftMotor1, 0);
  analogWrite(rightMotor2, 0);
  analogWrite(rightMotor1, speed);
}

void right(int speed){
  analogWrite(leftMotor2, 0);
  analogWrite(leftMotor1, speed);
  analogWrite(rightMotor2, speed);
  analogWrite(rightMotor1, 0);
}

void stop(){
  analogWrite(leftMotor1, 0);
  analogWrite(leftMotor2, 0);
  analogWrite(rightMotor1, 0);
  analogWrite(rightMotor2, 0);
}

void loop(){
  int pbResponse = digitalRead(pushbutton);
  if (pbResponse == HIGH && lastPBState == LOW){
    startstop();
  }
  lastPBState = pbResponse;

  leftSpeed = aInToOut(analogRead(leftPhotoTransistor));
  rightSpeed = aInToOut(analogRead(rightPhotoTransistor));
  // Serial.println(leftSpeed);
  if (on){
    adjustedForward(leftSpeed, rightSpeed);
    // forward(speed);
  }
  else {
    stop();
  }
}
