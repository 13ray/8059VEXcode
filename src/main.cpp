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
  // while(t) {
  //   if(Controller1.ButtonA.pressing()) {
  //     frontMogo.set(t);
  //     Controller1.Screen.print("port b and d true");
  //   }
  //   else if(Controller1.ButtonA.pressing() && Controller1.ButtonL1.pressing()) {
  //     frontMogo.set(f);
  //     Controller1.Screen.print("port b and d false");
  //   }
  //   else if(Controller1.ButtonX.pressing()) {
  //     digital_out(Brain.ThreeWirePort.C).set(t);
  //     Controller1.Screen.print("port c true");
  //   }
  //   else if(Controller1.ButtonX.pressing() && Controller1.ButtonA.pressing()) {
  //     digital_out(Brain.ThreeWirePort.C).set(f);
  //     Controller1.Screen.print("port c false");
  //   }
  //   else if(Controller1.ButtonY.pressing()) {
  //     digital_out(Brain.ThreeWirePort.E).set(t);
  //     Controller1.Screen.print("port e true");
  //   }
  //   else if(Controller1.ButtonY.pressing() && Controller1.ButtonL1.pressing()) {
  //     digital_out(Brain.ThreeWirePort.E).set(f);
  //     Controller1.Screen.print("port e false");
  //   }
  //   else if(Controller1.ButtonUp.pressing()) {
  //     digital_out(Brain.ThreeWirePort.F).set(t);
  //     Controller1.Screen.print("port f true");
  //   }
  //   else if(Controller1.ButtonUp.pressing() && Controller1.ButtonL1.pressing()) {
  //     digital_out(Brain.ThreeWirePort.F).set(f);
  //     Controller1.Screen.print("port f false");
  //   }
  //   Controller1.Screen.clearScreen();

  int driveMode = 1, tbMode = 0;
  std::string drivePrint = "";
  int LBSpeed = 0, RBSpeed = 0;
  int count = 0, pcount = 0;
  int by = 0, r1 = 0, r2 = 0, lr1 = 0, lr2 = 0, pby = 0, pr1 = 0, pr2 = 0, plr1 = 0, plr2 = 0, l1 = 0;
  // User control code here, inside the loop
  while (t) {
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
    else {
      LBSpeed = Controller1.Axis3.position();
      RBSpeed = Controller1.Axis2.position();
      drivePrint = "Tank    ";
    }

    leftBase.spin(fwd, LBSpeed, pct);
    rightBase.spin(fwd, RBSpeed, pct);
    
    //button counts
    if(Controller1.ButtonR2.pressing() && Controller1.ButtonL2.pressing()){lr2 += 1;}
    else if(Controller1.ButtonR2.pressing() && !Controller1.ButtonL2.pressing()) {r2 += 1;}
    else if(Controller1.ButtonR1.pressing() && Controller1.ButtonL2.pressing()) {lr1 += 1;} 
    else if(Controller1.ButtonR1.pressing() && !Controller1.ButtonL2.pressing()) {r1 += 1;}
    
    //2 bar
    if(lr2 == plr2 && lr2 != 0) {
      if(tbMode == 3) {tbMode = 0;}
      else {tbMode += 1;}
      
      if(tbMode%4 == 1) { //up close
        twoBar(f); 
        backMogo.set(f);
      }
      else if(tbMode%4 == 3) { //down open 
        twoBar(t);
        backMogo.set(t);;
      } 
      else {
        twoBar(t);
        backMogo.set(f);
      }
      lr2 = 0;
    }
    //front mogo intake
    else if(r2 == pr2 && r2 != 0) {
      frontMogo.set(f);
      if(liftPos == 0) {
        pcount = count;
      }
      r2 = 0;
    }
    //lift
    else if(lr1 == plr1 && lr1 != 0) {
      // liftAssist(t);
      if(liftPos == 0) {
        Controller1.rumble("-"); 
      }
      else {
        liftPos -= 1;
        if(liftPos == 0) {
          frontMogo.set(t);
        }
      }
      lr1 = 0;
    }
    else if(r1 == pr1 && r1 != 0) {
      // liftAssist(f);
      if(liftPos == 2) {
        Controller1.rumble("-");
      }
      else {
        liftPos += 1;
      }
      r1 = 0;
    }
    //front mogo
    if((count-pcount) == 10 && pcount != 0) frontMogo.set(t);

    //conveyor
    if(liftPos != 0) {
      if(Controller1.ButtonL1.pressing() && Controller1.ButtonL2.pressing()) {
        conveyor.spin(fwd, 100, pct);
      }
      else if(Controller1.ButtonL1.pressing()) {
        l1 += 1;
        conveyor.spin(reverse, 100, pct);
      }
      else {
        conveyor.stop();
      }
    }
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Two Bar = %d", tbMode);
    // printf("%.4f\n", lift.torque());
    Controller1.Screen.setCursor(2, 1);
    Controller1.Screen.print("Lift Pos = %d, %.1f", liftPos, pot_liftValue);
    Controller1.Screen.setCursor(3, 1);
    Controller1.Screen.print(drivePrint.c_str());

    // printf("r1: %d,\tr2: %d,\tlr1: %d,\t\tlr2: %d, %d\n", r1, r2, lr1, lr2, l1);
    // printf("pr1: %d,\tpr2: %d,\tplr1: %d,\tplr2: %d\n", pr1, pr2, plr1, plr2);
    //printf("by: %d\n", by);
    pr1 = r1, pr2 = r2, plr1 = lr1, plr2 = lr2, pby = by;
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  //task controlTask(Control);
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
    wait(1, msec);
  }
}