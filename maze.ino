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
    halt();
    solve(detectColor());
  } 
  else {
    moveFront();
  }

//test ir
//  onIR();
//  calibrateMotion();
//  printm();
//  offIR();
//  delay(200);
}
