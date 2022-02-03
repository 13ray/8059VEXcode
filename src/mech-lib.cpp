#include "vex.h"

//values or thresholds
int liftPos = 0, prevliftPos = 0;
int tarliftPos = 88, potRange = 1, potDiff = 0;

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

//two bar pistons: true = open
void twoBar(bool s) {
  if(s){
    twoBarL.open();
    twoBarR.open();
  }else{
    twoBarL.close();
    twoBarR.close();    
  }
}

//front mogo
void frontMOG(bool s){
  if(s){
    frontMogo.open();
  }else{
    frontMogo.close();
  }
}

//Latch pistons true = open = backwards
void Latch(bool s){
  if(s){
    latch.open();
  }else{
    latch.close();
  }
}

//hanging process
void hang(){
  while(pot_liftValue > 112 || pot_liftValue < 110){
    if(liftPos == 2) liftPos = 3;
    Latch(t);
    if(liftPos == 3) liftPos = 4;
  }
}

int Lift() {         //move to specific position 
  while(t) {
    switch(liftPos) {
      case 0: tarliftPos = 88; break; //139 lowest
      case 1: tarliftPos = 128; break; //99 scoring
      case 2: tarliftPos = 160; break; //72 highest
      case 3: tarliftPos = 146; break; //80 before latch 
      case 4: tarliftPos = 118; break; //111 hang
      case 5: tarliftPos = 97; break; //130 moving in auton
    }

    potDiff = tarliftPos - pot_liftValue;

    //pid for lift
    if(abs(potDiff) > potRange) {
      lift(potDiff*-15);
      if(abs(potDiff) < -10){
        lift(potDiff*-5);
      }
    }
    else {
      leftLift.stop(hold);
      rightLift.stop(hold);
    }
  }
  return(0);
}