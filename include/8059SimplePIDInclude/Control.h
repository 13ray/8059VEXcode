#ifndef _8059_SIMPLE_PID_CONTROL_HPP_
#define _8059_SIMPLE_PID_CONTROL_HPP_
extern double DEFAULT_KP, DEFAULT_KD, FMG_KP, FMG_KD, FMGS_KP, FMGS_KD, BMG_KP, BMG_KD, MGS_KP, MGS_KD;
extern double FMG_TURN_KP, FMG_TURN_KD, FMGS_TURN_KP, FMGS_TURN_KD, BMG_TURN_KP, BMG_TURN_KD, BMGFR_TURN_KP, BMGFR_TURN_KD, BMGFL_TURN_KP, BMGFL_TURN_KD, MGS_TURN_KP, MGS_TURN_KD;
extern double errorEncdL, errorEncdR, targEncdL, targEncdR, targPowerL, targPowerR, powerL, powerR, errorBearing, targBearing;
extern bool auton, pauseBase;
void baseMove(double dis, double kp, double kd);
void baseMove(double dis);
void baseTurn(double bearing, double kp, double kd);
void baseTurn(double bearing);
void powerBase(double l, double r);
void timerBase(double l, double r, double t);
void unPauseBase();
void waitBase(double cutoff);
extern int Control();
void resetCoords(double x, double y, double bearing);
void resetRot();

#endif