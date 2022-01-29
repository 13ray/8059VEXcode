#include "vex.h"
#include "8059SimplePIDInclude/Control.h"
#include "auton-sets.h"

void tuning() {
  baseMove(24, 0.27, 0.2);//default pid 
  waitBase(2000);
}