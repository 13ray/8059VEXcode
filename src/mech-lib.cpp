#include "vex.h"

//values or thresholds
int liftPos = 0, tarliftPos = 97;

bool f = false, t = true;
bool LMState = t, RMState = t, BMState = f, TBState = t;

int op_threshold = 100;

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
      case 0: tarliftPos = 97; break;
      case 1: tarliftPos = 80; break;
      case 2: tarliftPos = 54; break;
    }
    int diffliftPos = pot_liftValue - tarliftPos;
    if(abs(diffliftPos) > 1) {
      if(pot_liftValue < tarliftPos) {
        lift.spin(fwd, 100, pct);
      }
      else if(pot_liftValue > tarliftPos) {
        lift.spin(reverse, 100, pct);
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

//2 bar pistons
void twoBar(bool s) {
  leftBar.set(s);
  rightBar.set(s);
  TBState = s;
}
//front mogo pistons
void frontMogo(bool s) {
  leftMogo.set(s);
  rightMogo.set(s);
  LMState = s;
  RMState = s;
}

//all pistons - toggle
void piston(char p) {
  if(p == *"lm") {
    LMState = !LMState;
    leftMogo.set(LMState);
  }
  else if(p == *"rm") {
    RMState = !RMState;
    rightMogo.set(RMState);
  }
  else if(p == *"bm") {
    BMState = !BMState;
    backMogo.set(BMState);
  }
  else if(p == *"tb") {
    TBState = !TBState;
    twoBar(TBState);
  }
}

//all pistons - change
void piston(char p, bool s) {
  if(p == *"lm") {
    LMState = s;
    leftMogo.set(LMState);
  }
  else if(p == *"rm") {
    RMState = s;
    rightMogo.set(RMState);
  }
  else if(p == *"bm") {
    BMState = s;
    backMogo.set(BMState);
  }
  else if(p == *"tb") {
    TBState = s;
    twoBar(TBState);
  }
}
