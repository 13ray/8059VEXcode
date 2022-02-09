#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftFront = motor(PORT11, ratio18_1, f);
motor leftMid = motor(PORT3, ratio18_1, t);
motor leftBack = motor(PORT4, ratio18_1, f);
motor rightFront = motor(PORT20, ratio18_1, t);
motor rightMid = motor(PORT8, ratio18_1, f);
motor rightBack = motor(PORT6, ratio18_1, t);
motor_group leftBase = motor_group(leftFront, leftMid, leftBack);
motor_group rightBase = motor_group(rightFront, rightMid, rightBack);
motor leftLift = motor(PORT1, ratio36_1, f);
motor rightLift = motor(PORT10,ratio36_1, t);


digital_out twoBarL = digital_out(Brain.ThreeWirePort.A); 
digital_out twoBarR = digital_out(Brain.ThreeWirePort.B); 
digital_out frontMogo = digital_out(Brain.ThreeWirePort.H); 
digital_out latch = digital_out(Brain.ThreeWirePort.G); 

rotation rot_lb = rotation(PORT5, true);
rotation rot_rb = rotation(PORT7, false);
pot pot_lift = pot(Brain.ThreeWirePort.F);
inertial imu = inertial(PORT19);

timer Timer;
controller Controller1 = controller(primary);

//initialise
void vexcodeInit(){
  frontMOG(f);
  imu.calibrate();
  while(true) {
    if(imu.isCalibrating()) {
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print("IMU");
      wait(50, msec);
    }
    else break;
  }
  Controller1.Screen.clearScreen();

  rot_lb.resetPosition();
  rot_rb.resetPosition();
  resetCoords(0,0,0);
}