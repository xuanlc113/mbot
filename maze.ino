#include "Proximity.h"
#include "Motion.h"
#include "Waypoint.h"
#include "Color.h"
#include "Puzzle.h"

void setup() {
  Serial.begin(9600);
  onIR();
}

void loop() {
  if (atWaypoint()) {
    solve(detectColor());
  } else {
    moveFront();
  }
}
