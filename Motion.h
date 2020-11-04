#ifndef MOTION_H
#define MOTION_H

#include <MeMCore.h>
#include "Proximity.h"

#define DELAY 600

#define MAX_DISTANCE 3

#define HAS_LEFT_WALL 520
#define HAS_RIGHT_WALL 640
//5cm
#define MIN_GAP_LEFT 430
#define MIN_GAP_RIGHT 540
//3cm
#define EX_MIN_GAP_LEFT 400
#define EX_MIN_GAP_RIGHT 500

MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);

double MAX_ANALOG_LEFT;
double MAX_ANALOG_RIGHT; 

void calibrateMotion();
void moveFront();
void adjustAngle(double right, double left);
void adjustCenter(double right, double left);
void adjustLeft(double left);
void adjustRight(double right);
bool movingLeft();
bool movingRight();
void newSteerLeft(int right);
void newSteerRight(int left);
void steerStraight();
void steerLeft();
void steerHardLeft();
void steerRight();
void steerHardRight();
void turnLeft();
void turnRight();
void uTurn();
void halt();

void printm() {
  Serial.print(MAX_ANALOG_LEFT);
  Serial.print(" ");
  Serial.println(MAX_ANALOG_RIGHT);
}

void calibrateMotion() {
  MAX_ANALOG_RIGHT = 0;
  MAX_ANALOG_LEFT = 0;
  for (int i = 0; i < 20; i++) {
    MAX_ANALOG_RIGHT += readRight();
  }
  for (int i = 0; i < 20; i++) {
    MAX_ANALOG_LEFT += readLeft();
  }
  MAX_ANALOG_LEFT = (MAX_ANALOG_LEFT / 20) - 15;
  MAX_ANALOG_RIGHT = (MAX_ANALOG_RIGHT / 20) - 15;
}

void moveFront() {
  int left = readLeft();
  int right = readRight();
  adjustAngle(left, right);
}

void adjustAngle(double left, double right) {
  if (right < HAS_RIGHT_WALL) {
    adjustRight(right);
  } else if (left < HAS_LEFT_WALL) {
    adjustLeft(left);
  } else {
    adjustCenter(left, right);
  }
}

void adjustCenter(double left, double right) {
  steerStraight();
}

void adjustLeft(double left) {
//  if (left < EX_MIN_GAP_RIGHT) {
//      steerHardRight();
//  } else 
  if (left < MIN_GAP_LEFT){
    newSteerRight(left);
  }
  else {
    steerStraight();
  }
}

void adjustRight(double right) {
//  if (right < EX_MIN_GAP_RIGHT) {
//      steerHardLeft();
//  } else 
  if (right < MIN_GAP_RIGHT){
    newSteerLeft(right);
  }
  else {
    steerStraight();
  }
}

//right y = 121.73x - 9.9589
void newSteerLeft(int right) {
  double y = ((double) 122 * right) - 10;
  int i = (int) y * -255;
  motorLeft.run(i);
  motorRight.run(255);
}

//left y = 105x - 570
void newSteerRight(int left) {
  double y = ((double) 105 * left) - 57;
  int i = (int) y * 255;
  motorLeft.run(-255);
  motorRight.run(i);
}

void steerStraight() {
  motorLeft.run(-255);
  motorRight.run(255);
}

void steerLeft() {
  motorLeft.run(-225);
  motorRight.run(255);
}

void steerHardLeft() {
  motorLeft.run(-200);
  motorRight.run(255);
}

void steerRight() {
  motorLeft.run(-255);
  motorRight.run(225);
}

void steerHardRight() {
  motorLeft.run(-255);
  motorRight.run(200);
}

// puzzle motion

void turnLeft() {
  motorLeft.run(0);
  motorRight.run(255);
  delay(DELAY);
}

void turnRight() {
  motorLeft.run(-255);
  motorRight.run(0);
  delay(DELAY);
}

void uTurn() {
  if (readLeft() < HAS_LEFT_WALL) {
    motorLeft.run(-255);
    motorRight.run(-255);
  } else if (readRight() < HAS_RIGHT_WALL) {
    motorLeft.run(255);
    motorRight.run(255);
  } else {
    motorLeft.run(255);
    motorRight.run(255);
  }
  delay(DELAY - 50);
}

void halt() {
  motorLeft.stop();
  motorRight.stop();
}

#endif
