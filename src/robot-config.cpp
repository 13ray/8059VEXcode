#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftFront = motor(PORT19, ratio18_1, f);
motor leftMid = motor(PORT12, ratio18_1, f);
motor leftBack = motor(PORT14, ratio18_1, f);
motor rightFront = motor(PORT10, ratio18_1, t);
motor rightMid = motor(PORT2, ratio18_1, t);
motor rightBack = motor(PORT4, ratio18_1, t);
motor_group leftBase = motor_group(leftFront, leftMid, leftBack);
motor_group rightBase = motor_group(rightFront, rightMid, rightBack);
motor conveyor = motor(PORT11, ratio6_1, false);
motor lift = motor(PORT9, ratio36_1, false);

digital_out leftBar = digital_out(Brain.ThreeWirePort.H);
digital_out rightBar = digital_out(Brain.ThreeWirePort.A);
digital_out leftMogo = digital_out(Brain.ThreeWirePort.G);
digital_out rightMogo = digital_out(Brain.ThreeWirePort.B);
digital_out backMogo = digital_out(Brain.ThreeWirePort.E);

rotation rot_lb = rotation(PORT13, false);
rotation rot_rb = rotation(PORT3, true);
pot pot_lift = pot(Brain.ThreeWirePort.C);
optical op_leftMogo = optical(PORT5);
optical op_rightMogo = optical(PORT6);
optical op_backMogo = optical(PORT7);
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

  op_leftMogo.objectDetectThreshold(op_threshold);
  op_rightMogo.objectDetectThreshold(op_threshold);
  op_backMogo.objectDetectThreshold(op_threshold);
}