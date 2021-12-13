#include "vex.h"

//values or thresholds
int liftPos = 0, tarliftPos = 97;

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

//move lift to specific positions
int Lift() {
  while(t) {
    switch(liftPos) {
      case 0: tarliftPos = 97, antiTip.set(f); break;
      case 1: tarliftPos = 80; antiTip.set(t); break;
      case 2: tarliftPos = 54; antiTip.set(t); break;
    }
    if(abs(pot_liftValue - tarliftPos) > 1) {
      if(pot_liftValue < tarliftPos) {
        lift.spin(fwd, 100, pct);
        pressure.set(f);
        liftAssist.set(t);
      }
      else if(pot_liftValue > tarliftPos) {
        lift.spin(reverse, 100, pct);
        pressure.set(t);
        liftAssist.set(f);
      }
      else {
        lift.stop(hold);
      }
    }
    else {
      if(liftPos == 0) {
        pressure.set(f);
        liftAssist.set(t);
      }
      else {
        pressure.set(t);
        liftAssist.set(f);
      }
      lift.stop(hold);
    }
  }
  return(0);
}

//2 bar
