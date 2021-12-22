#include "vex.h"

//values or thresholds
int liftPos = 0, tarliftPos = 80, prevliftPos = 0;

bool f = false, t = true;

//ring intake
void con(int c) {
  conveyor.spin(fwd, c, pct);
}

void con(int c, double t) {
  con(c);
  wait(t, msec);
  conveyor.stop(hold);
}

//two bar pistons
void twoBar(bool s) {
  twoBarL.set(s);
  twoBarR.set(s);
}

//liftassist pistons
void liftAssist(bool s) {
  liftAssistL.set(s);
  liftAssistR.set(s);
}

//move lift to specific positions
int Lift() {
  while(t) {
    switch(liftPos) {
      case 0: tarliftPos = 80; break;
      case 1: tarliftPos = 75; break;
      case 2: tarliftPos = 52; break;
    }
    if(abs(pot_liftValue - tarliftPos) > 1) {
      if(pot_liftValue < tarliftPos) { //going down
        lift.spin(reverse, 100, pct);
      }
      else if(pot_liftValue > tarliftPos) { //going up
        lift.spin(fwd, 100, pct);
      }
    }
    else {
      lift.stop(hold);
    }
    if(lift.voltage() > 2) {liftAssist(f);}
    else {liftAssist(t);}
  }
  return(0);
}