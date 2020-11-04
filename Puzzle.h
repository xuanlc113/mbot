#ifndef PUZZLE_H
#define PUZZLE_H

#include "Motion.h"
#include "Proximity.h"
#include "Tune.h"

#define GAP 8

enum sign {
  LEFT,
  RIGHT,
  U_TURN,
  DOUBLE_LEFT,
  DOUBLE_RIGHT,
  FINISH
};

void solve(sign i);
void doubleLeft();
void doubleRight();
void finish();

void solve(sign i) {
  switch(i) {
    case LEFT:
      turnLeft();
      break;
    
    case RIGHT:
      turnRight();
      break;
    
    case U_TURN:
      uTurn();
      break;
    
    case DOUBLE_RIGHT:
      doubleRight();
      break;
    
    case DOUBLE_LEFT:
      doubleLeft();
      break;
    
    case FINISH: 
      celebrate();
      break;
  }
}

void doubleLeft() {
  turnLeft();
  while (getFrontDistance() > GAP) {
//    moveFront();
steerStraight();
  }
  turnLeft();
}

void doubleRight() {
  turnRight();
  while (getFrontDistance() > GAP) {
//    moveFront();
    steerStraight();
  }
  turnRight();
}

#endif
