#ifndef _MECH_LIB_H_
#define _MECH_LIB_H_

extern int liftPos;
extern double tarliftPos;
extern bool f, t;

void lift(int s);
void lift(int s, int t);
void liftRot(int rot);
void twoBar(bool s);
void frontMOG(bool s);
void waitfrontMOG(float t, int waitForCompletion);
void Latch(bool s);
//void Hang(bool s);

int Lift();

#endif