#include "Proximity.h"
#include "Motion.h"
#include "Waypoint.h"
#include "Color.h"
#include "Puzzle.h"

void setup() {
  Serial.begin(9600);
  led.setpin(13);
  onIR();
}

void loop() {
  if (atWaypoint()) {
    solve(detectColor());
  } 
else {
    moveFront();
  }

//uTurn();
//halt();
//delay(2000);
//doubleLeft();
//halt();
//delay(2000);
//doubleRight();
//halt();
//delay(2000);

//test ir
//  onIR();
//  calibrateMotion();
//  printm();
//  offIR();
//  delay(200);
}
