#include "vex.h"
#include "math.h"

//values or thresholds
int liftPos = 0, tarliftPos = 202, prevliftPos = 0, potRange = 3;

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

void liftRot(int rot){
  leftLift.rotateTo(rot,deg);
  rightLift.rotateTo(rot, deg);
}

//two bar pistons
void twoBar(bool s) {
  twoBarL.set(s);
  twoBarR.set(s);
}

int Lift() {         //move to specific position 
  while(t) {
    switch(liftPos) {
      case 0: tarliftPos = 202; break; //80
      case 1: tarliftPos = 180; break; //75
      case 2: tarliftPos = 125; break; //52
    }

    int lw = 0;

    if(liftPos == 0) {potRange = 2;}
    else {potRange = 3;}

    int potDiff = absD(pot_liftValue - tarliftPos);

    if(potDiff > potRange) {
      if(pot_liftValue < (tarliftPos+lw)) { //going down
        lift(-100);
        if(pot_liftValue < tarliftPos+lw){
          lift(-30);
        }
      }
      else if(pot_liftValue > (tarliftPos + lw)) { //going up
        lift(100);
        if(pot_liftValue > tarliftPos){
          lift(30);
        }
      }
    }
    else {
      leftLift.stop(hold);
      rightLift.stop(hold);
    }
  }
  return(0);
}
