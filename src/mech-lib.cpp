#include "vex.h"

//values or thresholds
int liftPos = 0, tarliftPos = 80, prevliftPos = 0, potRange = 10;

bool f = false, t = true;

//lift
void lift(int s) {
  leftLift.spin(fwd, s, pct);
  rightLift.spin(fwd, s, pct);
}

void lift(int s, int t) {
  lift(s);
  wait(t, msec);
  leftLift.stop(hold);
  rightLift.stop(hold);
}

//two bar pistons
void twoBar(bool s) {
  twoBarL.set(s);
  twoBarR.set(s);
}

//move lift to specific positions
int Lift() {
  while(t) {
    switch(liftPos) {
      case 0: tarliftPos = 202; break; //80
      case 1: tarliftPos = 180; break; //75
      case 2: tarliftPos = 128; break; //52
    }
    if(liftPos == 1) {potRange = 10;}
    else {potRange = 4;}

    int potDiff = pot_liftValue - tarliftPos;
    if(potDiff > potRange || potDiff < -potRange) {
      if(pot_liftValue < tarliftPos) { //going down
        lift(-100);
      }
      else if(pot_liftValue > tarliftPos) { //going up
        lift(100);
      }
    }
    else {
      leftLift.stop(hold);
      rightLift.stop(hold);
    }
  }
  return(0);
}