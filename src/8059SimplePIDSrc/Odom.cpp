#include "vex.h"

double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0;
const double inPerDeg = 0.0242;

void setCoords(double x, double y, double b){
  X = x;
  Y = y;
  bearing = b;
}

int Odometry(){
  while(true){
    if(imu.isCalibrating()){
      resetCoords(0, 0, 0);
    }else {
      double encdChangeL = rot_lbValue-prevEncdL;
      double encdChangeR = rot_rbValue-prevEncdR;

      double dist = (encdChangeL + encdChangeR)/2*inPerDeg;
      X += dist*cos(ang);
      Y += dist*sin(ang);
      /** update prev variables */
      prevEncdL = rot_lbValue;
      prevEncdR = rot_rbValue;
    }
    wait(5, msec);
  }
  return 0;
}
void resetPrevEncd() {
  prevEncdL = 0;
  prevEncdR = 0;
}

