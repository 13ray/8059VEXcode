#include "vex.h"
#include "math.h"

//values or thresholds
int liftPos = 0, prevliftPos = 0;
double tarliftPos = 75, potRange = 0.5;

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

//Latch pistons 
void Latch(bool s){
  latch.set(s);
}

int Lift() {         //move to specific position 
  while(t) {
    switch(liftPos) {
      case 0: tarliftPos =75; break; //170
      case 1: tarliftPos = 65; break; //180
      case 2: tarliftPos = 17; break; //252
      case 3: tarliftPos = 25; break; //before latch 
      case 4: tarliftPos = 50; break; //hang
    }
    int potDiff = tarliftPos - pot_liftValue;
    double kP= 10;
    double kD = 5;
    //printf("lift val:%d\n", pot_liftValue);

    if(abs(potDiff) > potRange) {
      lift(potDiff*kP);
      if(abs(potDiff) < 40){
        lift(potDiff*kD);
      }

    }
    else {
      leftLift.stop(hold);
      rightLift.stop(hold);
    }
  }
  return(0);
}

//void Hang(bool s){
  

