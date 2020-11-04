#define COLOR_H
#define LDRWait 10

#include <MeMCore.h>
#include "Puzzle.h"

MeRGBLed led(0, 30);
MeLightSensor lightSensor(PORT_8);

#define LDR 0   //LDR sensor pin at A0
#define LED 13  //Check Indicator to signal Calibration Completed
#define SCANTIMES 5
#define LDRwait 10

long RGBvalues[3] = {};
long total = 0;
//long blackvalues[3] = {182, 150, 165}; //black values for near full charge
long blackvalues[3] = {232, 190, 205};
/*long lookupvalues[5][3] = {
  {45, 0, 0}, //R
  {60, 35, 10}, //Y
  {10, 25, 10}, //G
  {30, 20, 40}, //P
  {35, 40, 50} //B
};*/

sign detectColor();
void getRGB();

sign detectColor() {
  motorLeft.run(0);
  motorRight.run(0);
  getRGB();
  // long color = 0;
  if (RGBvalues[0] >= 65) {
    return U_TURN; // color = 2;
  }
  else if (RGBvalues[0] >= 40) {
    return LEFT; // color = 1;
  }
  else if (RGBvalues[0] >= 20) {
    if (RGBvalues[1] >= 30) {
      return DOUBLE_RIGHT; // color = 5;
    } else {
      return DOUBLE_LEFT; // color = 4;
    }
  } 
  else {
    if (RGBvalues[1] >= 15) {
      return RIGHT; //color = 3;
    }
    else {
      return FINISH; // color = 0;
    }
  }
}

void getRGB() {
  for (long cycle = 0; cycle < 3; cycle += 1) {
    switch(cycle) {
      case 0:
        led.setColor(255, 0, 0);
        break;
      case 1:
        led.setColor(0, 255, 0);
        break;
      case 2:
        led.setColor(0, 0, 255);
        break;
      }
    led.show(); //Must use .show() to make new colour take effect.
    for (long i = 0; i < SCANTIMES; i += 1) {
      total += lightSensor.read();
      delay(LDRwait);
    }
    RGBvalues[cycle] = (long)((double)total / SCANTIMES - blackvalues[cycle]);
    total = 0;
  }
}
