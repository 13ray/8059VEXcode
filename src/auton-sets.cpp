#include "vex.h"
#include "auton-sets.h"

/* back mogo intake has piston
    if(Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing() && Controller1.ButtonR1.pressing()) {
      piston(*"tb");
    }

    //mogo intakes
    if(Controller1.ButtonR2.pressing() && Controller1.ButtonL2.pressing()) {
      if(TBState == t) {
        piston(*"bm", f);
      }
      else {
        Controller1.rumble("-");
      }
    }
    else if(Controller1.ButtonR2.pressing()) {
      piston(*"lm", t);
      piston(*"rm", t);
    }
    */