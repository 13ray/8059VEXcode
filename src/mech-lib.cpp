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

//two bar pistons: true = down
void twoBar(bool s) {
  if(s){
    twoBarL.close();
    twoBarR.close();
  }else{
    twoBarL.open();
    twoBarR.open();    
  }
}

//front mogo
void frontMOG(bool s){
  if(s){
    frontMogo.close();
  }else{
    frontMogo.open();
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

//wait for lift to finish moving
void waitLift(){
  while(lifting){
  wait(5, msec);
  }
}

int Lift() {         //move to specific position 
  while(t) {
    switch(liftPos) {
      case 0: tarliftPos = 87; break; //139 lowest
      case 1: tarliftPos = 128; break; //99 scoring
      case 2: tarliftPos = 160; break; //72 highest
      case 3: tarliftPos = 146; break; //80 before latch 
      case 4: tarliftPos = 118; break; //111 hang
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