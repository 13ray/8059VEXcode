#ifndef _MECH_LIB_H_
#define _MECH_LIB_H_

extern int op_threshold, liftPos, tarliftPos;
extern bool LMState, RMState, BMState, TBState;
extern bool f, t;

void con(int c);
void con(int c, int t);
void twoBar(bool s);
void piston(char p);
void piston(char p, bool s);

int Lift();
int FrontMogos();

#endif