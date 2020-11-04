#ifndef MOTION_H
#define MOTION_H

#include <MeMCore.h>
#include "Proximity.h"

#define DELAY 600
#define LEFT_WALL 520
#define RIGHT_WALL 640
#define IR_MAX_DISTANCE 6
#define ULTRASOUND_GAP 8

// y = 0.0086x + 0.6004
const double GRADIENT_LEFT = 0.0086;
const double INTERCEPT_LEFT = 0.6004;
const double GRADIENT_RIGHT = 121.73;
const double INTERCEPT_RIGHT = -9.9589;

MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);

// for calibration
double MAX_ANALOG_LEFT;
double MAX_ANALOG_RIGHT;

void moveFront();
void adjustAngle(double right, double left);
bool hasLeftWall(int left);
bool hasRightWall(int right);
void steerLeft(int right);
void steerRight(int left);
void steerStraight();
void halt();
void turnLeft();
void turnRight();
void uTurn();
void doubleLeft();
void doubleRight();

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
  MAX_ANALOG_LEFT = (MAX_ANALOG_LEFT / 20);
  MAX_ANALOG_RIGHT = (MAX_ANALOG_RIGHT / 20);
}

void moveFront() {
  int left = readLeft();
  int right = readRight();
  adjustAngle(left, right);
}

void adjustAngle(double left, double right) {
  if (hasRightWall(right)) {
    steerLeft(right);
  } else if (hasLeftWall(left)) {
    steerRight(left);
  } else {
    steerStraight();
  }
}

bool hasLeftWall(int left) {
  return left < LEFT_WALL;
}

bool hasRightWall(int right) {
  return right < RIGHT_WALL;
}

void steerLeft(int right) {
  double ratio = ((GRADIENT_RIGHT * right) + INTERCEPT_RIGHT) / IR_MAX_DISTANCE;
  int i = (int) ratio * -255;
  motorLeft.run(i);
  motorRight.run(255);
}

void steerRight(int left) {
  double ratio = ((GRADIENT_LEFT * left) + INTERCEPT_LEFT) / IR_MAX_DISTANCE;
  int i = (int) ratio * 255;
  motorLeft.run(-255);
  motorRight.run(i);
}

void steerStraight() {
  motorLeft.run(-255);
  motorRight.run(255);
}

void halt() {
  motorLeft.stop();
  motorRight.stop();
}

// puzzle motion

void turnLeft() {
  motorLeft.stop();
  motorRight.run(255);
  delay(DELAY);
}

void turnRight() {
  motorLeft.run(-255);
  motorRight.stop();
  delay(DELAY);
}

void uTurn() {
  if (hasLeftWall(readLeft())) {
    motorLeft.run(-255);
    motorRight.run(-255);
  } else {
    motorLeft.run(255);
    motorRight.run(255);
  }
  delay(DELAY - 50);
}

void doubleLeft() {
  turnLeft();
  while (getFrontDistance() > ULTRASOUND_GAP) {
    moveFront();
  }
  turnLeft();
}

void doubleRight() {
  turnRight();
  while (getFrontDistance() > ULTRASOUND_GAP) {
    moveFront();
  }
  turnRight();
}

#endif
