#include "vex.h"
int DEBUG_MODE = 6;

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
  printf("errorEncdL: %.2f errorEncdR: %.2f\t", errorEncdL, errorEncdR);
  printf("targPowerL: %.2f, targPowerR: %.2f\t", targPowerL, targPowerR);
  printf("powerL: %.2f powerR: %.2f\t", powerL, powerR);
  printf("curr angle: %.2f\n", bearing);
  printf("LiftencdL: %.2f LiftencdR: %.2f\n", liftEncdl, liftEncdr);
}
int Debug(){
  while(true){
    printPosMaster();
    if(imu.isCalibrating()) {
      printf("imu is calibrating...\n");
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Calibrating IMU");
    }else {
      Brain.Screen.clearScreen();
      switch(DEBUG_MODE){
        case 1: printPosTerminal(); break;
        case 2: printEncdTerminal(); break;
        case 3: printErrorTerminal(); break;
        case 4: printTargPowerTerminal(); break;
        case 5: printPowerTerminal(); break;
        case 6: printLiftEncdTerminal(); break;
        case 7: printAllTerminal(); break;
      }
    //}
    wait(50, msec);
  }
  return 0;
}
}
