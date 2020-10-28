#ifndef PUZZLE_H
#define PUZZLE_H

#include "Motion.h"
#include "Proximity.h"
#include "Tune.h"

#define GAP 4

enum sign {
  LEFT,
  RIGHT,
  U_TURN,
  DOUBLE_LEFT,
  DOUBLE_RIGHT,
  FINISH
};

void solve(sign i);
// while loop to replace main loop()
void doubleLeft();
void doubleRight();
void finish();

void solve(sign i) {
  switch(i) {
    LEFT:
      turnLeft();
      break;
    DOUBLE_LEFT:
      doubleLeft();
      break;
  }
}

void doubleLeft() {
  turnLeft();
  while (getFrontDistance() > GAP) {
    moveFront();
  }
  turnLeft();
}

#endif
