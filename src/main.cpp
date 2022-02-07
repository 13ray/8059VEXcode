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
  std::string drivePrint = "";
  int LBSpeed = 0, RBSpeed = 0;
  int liftStart = 0;
  bool L1Pressed = f, R1Pressed = f, R2Pressed = f, L2Pressed = f, UPPressed = f, twoBarTE = f;
  
  // User control code here, inside the loop
  while (t) {
    
    if(Controller1.ButtonA.pressing()) auton = t;
    if(auton){
      // baseTurn(30,FMGS_TURN_KP,FMGS_TURN_KD);
      task controlTask(Control);
      task odomTask(Odometry);
      resetCoords(0,0,0);

      //right red mogo
      baseMove(4, DEFAULT_KP, DEFAULT_KD); //intake right red
      waitBase(800);

      task liftTask(Lift);
      liftPos = 5;
      waitLift();

      baseMove(-14, DEFAULT_KP, DEFAULT_KD); //reverse
      waitBase(800);

      //right neutral mogo
      baseTurn(309, FMG_TURN_KP, FMG_TURN_KD); //face mogo
      waitBase(6000);
      
      baseMove(36, FMG_KP, FMG_KD); //go to mogo
      waitBase(8000);

      liftPos = 0;
      waitLift();
      baseMove(14, FMG_KP-0.03, FMG_KD); //intake right neutral
      waitBase(5000);
      resetRot();

      //scoring neutral and red mogos
      liftPos = 2;
      wait(500, msec);
      baseMove(60, FMGS_KP, FMGS_KD); //33 original
      waitBase(25000);
      resetRot();

      liftPos = 1;
      waitLift();
      frontMOG(t); //score
      wait(150, msec);

      //tall neutral mogo
      baseMove(-21, DEFAULT_KP, DEFAULT_KD); //move away from platform
      waitBase(8000);

      liftPos = 0;
      frontMOG(f);
      baseTurn(245, 1, 0); //face mogo
      waitBase(5000);

      baseMove(-23, DEFAULT_KP-0.06, DEFAULT_KD); //intake mogo
      waitBase(10000);
      twoBar(t);
      resetRot();

      //left red mogo
      baseMove(-47, BMG_KP, BMG_KD);
      waitBase(15000);
      resetRot();
      wait(500, msec);

      baseTurn(16, BMG_TURN_KP, BMG_TURN_KD); //face mogo
      waitBase(5000);
      resetRot();
      wait(500, msec);
      
      baseMove(18, BMG_KP-0.03, 0); //intake mogo
      waitBase(5000);

      //left neutral mogo
      liftPos = 5;
      waitLift();

      baseTurn(280, BMGFR_TURN_KP, BMGFR_TURN_KD);
      waitBase(5000);

      auton = f;
    }
    count += 1;

    if(Controller1.ButtonB.pressing()){
      auton2 = t;

    }
    if(auton2){
      twoBar(f);
      wait(200, msec);
      twoBar(t);
      
      auton2 = f;
    }
    
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
    if(Controller1.ButtonL1.pressing() && !L1Pressed){
      L1Pressed = t;
      twoBarTE = !twoBarTE; //switch 2b state
    }
    else if(!Controller1.ButtonL1.pressing()) {
      L1Pressed = f;
    }
    // twoBar(twoBarTE); //actuate 2b

    //frontMogo
    if(Controller1.ButtonL2.pressing() && !L2Pressed){
      L2Pressed = t;
      if(liftPos == 0){
        pcount = count;
      }
      frontMOG(t); //open
    }
    else{
      L2Pressed = f;
    }
    if((count-pcount) == 6 && pcount != 0) frontMOG(f); //close after controller loop runs 6 times

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
    else{
      R1Pressed = f;
    }
    if(Controller1.ButtonR2.pressing() && !R2Pressed){ //move down
      R2Pressed = t;
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
    else{
      R2Pressed = f;
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


