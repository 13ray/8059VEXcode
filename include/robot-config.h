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

extern digital_out leftBar;
extern digital_out rightBar;
extern digital_out leftMogo;
extern digital_out rightMogo;
extern digital_out backMogo;

extern rotation rot_lb;
extern rotation rot_rb;
extern pot pot_lift;
extern optical op_leftMogo;
extern optical op_rightMogo;
extern optical op_backMogo;
extern inertial imu;

extern task STask;
extern task PSTask;
extern task POTask;

extern timer Timer;
extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );