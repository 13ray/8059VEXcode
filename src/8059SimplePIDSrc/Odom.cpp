#include "vex.h"
const double inPerDeg = 0.01940277778;
const double baseWidth = 13.4;
double X = 0, Y = 0, prevEncdL = 0, prevEncdR = 0, prevAngle = 0;
double ang = 0, lastResetAngle = 0;
void setCoords(double x, double y, double a){
  X = x;
  Y = y;
  lastResetAngle = a*toRad;
  ang = a*toRad;
}
int Odometry(){
  while(true){
    double encdChangeL = (rot_lbValue-prevEncdL)*inPerDeg;
    double encdChangeR = (rot_rbValue-prevEncdR)*inPerDeg;
    ang = lastResetAngle + (rot_lbValue - rot_rbValue)*inPerDeg/baseWidth; //Theta = (s2-s1)/width
    double deltaAngle = ang - prevAngle;
    double sumEncdChange = encdChangeL + encdChangeR;

    if(deltaAngle == 0) //Cannot divide by 0
    {
			X += sumEncdChange/2*sin(ang);            	//Simple trigo
			Y += sumEncdChange/2*cos(ang);
		}
		else                //Refer to formulas
		{
			double halfDeltaAngle = deltaAngle/2;
			double strDist = (sumEncdChange/deltaAngle)*sin(halfDeltaAngle);
			X += strDist * sin(prevAngle+halfDeltaAngle);
			Y += strDist * cos(prevAngle+halfDeltaAngle);
		}
    /** update prev variables */
    prevEncdL = rot_lbValue;
    prevEncdR = rot_rbValue;
    prevAngle = ang;
  wait(5, msec);
  }
  return 0;
}
void resetPrevEncd() {
  prevEncdL = rot_lbValue;
  prevEncdR = rot_rbValue;
}
