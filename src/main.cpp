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
    
    /*if(Controller1.ButtonA.pressing()) auton = t;
    if(auton){
      // baseTurn(30,FMGS_TURN_KP,FMGS_TURN_KD);
      
      resetCoords(0,0,0);

      //right red mogo
      baseMove(4, DEFAULT_KP, DEFAULT_KD); //intake right red
      waitBase(800);

      baseMove(-11, DEFAULT_KP, DEFAULT_KD); //reverse
      waitBase(800);

      task liftTask(Lift);
      liftPos = 5;
      waitLift();

      //right neutral mogo
      baseTurn(305.5, FMG_TURN_KP, FMG_TURN_KD); //face mogo
      waitBase(3000);
      
      baseMove(36, FMG_KP, FMG_KD); //go to mogo
      waitBase(8000);

      liftPos = 0;
      waitLift();
      baseMove(14.7, FMG_KP-0.03, FMG_KD); //intake right neutral
      waitBase(4000);
      resetRot();

      //clearing rings
      liftPos = 2;
      baseMove(35,FMGS_KP, FMGS_KD);
      waitBase(9000);
      resetRot();
      wait(500, msec);

      baseTurn(12, FMGS_TURN_KP, FMGS_TURN_KD); //face rings
      waitBase(3000);

      baseMove(30, FMGS_KP, FMGS_KD); //clear rings
      waitBase(4500);
      wait(500, msec);

      //scoring neutral and red mogos
      baseMove(-14.7, FMGS_KP, FMGS_KD);
      waitBase(7800);

      baseTurn(286, FMGS_TURN_KP, FMGS_TURN_KD); //face platform
      waitBase(4300);

      baseMove(20.5, FMGS_KP-0.05, 0); //go into platform
      waitBase(3000);
      
      liftPos = 1;
      waitLift();
      frontMOG(t); //score
      wait(200, msec);

      //tall neutral
      liftPos = 2;
      waitLift();
      
      timerBase(30, 30, 500); //align against platform
      timerBase(19, 18, 250);
      resetRot();

      baseMove(-43.5, DEFAULT_KP-0.06, 0); //intake tall neutral
      waitBase(20000);
      liftPos = 0;
      twoBar(t);
      frontMOG(f);
      wait(100, msec);

      //left neutral mogo
      baseTurn(8, BMG_TURN_KP, BMG_TURN_KD); //face mogo
      waitBase(6000);

      baseMove(21, BMG_KP, BMG_KD); //intake left neutral 
      waitBase(10000);

      wait(100, msec);
      liftPos = 5;
      waitLift();

      //left red mogo
      baseTurn(105, BMGFR_TURN_KP, BMGFR_TURN_KD); //face platform
      waitBase(5000);

      baseMove(30, BMG_KP, BMG_KD);
      waitBase(10000);

      baseTurn(20, BMGFR_TURN_KP, BMGFR_TURN_KD); //face mogo
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
    }*/

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
    twoBar(twoBarTE); //actuate 2b*/

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


