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
motor rightBack = motor(PORT7, ratio18_1, t);
motor_group leftBase = motor_group(leftFront, leftMid, leftBack);
motor_group rightBase = motor_group(rightFront, rightMid, rightBack);
motor leftLift = motor(PORT1, ratio36_1, f);
motor rightLift = motor(PORT10,ratio36_1, t);


pneumatics twoBarL = pneumatics(Brain.ThreeWirePort.A); 
pneumatics twoBarR = pneumatics(Brain.ThreeWirePort.B); 
pneumatics frontMogo = pneumatics(Brain.ThreeWirePort.H); 
pneumatics latch = pneumatics(Brain.ThreeWirePort.G); 

rotation rot_lb = rotation(PORT5, false);
rotation rot_rb = rotation(PORT6, true);
pot pot_lift = pot(Brain.ThreeWirePort.F);
inertial imu = inertial(PORT20);

timer Timer;
controller Controller1 = controller(primary);

//initialise
void vexcodeInit(){
  imu.calibrate();
  if(imu.isCalibrating()) {wait(20, msec);}
  else{resetCoords(0,0,0);}
  frontMogo.close(); //down
  twoBar(f); //down
  Latch(f);
  Controller1.Screen.clearScreen();
}