#ifndef MOTION_H
#define MOTION_H

#include <MeMCore.h>
#include "Proximity.h"

#define MAX_DISTANCE 3
//#define MAX_ANALOG_LEFT 610
//#define MAX_ANALOG_RIGHT 590
//#define MIN_GAP_LEFT 520
//#define MAX_GAP_LEFT 580
//#define MIN_GAP_RIGHT 450
//#define MAX_GAP_RIGHT 550

MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);

double MAX_ANALOG_LEFT;
double MAX_ANALOG_RIGHT; 
double MIN_GAP_LEFT; 
double MAX_GAP_LEFT;
double MIN_GAP_RIGHT;
double MAX_GAP_RIGHT;

void calibrateMotion();
void moveFront();
void adjustAngle(double right, double left);
void adjustCenter(double right, double left);
void adjustLeft(double left);
void adjustRight(double right);
void turnLeft();
void turnRight();
void uTurn();
void halt();

void printm() {
  Serial.print(MAX_ANALOG_LEFT);
  Serial.print(" ");
  Serial.print(MIN_GAP_LEFT);
  Serial.print(" ");
  Serial.print(MAX_GAP_LEFT);
  Serial.print(" ");
  Serial.print("---");
  Serial.print(" ");
  Serial.print(MAX_ANALOG_RIGHT);
  Serial.print(" ");
  Serial.print(MIN_GAP_RIGHT);
  Serial.print(" ");
  Serial.println(MAX_GAP_RIGHT);
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
  
  MIN_GAP_LEFT = (85 * MAX_ANALOG_LEFT) / 100;
  MAX_GAP_LEFT = (70 * MAX_ANALOG_LEFT) / 100;
  MIN_GAP_RIGHT = (85 * MAX_ANALOG_RIGHT) / 100;
  MAX_GAP_RIGHT = (70 * MAX_ANALOG_RIGHT) / 100;
}

void moveFront() {
  int left = readLeft();
  int right = readRight();
  adjustAngle(left, right);
}

// handle missing walls, bounce-band, use digital?
void adjustAngle(double left, double right) {
//  Serial.print(left);
//  Serial.print(" ");
//  Serial.print(right);
//  Serial.print(" ");
  if (left > MAX_ANALOG_LEFT && right > MAX_ANALOG_RIGHT) {
    motorLeft.run(-255);
    motorRight.run(255);
//    Serial.println("center");
  } else if (left> MAX_ANALOG_LEFT) {
    adjustRight(right);
  } else if (right > MAX_ANALOG_RIGHT) {
    adjustLeft(left);
  } else {
    adjustCenter(left, right);
  }
}

void adjustCenter(double left, double right) {
  if (left < MIN_GAP_LEFT) {
    motorLeft.run(-255);
    motorRight.run(200);
//    Serial.println("center turn right");
  } else if (right < MIN_GAP_RIGHT) {
    motorLeft.run(-200);
    motorRight.run(255);
//    Serial.println("center turn left");
  } else {
    motorLeft.run(-255);
    motorRight.run(255);
//    Serial.println("center straight");
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
  if (left < MIN_GAP_LEFT) {
    motorLeft.run(-255);
    motorRight.run(200);
//    Serial.println("left turn right");
  } else if (left > MAX_GAP_LEFT) {
    motorLeft.run(-200);
    motorRight.run(255);
//    Serial.println("left turn left");
  } else {
    motorLeft.run(-255);
    motorRight.run(255);
//    Serial.println("left straight");
  }
}

void adjustRight(double right) {
  if (right < MIN_GAP_RIGHT) {
    motorLeft.run(-200);
    motorRight.run(255);
//    Serial.println("right turn right");
  } else if (right > MAX_GAP_RIGHT) {
    motorLeft.run(-255);
    motorRight.run(200);
//    Serial.println("right turn left");
  } else {
    motorLeft.run(-255);
    motorRight.run(255);
//    Serial.println("right straight");
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
