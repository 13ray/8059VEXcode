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

void twoBar(bool s) {
  twoBarL.set(s);
  twoBarR.set(s);
}

void liftAssist(bool s) {
  liftAssistL.set(s);
  liftAssistR.set(s);
}

//move lift to specific positions
int Lift() {
  while(t) {
    switch(liftPos) {
      case 0: tarliftPos = 81, liftAssist(f); break;
      case 1: tarliftPos = 75; liftAssist(t); break;
      case 2: tarliftPos = 50; liftAssist(t); break;
    }
    if(abs(pot_liftValue - tarliftPos) > 1) {
      if(pot_liftValue < tarliftPos) {
        lift.spin(reverse, 100, pct);
      }
      else if(pot_liftValue > tarliftPos) {
        lift.spin(fwd, 100, pct);
      }
      else {
        lift.stop(hold);
      }
    }
    else {
      lift.stop(hold);
    }
  }
  return(0);
}

//2 bar
