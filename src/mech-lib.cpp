#include "vex.h"
#include "math.h"

//values or thresholds
int liftPos = 0, prevliftPos = 0;
double tarliftPos = 139.5, potRange = 0.5;

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

void frontMOG(bool s){
  if(s){
    frontMogo.open();
  }else{
    frontMogo.close();
  }
}

//
void waitfrontMOG(int t, int waitForCompletion){
  frontMogo.open();
  wait(t,msec);
  if(waitForCompletion == 1){
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

//hang 
void hang(){
  if(liftPos == 2){
    liftPos += 1;
  }
  Latch(t);
  if(liftPos == 3){
    liftPos +=1;
  }
}


int Lift() {         //move to specific position 
  while(t) {
    switch(liftPos) {
      case 0: tarliftPos =139.5; break; //170
      case 1: tarliftPos = 99; break; //platform 
      case 2: tarliftPos = 72; break; //limit
      case 3: tarliftPos = 80; break; //before latch 
      case 4: tarliftPos = 111; break; //hang
    }

    double potDiff = tarliftPos - pot_liftValue;
    // printf("potDiff :%.2f\n", potDiff);
    // printf("tarliftPos :%.2f\n", tarliftPos);
    // printf("pot_liftValue :%d\n", pot_liftValue);
    // printf("\n");
    double kP= 10;
    double kD = 5;
    //printf("lift val:%d\n", pot_liftValue);

    if(absD(potDiff) > potRange) {
      lift(potDiff*kP);
      if(absD(potDiff) < 10){
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
  
