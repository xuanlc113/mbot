#ifndef WAYPOINT_H
#define WAYPOINT_H

MeLineFollower lineFinder(PORT_1);

bool bothLineIn();
bool atWaypoint();

void adjustWaypointLeft();
void adjustWaypointRight();

bool bothLineIn() {
  if (lineFinder.readSensors() == S1_IN_S2_IN) {
    return true;
  }
  return false;
}

bool atWaypoint() {
  int sensorState = lineFinder.readSensors();
  
  switch(sensorState)
  {
    case S1_IN_S2_IN:  
  Serial.println(" sdfs"); 
      return true;
      break;
    case S1_IN_S2_OUT:
      // adjustWaypointRight(); 
      return false; 
      break;
    case S1_OUT_S2_IN:
      // adjustWaypointLeft();
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

void adjustWaypointLeft() {
  while (!bothLineIn()) {
    motorLeft.run(0);
    motorRight.run(255);
  }
  motorRight.run(0);
}

void adjustWaypointRight() {
  while (!bothLineIn()) {
    motorLeft.run(-255);
    motorRight.run(0);
  }
  motorLeft.run(0);
}

#endif
