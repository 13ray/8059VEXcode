#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftFront = motor(PORT18, ratio18_1, f);
motor leftMid = motor(PORT19, ratio18_1, t);
motor leftBack = motor(PORT17, ratio18_1, f);
motor rightFront = motor(PORT8, ratio18_1, t);
motor rightMid = motor(PORT9, ratio18_1, f);
motor rightBack = motor(PORT7, ratio18_1, t);
motor_group leftBase = motor_group(leftFront, leftMid, leftBack);
motor_group rightBase = motor_group(rightFront, rightMid, rightBack);
motor conveyor = motor(PORT6, ratio6_1, false);
motor lift = motor(PORT16, ratio36_1, false);

digital_out twoBar = digital_out(Brain.ThreeWirePort.A);
digital_out frontMogo = digital_out(Brain.ThreeWirePort.B);
digital_out backMogo = digital_out(Brain.ThreeWirePort.C);
digital_out liftAssist = digital_out(Brain.ThreeWirePort.D);

rotation rot_lb = rotation(PORT20, false);
rotation rot_rb = rotation(PORT10, true);
pot pot_lift = pot(Brain.ThreeWirePort.G);
inertial imu = inertial(PORT8);

timer Timer;
controller Controller1 = controller(primary);
int hi = 0;

//initialise
void vexcodeInit(){
  Controller1.Screen.clearScreen();
  /*imu.calibrate();
  while(imu.isCalibrating()) {
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Calibrating IMU");
    wait(20, msec);
  }
  Controller1.Screen.clearLine(1);*/
  rot_lb.resetPosition();
  rot_rb.resetPosition();

}