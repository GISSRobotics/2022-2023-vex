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
// Drivetrain           drivetrain    4, 7
// launcher5            motor         5
// roller6              motor         6
// sideways83           motor_group   8, 3
// flywheel1            motor         1
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

int launcher() {
  // you don't need this loop either, it will capture the program control and
  // not let anything else happen
  while (true) {
    if (Controller1.ButtonLeft.pressing()) {
      flywheel20.spin(reverse);
    }
  };
}

// Automatic Roller Spinner
int roller() {
  /*
  if button pressed{
    look at colour
    if blue
       spin roller
    else
       stop roller
  pause 20ms
  }
  */
  // you don't need this while(true) {}
  // it will capture control and not release program flow back

  while (true) {

    if (Controller1.ButtonL2.pressing()) {
      // if left shoulder 2 button pressing spin roller in one direction
      roller6.spin(forward);

    } else if (Controller1.ButtonR2.pressing()) {
      // if right shoulder 2 button pressing spin roller in one direction
      roller6.spin(reverse);
    } else if (Controller1.ButtonL1.pressing()) {
      // if left shoulder 1 button pressing
      // turn on the light check the color and spin until not blue
      colour2.setLightPower(100);
      if (colour2.color() == red) {
        roller6.spin(forward);
      } else {
        roller6.stop();
      }
    } else if (Controller1.ButtonR1.pressing()) {
      // if right shoulder 1 button pressing
      // turn on the light check the color and spin until not blue
      colour2.setLightPower(100);
      if (colour2.color() == red) {
        roller6.spin(reverse);
      } else {
        roller6.stop();
      }
    } else {
      // turn off the light and stop the roller
      colour2.setLightPower(0);
      roller6.stop();
    }
    // end of the while loop so goes back to the top
  }
  return 0;
}

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

  roller6.setMaxTorque(100, percent);
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
  Brain.Screen.print(colour2.color());

  // turn on the light
  colour2.setLightPower(100);
  Drivetrain.driveFor(forward, 18, inches);

  while (true) {
    // drive forward
    if (colour2.color() == red) {
      // if blue spin the roller
      roller6.spin(forward);
    } else {
      // stop the roller
      roller6.stop();
    }
    // let things happen for a bit
    wait(20, msec);
    // loop until end of the auto mode
  }

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
  task rollerSpinner(roller);
  // User control code here, inside the loop
  while (1) {
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
