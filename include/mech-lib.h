#ifndef _MECH_LIB_H_
#define _MECH_LIB_H_

extern int liftPos;
extern double tarliftPos;
extern bool f, t;

//lift
void lift(int s);
void lift(int s, int t);
void liftRot(int rot);

//twoBar
void twoBar(bool s);

//frontMogo
void frontMOG(bool s);
void waitfrontMOG(int t, int waitForCompletion);

//Latch
void Latch(bool s);

//multi-action
int Lift();
void hang();

#endif