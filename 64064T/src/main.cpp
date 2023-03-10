/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// frontRight           motor         20              
// frontLeft            motor         14              
// backRight            motor         19              
// backLeft             motor         17              
// loader               motor         18              
// feed                 motor         15              
// launch               motor         16              
// pneumatic1           digital_out   A               
// roller               motor         21              
// Pneumatic2           digital_out   B               
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
  loader.setVelocity(-50, percent);
  feed.setVelocity(10, percent);
  launch.setVelocity(-100, percent);
  frontRight.setVelocity(100, percent);
  frontLeft.setVelocity(100, percent);
  backRight.setVelocity(100, percent);
  backLeft.setVelocity(100, percent);
  roller.setVelocity(100, percent);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void driveC(int forward, int sideways, int turn) {
  frontRight.spin(vex::forward, forward - sideways + turn, vex::percent);
  frontLeft.spin(vex::forward, forward + sideways + turn, vex::percent);
  backRight.spin(vex::forward, forward + sideways - turn, vex::percent);
  backLeft.spin(vex::forward, forward - sideways - turn, vex::percent);
}

void stop() {
  driveC(0, 0, 0);
  frontRight.setPosition(0, degrees);
}

void goDegrees(double deg) {
  frontRight.setPosition(0, degrees);
  while (frontRight.position(degrees) * -1 < deg) {
    driveC(0, 50, 0);
  }
}

void go(int rotations) {
  frontRight.setPosition(0, degrees);
  for (int i = 0; i < rotations; i++) {
    driveC(0, 50, 0);
    wait(10, msec);
  }
}

void goBDegrees(double deg) {
  frontRight.setPosition(0, degrees);
  while (frontRight.position(degrees) < deg) {
    driveC(0, -50, 0);
  }
}

void goBack(int rotations) {
  frontRight.setPosition(0, degrees);
  for (int i = 0; i < rotations; i++) {
    driveC(0, 50, 0);
    wait(10, msec);
  }
}

void pRDegrees(double deg) {
  frontRight.setPosition(0, degrees);
  while (frontRight.position(degrees) < deg) {
    driveC(0, 0, 50);
  }
}

void pivotRight(int rotations) {
  frontRight.setPosition(0, degrees);
  for (int i = 0; i < rotations; i++) {
    driveC(0, 0, 50);
    wait(10, msec);
  }
}

void pLDegrees(double deg) {
  frontRight.setPosition(0, degrees);
  while (frontRight.position(degrees) * -1 < deg) {
    driveC(0, 0, -50);
  }
}

void pivotLeft(int rotations) {
  frontRight.setPosition(0, degrees);
  for (int i = 0; i < rotations; i++) {
    driveC(0, 0, -50);
    wait(10, msec);
  }
}

void rightDegrees(double deg) {
  frontRight.setPosition(0, degrees);
  while (frontRight.position(degrees) < deg) {
    driveC(50, 0, 0);
  }
}

void goRight(int rotations) {
  frontRight.setPosition(0, degrees);
  for (int i = 0; i < rotations; i++) {
    driveC(50, 0, 0);
    wait(10, msec);
  }
}

void leftDegrees(double deg) {
  frontRight.setPosition(0, degrees);
  while (frontRight.position(degrees) * -1 < deg) {
    driveC(-50, 0, 0);
  }
}

void goLeft(int rotations) {
  frontRight.setPosition(0, degrees);
  for (int i = 0; i < rotations; i++) {
    driveC(-50, 0, 0);
    wait(10, msec);
  }
}

void control() {
  int forward = Controller1.Axis1.position(vex::percent);
  int sideways = Controller1.Axis2.position(vex::percent);
  int turn = Controller1.Axis4.position(vex::percent);
  driveC(forward, sideways, turn);
}

void shootDeg(int rotations) { feed.spin(forward); }

void stopShoot() { feed.stop(); }

void loadIn() { loader.spin(forward); }

void loadStop() { loader.stop(); }

void shoot() {
  if (Controller1.ButtonR2.pressing()) {
    shootDeg(1);
  } else {
    stopShoot();
  }
}

void load() {
  if (Controller1.ButtonL1.pressing()) {
    loadIn();
  } else {
    loadStop();
  }
}

void feedMe(int roations) { launch.spin(forward); }

void starve() { launch.stop(); }

void feedMeHungy() {
  if (Controller1.ButtonR1.pressing()) {
    feedMe(1);
  } else {
    starve();
  } 
}

void expansion() {

  if (Brain.Timer.time(seconds) >= 65) {
    Brain.Screen.setCursor(3, 1);
    Brain.Screen.setPenColor(green);
    Brain.Screen.print("expansion saftey = true");
    if (Controller1.ButtonUp.pressing() && Controller1.ButtonA.pressing()) {
      pneumatic1.set(true);
      Pneumatic2.set(true);
      Brain.Screen.print("  Launch Cleared");
    }
  }
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

  Brain.Screen.print("auto");

  launch.spin(forward);
  wait(3, sec);
  
  feed.spinFor(forward, 15, turns);
  /*
  roller.spinFor(forward, 90, degrees);
  */
  Brain.Screen.newLine();
  Brain.Screen.print("END auto");
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
  // User control code here, inside the loop
  Brain.Timer.reset();
  while (1) {
    control();
    shoot();
    load();
    feedMeHungy();
    expansion();
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
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
