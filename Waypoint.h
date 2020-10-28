#ifndef WAYPOINT_H
#define WAYPOINT_H

// detect black line with array of a range of black values
MeLineFollower lineFinder(PORT_1);

#include "Color.h"
bool atWaypoint();

bool atWaypoint() {
  int sensorState = lineFinder.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN:   
      return true;
      break;
    case S1_IN_S2_OUT: 
      return false; 
      break;
    case S1_OUT_S2_IN: 
      return false; 
      break;
    case S1_OUT_S2_OUT: 
      return false;
      break;   
    default:
      return false;
      break;
  }
}

#endif
