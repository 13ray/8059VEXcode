#include "vex.h"

double DEFAULT_KP = 0.163, DEFAULT_KD = 5.5; //no mogos on robot
double FMG_KP = 0.14, FMG_KD = 1.5; //1 mogo in front
double FMGS_KP = 0.13, FMGS_KD = 3; //2 mogos in front
double BMG_KP = 0.14, BMG_KD = 0.5; //back mogo only / back mogo and 1 front
double MGS_KP = 0.13, MGS_KD = 0.3;//all 3 mogos
double FMG_TURN_KP = 1.1, FMG_TURN_KD = 0.2; //1 mogo front right 
double FMGS_TURN_KP = 1.2, FMGS_TURN_KD = 0.5; //2 mogos in front
double BMG_TURN_KP = 0.75, BMG_TURN_KD = 0; //back mogo only 
double BMGFR_TURN_KP = 0.74, BMGFR_TURN_KD = 0.4; //back mogo and front right
double BMGFL_TURN_KP = 0.84, BMGFL_TURN_KD = 0.7; //back mogo and front left
double MGS_TURN_KP = 0.8, MGS_TURN_KD = 0.5; //all 3 mogos

#define RAMPING_POW 1
#define DISTANCE_LEEWAY 15
#define BEARING_LEEWAY 1
#define MAX_POW 100

double targEncdL = 0, targEncdR = 0, targBearing = 0;
double errorEncdL = 0, errorEncdR = 0, errorBearing = 0;
double powerL = 0, powerR = 0;
double targPowerL = 0, targPowerR = 0;
double kP = DEFAULT_KP, kD = DEFAULT_KD;

bool turnMode = false, pauseBase = false, auton = f;

void baseMove(double dis, double kp, double kd){
  targEncdL = rot_lbValue;
  targEncdR = rot_rbValue;
  turnMode = false;

  targEncdL += dis/inPerDeg;
  targEncdR += dis/inPerDeg;

  kP = kp;
  kD = kd;
}
void baseMove(double dis){
  baseMove(dis, DEFAULT_KP, DEFAULT_KD);
}

void baseTurn(double p_bearing, double kp, double kd){
  turnMode = true;
  targBearing = p_bearing;
	kP = kp;
	kD = kd;
}
void baseTurn(double bearing){
  baseTurn(bearing, FMG_TURN_KD, FMG_TURN_KD);
}

void powerBase(double l, double r) {
  pauseBase = true;
  powerL = l;
  powerR = r;
}

void timerBase(double l, double r, double t) {
  pauseBase = true;
  powerL = l;
  powerR = r;
  wait(t, msec);
  powerL = 0;
  powerR = 0;
  pauseBase = false;
  resetCoords(X, Y, bearing);
}

void unPauseBase() {
  powerL = 0;
  powerR = 0;
  pauseBase = false;
  resetCoords(X, Y, bearing);
}

void waitBase(double cutoff){
	double start = Timer.time();
  if(turnMode) {
    while(fabs(targBearing - bearing) > BEARING_LEEWAY && (Timer.time()-start) < cutoff) wait(20, msec);
  }else{
    while((fabs(targEncdL - rot_lbValue) > DISTANCE_LEEWAY || fabs(targEncdR - rot_rbValue) > DISTANCE_LEEWAY) && (Timer.time()-start) < cutoff) wait(20, msec);
  }
  printf("time taken, %.f \n", start);
  targBearing = bearing;
  targEncdL = rot_lbValue;
  targEncdR = rot_rbValue;
}

int Control(){
  double prevErrorEncdL = 0, prevErrorEncdR = 0, prevErrorBearing = 0;
  while(t) {
    if(!imu.isCalibrating() && !pauseBase) {
      if(turnMode) {
        errorBearing = targBearing - bearing;
        if(absD(errorBearing) > 180) errorBearing = -(errorBearing-180);
        double deltaErrorBearing = errorBearing - prevErrorBearing;

        targPowerL = errorBearing * kP + deltaErrorBearing * kD;
        targPowerR = -targPowerL;

        prevErrorBearing = errorBearing;
      }
      else {
        errorEncdL = targEncdL - rot_lbValue;
        errorEncdR = targEncdR - rot_rbValue;

        double deltaErrorEncdL = errorEncdL - prevErrorEncdL;
        double deltaErrorEncdR = errorEncdR - prevErrorEncdR;

        targPowerL = errorEncdL * kP + deltaErrorEncdL * kD;
        targPowerR = errorEncdR * kP + deltaErrorEncdR * kD;

        prevErrorEncdL = errorEncdL;
        prevErrorEncdR = errorEncdR;
      }

      double deltaPowerL = targPowerL - powerL;
      powerL += abscap(deltaPowerL, RAMPING_POW);
      double deltaPowerR = targPowerR - powerR;
      powerR += abscap(deltaPowerR, RAMPING_POW);

      powerL = abscap(powerL, MAX_POW);
      powerR = abscap(powerR, MAX_POW);
    }
    leftBase.spin(fwd, powerL, pct);
    rightBase.spin(fwd, powerR, pct);
    wait(5, msec);
  }
  return 0;
}

void resetRot(){
  rot_lb.resetPosition();
  rot_rb.resetPosition();
  targEncdL = 0;
  targEncdR = 0;
  errorEncdL = 0;
  errorEncdR = 0;
  resetPrevEncd();

  wait(100, msec);
}

void resetCoords(double x, double y, double angleInDeg){
  resetPrevEncd();

  targBearing = bearing;
  targEncdL = 0;
  targEncdR = 0;

  setCoords(x, y, angleInDeg);
}