#ifndef _MECH_LIB_H_
#define _MECH_LIB_H_

extern int liftPos, tarliftPos, potDiff;
extern bool f, t, lifting;

void lift(int s);
void lift(int s, int t);
void liftRot(int rot);
void twoBar(bool s);
void frontMOG(bool s);
void Latch(bool s);
void hang();
void waitLift();

int Lift();


#endif