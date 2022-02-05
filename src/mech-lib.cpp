#include "vex.h"

//values or thresholds
int liftPos = 0, prevliftPos = 0;
int tarliftPos = 87, potRange = 1, potDiff = 0;
bool lifting = f;

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

//two bar pistons: false = down
void twoBar(bool s) {
  if(s){
    twoBarL.set(t);
    twoBarR.set(t);
  }else{
    twoBarL.set(f);
    twoBarR.set(f);    
  }
}

//front mogo: true = release
void frontMOG(bool s){
  if(s){
    frontMogo.set(f);
  }else{
    frontMogo.set(t);
  }
}

//hanging process
void hang(){
  while(pot_liftValue > 117 || pot_liftValue < 115){
    if(liftPos == 2) liftPos = 3;
    latch.set(t);
    if(liftPos == 3) liftPos = 4;
  }
}

//wait for lift to finish moving
void waitLift(){
  while(t){
    wait(10, msec);
    if(!lifting) break;
  }
}

int Lift() {         //move to specific position 
  while(t) {
    switch(liftPos) {
      case 0: tarliftPos = 87; break; //139 lowest
      case 1: tarliftPos = 128; break; //99 scoring
      case 2: tarliftPos = 160; break; //72 highest
      case 3: tarliftPos = 146; break; //80 before latch 
      case 4: tarliftPos = 116; break; //111 hang
      case 5: tarliftPos = 100; break; //130 moving in auton
    }

    potDiff = tarliftPos - pot_liftValue;

    //pid for lift
    if(abs(potDiff) > potRange) {
      lifting = t;
      if(abs(potDiff) < 10){
        lift(potDiff*-5);
      }
      else{
        lift(potDiff*-15);
      }
    }
    else {
      lifting = f;
      leftLift.stop(hold);
      rightLift.stop(hold);
    }
    // printf("pot Diff: %d\n", potDiff);
    // printf("speed: %.2f\n", leftLift.velocity(pct));
    wait(5, msec);
  }
  return(0);
}