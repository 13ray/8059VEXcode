#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftFront = motor(PORT3, ratio18_1, f);
motor leftMid = motor(PORT1, ratio18_1, t);
motor leftBack = motor(PORT2, ratio18_1, f);
motor rightFront = motor(PORT8, ratio18_1, t);
motor rightMid = motor(PORT10, ratio18_1, f);
motor rightBack = motor(PORT9, ratio18_1, t);
motor_group leftBase = motor_group(leftFront, leftMid, leftBack);
motor_group rightBase = motor_group(rightFront, rightMid, rightBack);
motor conveyor = motor(PORT6, ratio6_1, t);
motor lift = motor(PORT5, ratio36_1, t);

digital_out twoBarL = digital_out(Brain.ThreeWirePort.B);
digital_out twoBarR = digital_out(Brain.ThreeWirePort.D);
digital_out frontMogo = digital_out(Brain.ThreeWirePort.G);
digital_out backMogo = digital_out(Brain.ThreeWirePort.C);
digital_out liftAssistL = digital_out(Brain.ThreeWirePort.E);
digital_out liftAssistR = digital_out(Brain.ThreeWirePort.F);

rotation rot_lb = rotation(PORT4, false);
rotation rot_rb = rotation(PORT7, true);
pot pot_lift = pot(Brain.ThreeWirePort.H);
inertial imu = inertial(PORT20);

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
  frontMogo.set(t);
  twoBar(t);
  rot_lb.resetPosition();
  rot_rb.resetPosition();

}