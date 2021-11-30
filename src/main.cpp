/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {

  int driveMode = 1;
  double slowSpeed = 0.5;
  bool slowBase = f;

  int LBSpeed = 0;
  int RBSpeed = 0;

  // User control code here, inside the loop
  while (t) {
    if(Controller1.ButtonY.pressing()) {
      driveMode += 1;
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print("Drive Mode = %d", driveMode);
    }

    if(driveMode%3 == 1) { //reverse arcade
      LBSpeed = Controller1.Axis2.position() + Controller1.Axis4.position();
      RBSpeed = Controller1.Axis2.position() - Controller1.Axis4.position();
    }
    else if(driveMode%3 == 2) { //normal arcade
      LBSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      RBSpeed = Controller1.Axis3.position() - Controller1.Axis1.position(); 
    }
    else {
      LBSpeed = Controller1.Axis3.position();
      RBSpeed = Controller1.Axis2.position();
    }

    if(Controller1.ButtonUp.pressing()) {
      slowBase = !slowBase;
    }

    if(slowBase) {
      if(LBSpeed == 0 && RBSpeed == 0) {
        leftBase.stop(hold);
        rightBase.stop(hold);
      }
      else {
        leftBase.spin(fwd, LBSpeed*slowSpeed, pct);
        rightBase.spin(fwd, RBSpeed*slowSpeed, pct);
      }
    }
    else {
      leftBase.spin(fwd, LBSpeed, pct);
      rightBase.spin(fwd, RBSpeed, pct);
    }
    
    //2 bar
    if(Controller1.ButtonR2.pressing() && Controller1.ButtonL2.pressing()) {
      piston(*"tb");
    }

    //mogo intakes
    if(Controller1.ButtonR2.pressing()) {
      piston(*"lm", t);
      piston(*"rm", t);
    }
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

    //lift
    if(Controller1.ButtonR1.pressing() && Controller1.ButtonL2.pressing()) {
      if(liftPos == 1) {
        Controller1.rumble("-");
      }
      else {
        liftPos -= 1;
      }
    } 
    else if(Controller1.ButtonR1.pressing()) {
      if(liftPos == 3) {
        Controller1.rumble("-");
      }
      else {
        liftPos += 1;
      }
    }

    //conveyor
    if(liftPos != 1) {
      if(Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing()) {
        con(100);
      }
      else if(Controller1.ButtonL1.pressing()) {
        con(-100);
      }
      else {
        conveyor.stop();
      }
    }

    if(imu.isCalibrating()) {
      Controller1.Screen.setCursor(1,1);
      Controller1.Screen.print("Calibrating IMU");
    }
    else {
      Controller1.Screen.setCursor(1, 1);
      Controller1.Screen.print("%.2f %.2f %.2f", X, Y, ang * toDeg);
      Controller1.Screen.setCursor(2, 1);
      Controller1.Screen.print("Lift Pos = %d, %d, %d", liftPos, pot_liftValue, tarliftPos);
      Controller1.Screen.setCursor(3, 1);
      Controller1.Screen.print("Drive Mode = %d", driveMode%3);
    }
    
    
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  task controlTask(Control);
  task sensorTask(Sensors);
  task odomTask(Odometry);
  task debugTask(Debug);
  task liftTask(Lift);

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}