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
  auton = t;
  resetCoords(0,0,0);


  // baseMove(24);
  // waitBase(2000);
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
  auton = f;
  bool auton2 = f;
  int driveMode = 1, count = 0, pcount = 0;
  int LBSpeed = 0, RBSpeed = 0;
  int liftStart = 0;
  bool L1Pressed = f, R1Pressed = f, R2Pressed = f, L2Pressed = f, UPPressed = f, YPressed = f;
  bool twoBarState = f;
  
  // User control code here, inside the loop
  while (t) {
    //auton 1
    if(Controller1.ButtonA.pressing()) auton = t;
    if(auton){
      skills();
      auton = f;
    }

    //auton 2
    if(Controller1.ButtonB.pressing()) auton2 = t;
    if(auton2){
      test();
      auton2 = f;
    }
    count += 1;
    
    //drivemode
    if(Controller1.ButtonY.pressing() && !YPressed){
      YPressed = t;
      driveMode += 1;
    }
    else if(!Controller1.ButtonY.pressing()) YPressed = f;

    if(driveMode%3 == 1) { //reverse arcade
      LBSpeed = Controller1.Axis2.position() + Controller1.Axis4.position();
      RBSpeed = Controller1.Axis2.position() - Controller1.Axis4.position();
    }
    else if(driveMode%3 == 2) { //normal arcade
      LBSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      RBSpeed = Controller1.Axis3.position() - Controller1.Axis1.position(); 
    }
    else { //tank
      LBSpeed = Controller1.Axis3.position();
      RBSpeed = Controller1.Axis2.position();
    }

    leftBase.spin(fwd, LBSpeed, pct);
    rightBase.spin(fwd, RBSpeed, pct);
    
    //2 bar
    if(Controller1.ButtonL1.pressing() && !L1Pressed){
      L1Pressed = t;
      twoBarState = !twoBarState; //switch 2b state
    }
    else if(!Controller1.ButtonL1.pressing()) L1Pressed = f;

    twoBar(twoBarState); //actuate 2b

    //frontMogo
    if(Controller1.ButtonL2.pressing() && !L2Pressed){
      L2Pressed = t;
      if(liftPos == 0){
        pcount = count;
      }
      frontMOG(t); //open
    }
    else if(!Controller1.ButtonL2.pressing()) L2Pressed = f;

    if((count-pcount) == 8 && pcount != 0) frontMOG(f); //close after controller loop runs 8 times

    //Latch
    if(Controller1.ButtonUp.pressing() && !UPPressed){
      UPPressed = t;
      hang();
    }
    else if(!Controller1.ButtonUp.pressing()) UPPressed = false;

    //Lift
    if(Controller1.ButtonR1.pressing() && !R1Pressed){ //move up
      R1Pressed = t;
      liftStart += 1;
      Controller1.Screen.clearLine(2);
      if(liftPos < 2){
        liftPos +=1;
      }
      else if(liftPos == 2){
        Controller1.rumble("-");
      }
    }
    else if(!Controller1.ButtonR1.pressing()) R1Pressed = f;

    if(Controller1.ButtonR2.pressing() && !R2Pressed){ //move down
      R2Pressed = t;
      Controller1.Screen.clearLine(2);
      if(liftPos > 0){
        liftPos -= 1;
        if(liftPos == 0){ //close front mogo
          frontMOG(f);
        }
      }
      else if(liftPos == 0){
        Controller1.rumble("-");
      }
    } 
    else if(!Controller1.ButtonR2.pressing()) R2Pressed = f;

    if(liftStart == 1){
      task liftTask(Lift);
    }
    wait(10, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // task controlTask(Control);
  task sensorTask(Sensors);
  // task odomTask(Odometry);
  // task debugTask(Debug);
  // task liftTask(Lift);

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(5, msec);
  }
}


