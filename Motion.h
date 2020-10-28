#ifndef MOTION_H
#define MOTION_H

#include <MeMCore.h>
#include "Proximity.h"

#define MAX_DISTANCE 3
#define MIN_ANALOG 50
#define MAX_ANALOG 400
#define MIN_GAP 100
#define MAX_GAP 150


MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);

void moveFront();
void adjustAngle(double right, double left);
void adjustCenter(double right, double left);
void adjustLeft(double left);
void adjustRight(double right);
void turnLeft();
void turnRight();
void uTurn();
void halt();

void moveFront() {
  int left = readLeft();
  int right = readRight();
  adjustAngle(left, right);
  delay(100); // needed?
}

// handle missing walls, bounce-band, use digital?
void adjustAngle(double right, double left) {
  if (right == -1 && left == -1) {
    motorLeft.run(-255);
    motorRight.run(255);
  } else if (right == -1) {
    adjustLeft(left);
  } else if (left == -1) {
    adjustRight(right);
  } else {
    adjustCenter(right, left);
  }
}

void adjustCenter(double right, double left) {
  if (left < MIN_GAP) {
    motorLeft.run(-255);
    motorRight.run(200);
  } else if (right < MIN_GAP) {
    motorLeft.run(-200);
    motorRight.run(255);
  } else {
    motorLeft.run(-255);
    motorRight.run(255);
  }
}

//int in = 0;
//int timer;
//
//void adjustLeft(double left) {
//  if (millis() < timer) {
//    motorLeft.run(-200);
//    motorRight.run(250);
//  } else if (left < MIN_GAP) {
//    motorLeft.run(-255);
//    motorRight.run(200);
//    in = 1;
//  } else if (left < MAX_GAP) {
//    if (in == 1) {
//      timer = millis() + 200;
//      in = 0;
//    }
//  }
//}

void adjustLeft(double left) {
  if (left < MIN_GAP) {
    motorLeft.run(-255);
    motorRight.run(200);
  } else if (left > MAX_GAP) {
    motorLeft.run(-200);
    motorRight.run(255);
  } else {
    motorLeft.run(-255);
    motorRight.run(255);
  }
}

void adjustRight(double right) {
  if (right < MIN_GAP) {
    motorLeft.run(-200);
    motorRight.run(255);
  } else if (right > MAX_GAP) {
    motorLeft.run(-255);
    motorRight.run(200);
  } else {
    motorLeft.run(-255);
    motorRight.run(255);
  }
}


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
  motorLeft.run(255);
  motorRight.run(255);
  delay(600);
}

void halt() {
  motorLeft.stop();
  motorRight.stop();
}

#endif
