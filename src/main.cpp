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
  baseMove(24);
  waitBase(2000);
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
  int driveMode = 1;
  std::string drivePrint = "";
  int LBSpeed = 0, RBSpeed = 0;
  int count = 0; //, pcount = 0;
  int by = 0, pby = 0;
  bool twoBarTE = false; //twoBar toggle Enabled
  bool frontTE = false; //frontmogos toggle Enabled
  bool latchTE = false; //latch toggle Enabled
  bool L1Pressed = false; //flag
  bool L2Pressed = false;
  bool UPPressed = false;

    
  //int r1 = 0, r2 = 0, l1r1 = 0, l2r2 = 0, l1 = 0, ll2 = 0,  pr1 = 0, pr2 = 0, pl1r1 = 0, pl2r2 = 0, pl1 = 0, pll2 = 0;
  
  // User control code here, inside the loop
  while (t) {
    bool L1 = Controller1.ButtonL1.pressing();
    bool L2 = Controller1.ButtonL2.pressing();
    bool UP = Controller1.ButtonUp.pressing();
    count += 1;
    //drivemode
    if(Controller1.ButtonY.pressing()) by += 1;
    if(by == pby && by!= 0) driveMode += 1, by = 0;
    if(driveMode%3 == 1) { //reverse arcade
      LBSpeed = Controller1.Axis2.position() + Controller1.Axis4.position();
      RBSpeed = Controller1.Axis2.position() - Controller1.Axis4.position();
      drivePrint = "R Arcade";
    }
    else if(driveMode%3 == 2) { //normal arcade
      LBSpeed = Controller1.Axis3.position() + Controller1.Axis1.position();
      RBSpeed = Controller1.Axis3.position() - Controller1.Axis1.position(); 
      drivePrint = "Arcade  ";
    }
    else { //tank
      LBSpeed = Controller1.Axis3.position();
      RBSpeed = Controller1.Axis2.position();
      drivePrint = "Tank    ";
    }

    leftBase.spin(fwd, LBSpeed, pct);
    rightBase.spin(fwd, RBSpeed, pct);
    
    /*button counts
    if(Controller1.ButtonR2.pressing() && Controller1.ButtonL2.pressing()){l2r2 += 1;}
    else if(Controller1.ButtonR2.pressing() && !Controller1.ButtonL2.pressing()) {r2 += 1;}
    else if(Controller1.ButtonR1.pressing() && Controller1.ButtonL2.pressing()) {l1r1 += 1;} 
    else if(Controller1.ButtonR1.pressing() && !Controller1.ButtonL2.pressing()) {r1 += 1;}
    else if(Controller1.ButtonL1.pressing() && !Controller1.ButtonL2.pressing()) {l1 += 1;}
    else if(Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing()) {ll2 += 1;} */
    

    /////////2 bar
    if(L1 && !L1Pressed){
      L1Pressed = t;
      twoBarTE = !twoBarTE;
      //twoBar(t);
    }else if(!L1) L1Pressed = false;
    
    if(twoBarTE){
      twoBar(t);
    }else{
      twoBar(f);
    }

    ///////////4 bar
    if(L2 && !L2Pressed){
      L2Pressed = t;
      frontTE = !frontTE;
    }else if(!L2) L2Pressed = false;
    
    if(frontTE){
      frontMOG(t);
    }else{
      frontMOG(f);
    }

    ///Latch
    
    if(UP && !UPPressed){
      UPPressed = t;
      latchTE = !latchTE;
    }else if(!UP) UPPressed = false;

    if(latchTE){
      if(liftPos == 2){
          liftPos += 1;
        }
        Latch(t);
        if(liftPos == 3){
          liftPos +=1;
          }
    }

////Lift
    if(Controller1.ButtonR1.pressing()){
      if(liftPos < 2){
        liftPos +=1;
      }else if(liftPos == 2){
        Controller1.rumble("-");
      }}

    if(Controller1.ButtonR2.pressing()){
      if( liftPos > 0 && liftPos <= 2){
        liftPos -= 1;
      }else if(liftPos == 0){
        Controller1.rumble("-");
        //printf("curr angle: %d\n", pot_liftValue);
        
      }
    }
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Two Bar = %d", twoBarL.value());
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Lift Pos = %d, %d", liftPos, pot_liftValue);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(drivePrint.c_str());
    //printf("pot_liftValue %d", pot_liftValue);

  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  task controlTask(Control);
  task sensorTask(Sensors);
  task odomTask(Odometry);
  //task debugTask(Debug);
  task liftTask(Lift);

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


