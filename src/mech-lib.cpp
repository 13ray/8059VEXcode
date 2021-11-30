#include "vex.h"

//values or thresholds
int liftPos = 1, tarliftPos = 53;
int liftPos1 = 92, liftPos2 = 76, liftPos3 = 53;

bool f = false, t = true;
bool LMState = f, RMState = f, BMState = t, TBState = f;

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
      case 1: tarliftPos = 92; break;
      case 2: tarliftPos = 76; break;
      case 3: tarliftPos = 53; break;
    }
    if(pot_liftValue != tarliftPos) {
      Controller1.rumble(".");
      if(pot_liftValue < tarliftPos) {
        lift.spin(fwd, 80, pct);
      }
      else if(pot_liftValue > tarliftPos) {
        lift.spin(reverse, 80, pct);
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

//close individual pistons
void LMCPiston(void) {
  piston(*"lm", true);
}
void RMCPiston(void) {
  piston(*"rm", true);
}

//auto open/close mogo pistons
void closeMogo() {
  op_leftMogo.objectDetected(LMCPiston);
  op_rightMogo.objectDetected(RMCPiston);
}