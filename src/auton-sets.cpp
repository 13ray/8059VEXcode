#include "vex.h"
#include "auton-sets.h"

#include "8059SimplePIDInclude/Control.h"
#include "mech-lib.h"

void tuningPID(){
  mogoFB(f);
  lift(100,500);
  baseMove(10, 0.0012, 0);
}