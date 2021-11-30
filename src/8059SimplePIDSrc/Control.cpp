#include "vex.h"

#define DEFAULT_KP 0.17
#define DEFAULT_KI 0
#define DEFAULT_KD 5
#define DEFAULT_TURN_KP 0.29
#define DEFAULT_TURN_KI 0
#define DEFAULT_TURN_KD 10
#define KI_LIMIT 0
#define RAMPING_POW 1
#define DISTANCE_LEEWAY 15
#define MAX_POW 100

double targEncdL = 0, targEncdR = 0;
double errorEncdL = 0, errorEncdR = 0;
double powerL = 0, powerR = 0;
double targPowerL = 0, targPowerR = 0;
double kP = DEFAULT_KP, kD = DEFAULT_KD, kI = DEFAULT_KI;

bool turnMode = f;

void baseMove(double dis, double kp, double ki, double kd){
  targEncdL = rot_lbValue;
  targEncdR = rot_rbValue;

  targEncdL += dis/inPerDeg;
  targEncdR += dis/inPerDeg;

  kP = kp;
  kI = ki;
  kD = kd;
}
void baseMove(double dis){
  baseMove(dis, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD);
}

void baseMove(double x, double y, double p, double i, double d){
	double errY = y-Y;
	double errX = x-X;
	double dis = sqrt(errY*errY + errX*errX);
	double targAngle = atan2(errX,errY);

	int negator = 1;
  if(fabs(targAngle-ang) >= PI/2) negator = -1;

  targEncdL += dis/inPerDeg*negator;
  targEncdR += dis/inPerDeg*negator;

  kP = p;
  kI = i;
  kD = d;
}

void baseMove(double x, double y){
  baseMove(x, y, DEFAULT_KP, DEFAULT_KI, DEFAULT_KD);
}

void baseTurn(double a, double kp, double ki, double kd){
  double error = a*toRad - ang;
  double diff = error*baseWidth/inPerDeg/2;

  targEncdL += diff;
  targEncdR += -diff;
	kP = kp;
  kI = ki;
	kD = kd;
}

void baseTurn(double a){
  baseTurn(a, DEFAULT_TURN_KP, DEFAULT_TURN_KI, DEFAULT_TURN_KD);
}

void powerBase(double l, double r) {
  powerL = l;
  powerR = r;
}

void timerBase(double l, double r, double t) {
  powerL = l;
  powerR = r;
  wait(t, msec);
  powerL = 0;
  powerR = 0;
}

void waitBase(double cutoff){
	double start = Timer.time();
  while((fabs(targEncdL - rot_lbValue) > DISTANCE_LEEWAY || fabs(targEncdR - rot_rbValue) > DISTANCE_LEEWAY) && (Timer.time()-start) < cutoff) wait(20, msec);
  printf("Time taken %.2f\n", (Timer.time() - start));
  wait(200, msec);
  // targEncdL = encdL;
  // targEncdR = encdR;
  resetPrevEncd();
}

void waitBaseNoD(double cutoff){
	double start = Timer.time();
  while((fabs(targEncdL - rot_lbValue) > DISTANCE_LEEWAY || fabs(targEncdR - rot_rbValue) > DISTANCE_LEEWAY) && (Timer.time()-start) < cutoff) wait(20, msec);
  printf("Time taken %.2f\n", (Timer.time() - start));
  // wait(200, msec);
  // targEncdL = encdL;
  // targEncdR = encdR;
  resetPrevEncd();
}

int Control(){
  double prevErrorEncdL = 0, prevErrorEncdR = 0, integralL = 0, integralR = 0;
  while(true){
    errorEncdL = targEncdL - rot_lbValue;
    errorEncdR = targEncdR - rot_rbValue;

    if(fabs(errorEncdL) < KI_LIMIT) integralL += errorEncdL;
    else integralL = 0;
    if(fabs(errorEncdR) < KI_LIMIT) integralR += errorEncdR;
    else integralR = 0;

    double deltaErrorEncdL = (errorEncdL - prevErrorEncdL);
    double deltaErrorEncdR = (errorEncdR - prevErrorEncdR);

    targPowerL = errorEncdL * kP + integralL * kI + deltaErrorEncdL * kD;
    targPowerR = errorEncdR * kP + integralR * kI + deltaErrorEncdR * kD;

    prevErrorEncdL = errorEncdL;
    prevErrorEncdR = errorEncdR;

    double deltaPowerL = targPowerL - powerL;
    powerL += abscap(deltaPowerL, RAMPING_POW);
    double deltaPowerR = targPowerR - powerR;
    powerR += abscap(deltaPowerR, RAMPING_POW);

    powerL = abscap(powerL, MAX_POW);
    powerR = abscap(powerR, MAX_POW);

    leftBase.spin(fwd, powerL, pct);
    rightBase.spin(fwd, powerR, pct);
  }
  return 0;
}

void resetCoords(double x, double y, double angleInDeg){
  leftBase.resetRotation();
  rightBase.resetRotation();

  rot_lb.resetPosition();
  rot_rb.resetPosition();
  resetPrevEncd();

  targEncdL = 0;
  targEncdR = 0;

  setCoords(x, y, angleInDeg);
}