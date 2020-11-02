#ifndef MOTION_H
#define MOTION_H

#include <MeMCore.h>
#include "Proximity.h"

#define MAX_DISTANCE 3

#define HAS_LEFT_WALL 540
#define HAS_RIGHT_WALL 570
//5cm
#define MIN_GAP_LEFT 520
#define MIN_GAP_RIGHT 530
//3cm
#define EX_MIN_GAP_LEFT 400
#define EX_MIN_GAP_RIGHT 400

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
//  printm();
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
  if (left < EX_MIN_GAP_RIGHT) {
      steerHardRight();
  } else if (left < MIN_GAP_LEFT){
    steerRight();
//    Serial.println("left steer right");
  } 
//  else if (movingLeft()) {
//    steerRight();
//  } else if (movingRight()) {
//    steerLeft();
//  } 
  else {
    steerStraight();
//    Serial.println("left straight");
  }
}

void adjustRight(double right) {
  if (right < EX_MIN_GAP_RIGHT) {
      steerHardLeft();
  } else if (right < MIN_GAP_RIGHT){
    steerLeft();
  }
//  else if (movingLeft()) {
//    steerRight();
//  } else if (movingRight()) {
//    steerLeft();
//  }
  else {
    steerStraight();
  }
}

bool movingRight() {
  double prev;
  double next;
  for (int i = 0; i < 5; i++) {
    prev += readLeft();
  }
  delay(10);
  for (int i = 0; i < 5; i++) {
    next += readLeft();
  }
  prev = prev / 10;
  next = next / 10;
  if (next - prev > 10) {
    return true;
  }
  return false;
}

bool movingLeft() {
  double prev;
  double next;
  for (int i = 0; i < 10; i++) {
    prev += readRight();
  }
  delay(10);
  for (int i = 0; i < 10; i++) {
    next += readRight();
  }
  prev = prev / 10;
  next = next / 10;
  if (next - prev > 10) {
    return true;
  }
  return false;
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
  delay(600);
}

void turnRight() {
  motorLeft.run(-255);
  motorRight.run(0);
  delay(600);
}

void uTurn() {
  if (readLeft() < HAS_LEFT_WALL) {
    motorLeft.run(-255);
    motorRight.run(-255);
  } else {
    motorLeft.run(255);
    motorRight.run(255);
  }
  delay(600);
}

void halt() {
  motorLeft.stop();
  motorRight.stop();
}

#endif
