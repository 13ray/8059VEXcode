using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor leftFront;
extern motor leftMid;
extern motor leftBack;
extern motor rightFront;
extern motor rightMid;
extern motor rightBack;
extern motor_group leftBase;
extern motor_group rightBase;
extern motor conveyor;
extern motor leftLift;
extern motor rightLift;

extern digital_out twoBarL;
extern digital_out twoBarR;
extern digital_out frontMogo;
extern digital_out backMogo;
extern digital_out liftAssistL;
extern digital_out liftAssistR;

extern rotation rot_lb;
extern rotation rot_rb;
extern pot pot_lift;
//extern inertial imu;

extern timer Timer;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );