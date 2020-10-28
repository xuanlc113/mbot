#ifndef PROXIMITY_H
#define PROXIMITY_H

#include <MeMCore.h>

MePort IR(PORT_3);
MeUltrasonicSensor ultrasonic(PORT_3);

void onIR();
void offIR();
int readLeft();
int readRight();
double getFrontDistance();

void onIR() {
  IR.dWrite1(HIGH);
  IR.dWrite2(HIGH);
}

void offIR() {
  IR.dWrite1(LOW);
  IR.dWrite2(LOW);
}

int readLeft() {
  return IR.aRead1();
}

int readRight() {
  return IR.aRead2();
}

double getFrontDistance() {
  return ultrasonic.distanceCm();
}

#endif
