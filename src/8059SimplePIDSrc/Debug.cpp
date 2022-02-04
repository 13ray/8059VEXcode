#include "vex.h"
int DEBUG_MODE = 7;

void printPosMaster(){
  Controller1.Screen.setCursor(3, 0);
  Controller1.Screen.print("%.2f %.2f %.2f", X, Y, bearing);
}
void printPosTerminal(){
  printf("x: %.2f y: %.2f bearing: %.2f\n", X, Y, bearing);
}
void printEncdTerminal(){
  printf("encdL: %.2f encdR: %.2f\n", rot_lbValue, rot_rbValue);
}
void printErrorTerminal(){
  printf("errorEncdL: %.2f errorEncdR: %.2f\n", errorEncdL, errorEncdR);
}
void printTargPowerTerminal(){
  printf("targPowerL: %.2f, targPowerR: %.2f\n", targPowerL, targPowerR);
}
void printPowerTerminal(){
  printf("powerL: %.2f powerR: %.2f\n", powerL, powerR);
}
void printLiftEncdTerminal(){
  printf("LiftencdL: %.2f LiftencdR: %.2f\n", liftEncdl, liftEncdr);
}

void printAllTerminal() {
  printf("x: %.2f y: %.2f bearing: %.2f\t", X, Y, bearing);
  printf("encdL: %.2f encdR: %.2f\n", rot_lbValue, rot_rbValue);
  printf("errorEncdL: %.2f errorEncdR: %.2f\t", errorEncdL, errorEncdR);
  printf("targPowerL: %.2f, targPowerR: %.2f\t", targPowerL, targPowerR);
  printf("powerL: %.2f powerR: %.2f\t", powerL, powerR);
  printf("curr angle: %.2f\n", bearing);
}
int Debug(){
  while(t){
    printf("x: %.2f y: %.2f bearing: %.2f\n", X, Y, bearing);
    printf("errorBearing: %.2f targBearing: %.2f\n", errorBearing, targBearing);
    wait(20, msec);
  }
  return 0;
}
