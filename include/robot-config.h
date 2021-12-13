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
extern motor lift;

extern digital_out twoBar;
extern digital_out frontMogo;
extern digital_out backMogo;
extern digital_out liftAssist;
extern digital_out pressure;
extern digital_out antiTip;

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