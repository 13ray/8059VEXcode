#include "vex.h"

#define DEFAULT_KP 0.0012
#define DEFAULT_KD 0
#define DEFAULT_TURN_KP 0.95
#define DEFAULT_TURN_KD 0
#define RAMPING_POW 2.5
#define DISTANCE_LEEWAY 2000
#define BEARING_LEEWAY 1

const double MAX_POW = 100;
double targEncdL = 0, targEncdR = 0, targBearing = 0;
double errorEncdL = 0, errorEncdR = 0, errorBearing = 0;
double prevErrorEncdL = 0, prevErrorEncdR = 0, prevErrorBearing = 0;
double powerL = 0, powerR = 0;
double targPowerL = 0, targPowerR = 0;
double kP = DEFAULT_KP, kD = DEFAULT_KD;
bool turnMode = false, pauseBase = false, auton = f;
bool baseBraking = false;
bool movementEnded = false;
void baseMove(double dis, double kp, double kd){
  pauseBase = false;
  movementEnded = false;
  printf("baseMove: %.1f\t", dis);
  turnMode = false;
  targEncdL = rot_lbValue + dis/inPerDeg;
  targEncdR = rot_rbValue + dis/inPerDeg;

  kP = kp;
  kD = kd;
}
void baseMove(double dis){
  baseMove(dis, DEFAULT_KP, DEFAULT_KD);
}
void baseTurn(double b, double kp, double kd){
  pauseBase = false;
  movementEnded = false;
  printf("baseTurn: %.1f\t", b);
  targBearing = bearing + boundDegTurn(b - bearing);
  printf("targBearing: %.1f\n", targBearing);
  turnMode = true;
	kP = kp;
	kD = kd;
}
void baseTurn(double b){
  baseTurn(b, DEFAULT_TURN_KP, DEFAULT_TURN_KD);
}
void powerBase(double l, double r) {
  pauseBase = true;
  movementEnded = false;
  powerL = l;
  powerR = r;
}
void timerBase(double l, double r, double t) {
  pauseBase = true;
  movementEnded = false;
  powerL = l;
  powerR = r;
  wait(t, msec);
  powerL = 0;
  powerR = 0;
  // pauseBase = false;
  movementEnded = true;
  wait(15, msec);
  pauseBase = false;
}
void unPauseBase() {
  powerL = 0;
  powerR = 0;
  pauseBase = false;
}

void waitBase(double cutoff){
	double start = Timer.time();
  if(turnMode) {
    while(fabs(targBearing - bearing) > BEARING_LEEWAY && (Timer.time()-start) < cutoff) wait(5, msec);
  }else{
    while((fabs(targEncdL - rot_lbValue) > DISTANCE_LEEWAY || fabs(targEncdR - rot_rbValue) > DISTANCE_LEEWAY) && (Timer.time()-start) < cutoff) wait(5, msec);
  }

  targEncdL = rot_lbValue;
  targEncdR = rot_rbValue;

  pauseBase = true;
  movementEnded = true;
}

