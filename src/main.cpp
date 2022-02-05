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
  int driveMode = 1, count = 0, pcount = 0;
  std::string drivePrint = "";
  int LBSpeed = 0, RBSpeed = 0;
  int liftStart = 0;
  bool twoBarTE = f, latchTE = f;
  bool L1Pressed = f, UPPressed = f;
  bool L1 = f, L2 = f, UP = f;
  
  // User control code here, inside the loop
  while (t) {
    
    /*if(Controller1.ButtonA.pressing()) auton = t;
    if(auton){
      // baseTurn(30,FMGS_TURN_KP,FMGS_TURN_KD);
      
      resetCoords(0,0,0);
      liftPos = 0;

      //right red
      baseMove(4, DEFAULT_KP, DEFAULT_KD); //intake mogo
      waitBase(1000);

      baseMove(-11, DEFAULT_KP, DEFAULT_KD); //reverse
      waitBase(1500);

      task liftTask(Lift);
      liftPos = 5;
      waitLift();

      //left neutral
      baseTurn(304, FMG_TURN_KP, FMG_TURN_KD); //face mogo
      waitBase(5000);
      
      baseMove(36, FMG_KP, FMG_KD); //go to mogo
      waitBase(9000);

      liftPos = 0;
      baseMove(12.8, FMG_KP, FMG_KD); //intake mogo
      waitBase(3000);
      resetRot();

      //clearing rings
      liftPos = 2;
      baseMove(31,FMGS_KP, FMGS_KD);
      waitBase(9000);
      resetRot();

      baseTurn(18, FMGS_TURN_KP, FMGS_TURN_KD);
      waitBase(5000);
      auton = f;
    }*/

    L1 = Controller1.ButtonL1.pressing();
    L2 = Controller1.ButtonL2.pressing();
    UP = Controller1.ButtonUp.pressing();
    count += 1;

    //drivemode
    if(Controller1.ButtonY.pressing()) driveMode += 1, Controller1.Screen.clearLine(3);
    if(driveMode%3 == 1) { //reverse arcade
      LBSpeed = Controller1.Axis2.position() + Controller1.Axis4.position();
      RBSpeed = Controller1.Axis2.position() - Controller1.Axis4.position();
      drivePrint = "R Arcade";
    }
    else if(driveMode%3 == 2) { //normal arcade
      LBSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      RBSpeed = Controller1.Axis3.position() - Controller1.Axis1.position(); 
      drivePrint = "Arcade";
    }
    else { //tank
      LBSpeed = Controller1.Axis3.position();
      RBSpeed = Controller1.Axis2.position();
      drivePrint = "Tank";
    }

    leftBase.spin(fwd, LBSpeed, pct);
    rightBase.spin(fwd, RBSpeed, pct);
    
    //2 bar
    if(L1 && !L1Pressed){
      L1Pressed = t;
      twoBarTE = !twoBarTE; //switch 2b state
    }
    else if(!L1) {
      L1Pressed = f;
    }
    twoBar(!twoBarTE); //actuate 2b state

    //frontMogo
    if(L2){
      if(liftPos == 0){
        pcount = count;
      }
      frontMOG(t); //open
    }
    if((count-pcount) == 6 && pcount != 0) frontMOG(f); //close after controller loop runs 10 times

    //Latch
    if(UP && !UPPressed){
      UPPressed = t;
      latchTE = !latchTE; //switch latch state
    }
    else if(!UP) UPPressed = false;

    if(latchTE){ //actuate latch state
      hang();
    }

    //Lift
    if(Controller1.ButtonR1.pressing()){ //move up
      liftStart += 1;
      Controller1.Screen.clearLine(2);
      if(liftPos < 2){
        liftPos +=1;
      }
      else if(liftPos == 2){
        Controller1.rumble("-");
      }
    }
    if(Controller1.ButtonR2.pressing()){ //move down
      Controller1.Screen.clearLine(2);
      if(liftPos > 0){
        liftPos -= 1;
        if(liftPos == 0){ //close front mogo when 
          frontMOG(f);
        }
      }
      else if(liftPos == 0){
        Controller1.rumble("-");
      }
    } 

    if(liftStart == 1){
      task liftTask(Lift);
    }

    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Two Bar = %d", twoBarL.value());
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Lift Pos = %d, %d", liftPos, imu.isCalibrating());
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(drivePrint.c_str());
    Controller1.Screen.clearLine(1);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  task controlTask(Control);
  task sensorTask(Sensors);
  task odomTask(Odometry);
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


