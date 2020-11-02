#ifndef TUNE_H
#define TUNE_H

#include "Motion.h"

MeBuzzer buzzer;

void celebrate();

void celebrate() {
  halt();
  buzzer.tone(600, 1000);   //Buzzer sounds 600Hz for 1000ms
  delay(2000);              //Pause for 2000ms, Buzzer no sound
  buzzer.tone(1200, 1000);  //Buzzer sounds 1200Hz for 1000ms
  delay(2000);              //Pause for 2000ms, Buzzer no sound
  
  noInterrupts();
  while(true) {}
}

#endif