int Control(){
  prevErrorEncdL = 0, prevErrorEncdR = 0, prevErrorBearing = 0;
  while(auton){
    if(!pauseBase) {
      if(turnMode){
        errorBearing = targBearing - bearing;
        double deltaErrorBearing = errorBearing - prevErrorBearing;

        targPowerL = errorBearing * kP + deltaErrorBearing * kD;
        targPowerR = -targPowerL;
        prevErrorBearing = errorBearing;

        double deltaPowerL = targPowerL - powerL;
        powerL += abscap(deltaPowerL, RAMPING_POW);
        double deltaPowerR = targPowerR - powerR;
        powerR += abscap(deltaPowerR, RAMPING_POW);

        powerL = abscap(powerL, MAX_POW);
        powerR = abscap(powerR, MAX_POW);

        // misc
        targEncdL = rot_lbValue;
        targEncdR = rot_rbValue;
      }else{
        errorEncdL = targEncdL - rot_lbValue;
        errorEncdR = targEncdR - rot_rbValue;
        double deltaErrorEncdL = errorEncdL - prevErrorEncdL;
        double deltaErrorEncdR = errorEncdR - prevErrorEncdR;

        double pd_targPowerL = errorEncdL * kP + deltaErrorEncdL * kD;
        double pd_targPowerR = errorEncdR * kP + deltaErrorEncdR * kD;
        double pd_maxTargPower = std::max(fabs(pd_targPowerL), fabs(pd_targPowerR));

        double setPower = std::min(pd_maxTargPower, MAX_POW);
        double lToR = ((pd_targPowerR != 0)? (pd_targPowerL/pd_targPowerR) : 1);
        if(lToR != 0){
            if(fabs(lToR)>=1){
              targPowerL = setPower*sign(pd_targPowerL);
              targPowerR = setPower*sign(pd_targPowerR)/fabs(lToR);
            } else{
              targPowerL = setPower*sign(pd_targPowerL)*fabs(lToR);
              targPowerR = setPower*sign(pd_targPowerR);
          }
        }
        double deltaPowerL = targPowerL - powerL;
        double deltaPowerR = targPowerR - powerR;

        deltaPowerL = abscap(deltaPowerL, RAMPING_POW);
        deltaPowerR = abscap(deltaPowerR, RAMPING_POW);

        powerL += deltaPowerL;
        powerR += deltaPowerR;

        // manual base compensation factor
        double mod = 1; //>1 to make left faster, <1 to make right faster
        if(mod >= 1) powerR /= mod;
        else powerL *= mod;
        prevErrorEncdL = errorEncdL;
        prevErrorEncdR = errorEncdR;
      }
    }else if(movementEnded){
      targEncdL = rot_lbValue;
      targEncdR = rot_rbValue;
      targBearing = bearing;
      errorEncdL = 0;
      errorEncdR = 0;
      errorBearing = 0;
      targPowerL = 0;
      targPowerR = 0;
      powerL = 0;
      powerR = 0;
      prevErrorEncdL = 0;
      prevErrorEncdR = 0;
      // printf("%.1f %.1f %.1f %.1f %.1f %.1f \n",targEncdL, errorEncdL, errorBearing, targPowerL, powerL, prevErrorEncdL);
    }
    leftBase.spin(fwd, powerL, pct);
    rightBase.spin(fwd, powerR, pct);
    wait(5, msec);
  }
  return 0;
}

void resetCoords(double x, double y, double angleInDeg){
  resetPrevEncd();

  targBearing = bearing;
  targEncdL = 0;
  targEncdR = 0;

  setCoords(x, y, angleInDeg);
}

/*
#define DEFAULT_KP 0.27
#define DEFAULT_KD 0.2
#define DEFAULT_TURN_KP 1.2 // 20 degrees = 2.5, 180 degrees = 1
#define DEFAULT_TURN_KD 0.6
#define RAMPING_POW 1.2
#define DISTANCE_LEEWAY 15
#define BEARING_LEEWAY 1.5
#define MAX_POW 100

double targEncdL = 0, targEncdR = 0, targBearing = 0;
double errorEncdL = 0, errorEncdR = 0, errorBearing = 0;
double powerL = 0, powerR = 0;
double targPowerL = 0, targPowerR = 0;
double kP = DEFAULT_KP, kD = DEFAULT_KD;

bool turnMode = false, pauseBase = false, auton = f;

void baseMove(double dis, double kp, double kd){
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
  baseTurn(bearing, DEFAULT_TURN_KP, DEFAULT_TURN_KD);
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

  targEncdL = rot_lbValue;
  targEncdR = rot_rbValue;
}

int Control(){
  double prevErrorEncdL = 0, prevErrorEncdR = 0, prevErrorBearing = 0;
  while(auton) {
    if(!imu.isCalibrating() && !pauseBase) {
      if(turnMode) {
        errorBearing = targBearing - bearing;
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

void resetCoords(double x, double y, double angleInDeg){
  resetPrevEncd();

  targBearing = bearing;
  targEncdL = 0;
  targEncdR = 0;

  setCoords(x, y, angleInDeg);
}
*/