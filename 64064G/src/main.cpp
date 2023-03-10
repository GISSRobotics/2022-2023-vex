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
// Vision               vision        20              
// rollerMotor          motor         18              
// expansionMotor       motor         14              
// Drivetrain           drivetrain    4, 15, 12, 3    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

// Global variables to use throughout program
// that can be changed by clicking the screen
bool ON_RED_ALLIANCE = true;
bool IN_LEFT_START_POSITION = true;
void allianceAndPositionSelect() {
  // Read the position of the screen that was clicked
  int x = Brain.Screen.xPosition();
  int y = Brain.Screen.yPosition();

  // Save which button was clicked in the global variable
  IN_LEFT_START_POSITION = x < 240;
  ON_RED_ALLIANCE = y < 130;
  // Position cursor and clear out last value
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.clearLine();

  // Print out
  if (ON_RED_ALLIANCE) {
    Brain.Screen.print("Red Alliance - ");
  } else {
    Brain.Screen.print("Blue Alliance - ");
  }
  if (IN_LEFT_START_POSITION) {
    Brain.Screen.print("Left Position");
  } else {
    Brain.Screen.print("Right Position");
  }
}
void launchAllianceAndPositionChooser() {
  // Draw the Alliance and position buttons on the screen
  Brain.Screen.clearScreen();
  Brain.Screen.setFillColor(red);
  Brain.Screen.drawRectangle(10, 30, 225, 95);
  Brain.Screen.drawRectangle(245, 30, 225, 95);
  Brain.Screen.setFillColor(blue);
  Brain.Screen.drawRectangle(245, 135, 225, 95);
  Brain.Screen.drawRectangle(10, 135, 225, 95);
  // Listen to screen presses to save alliance and position in variables
  Brain.Screen.pressed(allianceAndPositionSelect);
}

void setRoller(void) {
  rollerMotor.spin(forward);
  bool done = false;

  while (!done) {
    if (Controller1.ButtonX.pressing()) {
      done = true;
    }
    Vision.takeSnapshot(Vision__REDDISH);
    if (Vision.objectCount > 0) {
      int redY = Vision.objects[0].centerY;
      Vision.takeSnapshot(Vision__BLUEISH);
      if (Vision.objectCount > 0) {
        if ((ON_RED_ALLIANCE && Vision.objects[0].centerY > redY) ||
            (!ON_RED_ALLIANCE && Vision.objects[0].centerY < redY)) {
          done = true;
        }
      }
    }
  }
  rollerMotor.stop();
}

bool launched = false;

void launch(void) {
  if (!launched) {
    expansionMotor.spinFor(90, degrees);
  }

  launched = true;
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions */
/*                                                                           */
/*  You may want to perform some actions before the competition
 * starts.      */
/*  Do them in the following function.  You must return from this
 * function   */
/*  or the autonomous and usercontrol tasks will not be started.
 * This       */
/*  function is only called once after the V5 has been powered on
 * and        */
/*  not every time that the robot is disabled. */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  Controller1.ButtonY.pressed(setRoller);
  Controller1.ButtonUp.pressed(launch);
  launchAllianceAndPositionChooser();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task */
/*                                                                           */
/*  This task is used to control your robot during the autonomous
 * phase of   */
/*  a VEX Competition. */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands
 * here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  Drivetrain.driveFor (reverse,  1, inches);
  setRoller();
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task */
/*                                                                           */
/*  This task is used to control your robot during the user control
 * phase of */
/*  a VEX Competition. */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands
 * here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {

  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor +
    // servo values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick
    // values to update your motors, etc.
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
