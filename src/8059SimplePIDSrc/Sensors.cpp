#include "vex.h"

int pot_liftValue = 0;
double rot_lbValue = 0, rot_rbValue = 0, bearing = 0, ang = halfPI, liftEncdl = 0, liftEncdr = 0;

int Sensors() {
  while(t) {
    if(!imu.isCalibrating()) {
      rot_lbValue = rot_lb.position(deg);
      rot_rbValue = rot_rb.position(deg);
      bearing = imu.heading(deg);
      ang = halfPI - bearing * toRad;
    }

    liftEncdl = leftLift.position(deg);
    liftEncdr = rightLift.position(deg);
    pot_liftValue = pot_lift.value(deg);
    wait(5,msec);
  }
  return(0);
}