#include "vex.h"
double boundRad(double rad){
  double res = fmod(rad, twoPI);
  if(res < 0) res += twoPI;
  return res;
}
double boundDeg(double deg){
  double res = fmod(deg, 360);
  if(res < 0) res += 360;
  return res;
}
double abscap(double x, double abscap){
  if(x > abscap) return abscap;
  else if(x < -abscap) return -abscap;
  else return x;
}

double absD(double q){
  if(q>0) return q;
  else if(q<0) return -q;
  else return 0;
}

double max(double a, double b) {
  if(a>b) return a;
  else return b;
}

int sign(double x){
  if(fabs(x) <= 1/1e9) return 0;
  else if(x > 0) return 1;
  else return -1;
}