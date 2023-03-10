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
// BackRightDriveMotor  motor         1
// BackLeftDriveMotor   motor         2
// FrontLeftDriveMotor  motor         3
// FrontRightDriveMotor motor         4
// Intake               motor         6
// Flywheel             motor         5
// PizzaCutter          motor         10
// Roller               motor         7
// Optical              optical       12
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
// bool Controller1UpDownButtonsControlMotorsStopped = true;

// define your global instances of motors and other devices here

void move(int forwards, int sideways, int turn) {
  FrontRightDriveMotor.spin(vex::forward, forwards + sideways - turn,
                            vex::percent);
  FrontLeftDriveMotor.spin(vex::forward, forwards - sideways + turn,
                           vex::percent);
  BackRightDriveMotor.spin(vex::forward, forwards - sideways - turn,
                           vex::percent);
  BackLeftDriveMotor.spin(vex::forward, forwards + sideways + turn,
                          vex::percent);
}

void moveStop() {
  FrontLeftDriveMotor.stop();
  FrontRightDriveMotor.stop();
  BackLeftDriveMotor.stop();
  BackRightDriveMotor.stop();
}

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

void switchingTeam() {
  // Global variables to use throughout program
  // that can be changed by clicking the screen
  allianceAndPositionSelect();
  launchAllianceAndPositionChooser();
}

// get rollers to blue
void whatColourBlue() {
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.clearLine();
  Brain.Screen.print(Optical.color());

  if (Optical.color() > 250 && Optical.color() <= 260) {
    Roller.stop();
  } else {
    Roller.spin(forward);
  }
}

void whatColourRed() {
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.clearLine();
  Brain.Screen.print(Optical.color());
  if (Optical.color() == 16711680) {
    Roller.stop();
  } else {
    Roller.spin(forward);
  }
}

// if the rollers are complete, stop moving
void rollerMoveStop() {
  if (Optical.color() == blue) {
    moveStop();
  } else if (Optical.color() == cyan) {
    moveStop();
  }
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
  // int v();

  switchingTeam();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...

  Flywheel.setVelocity(100, percent);
  PizzaCutter.setVelocity(100, percent);
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

  /*
    if start left
      do left
    else
      do right
    end

    do either side
  */

  if (IN_LEFT_START_POSITION == true) {
    // left auton

    // get roller
    move(0, 100, 0);
    Roller.spinFor(reverse, 80, degrees);

    // move away
    move(0, -100, 0);
    wait(.1, sec);
    moveStop();

    // turn around
    move(0, 0, 100);
    wait(.7, sec);
    moveStop();

    // shoot discs
    Flywheel.spin(forward);
    wait(3, sec);
    PizzaCutter.spinFor(reverse, 2, sec);
    Intake.spin(reverse);
    wait(1, sec);
    PizzaCutter.spinFor(reverse, 2, sec);
    Flywheel.stop();
    PizzaCutter.stop();
    Intake.stop();

  } else {
    // right side

    // move left
    move(0, -100, 0);
    wait(1, sec);
    moveStop();

    // shoot discs
    Flywheel.spin(forward);
    wait(3, sec);
    PizzaCutter.spinFor(reverse, 2, sec);
    Intake.spin(reverse);
    wait(1, sec);
    PizzaCutter.spinFor(reverse, 2, sec);
    Flywheel.stop();
    PizzaCutter.stop();
    Intake.stop();
  }

  // testing
  // move(100, 0, 0); = foward
  // move(0, 100, 0); = right
  // move(0, 0, 100); = turn right
  // one full turn = 1.4 sec
  // Roller.spinFor(forward, 360, degrees);
  // wait(.5, sec);
  // moveStop();
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

void PCButton() {
  if ((Controller1.ButtonL1.pressing()) && (Flywheel.velocity(rpm) > 250)) {
    PizzaCutter.spin(reverse);
  } else {
    PizzaCutter.stop();
    wait(5, msec);
  }
}

//void rollerButton() {
  /*
  if button pressing
     if red alliance
       do red
      else
        do blue
      end
  end
  */
/*
  if (ON_RED_ALLIANCE == true) {
    Optical.setLightPower(100, percent);
    whatColourRed();
  } else if (ON_RED_ALLIANCE == false) {
    Optical.setLightPower(100, percent);
    whatColourBlue();
  } else {
    wait(20, msec);
  }
}
*/
void move() {
  int forwards = Controller1.Axis3.position();
  int sideways = Controller1.Axis4.position();
  int turn = Controller1.Axis1.position();
  move(forwards, sideways, turn);
}

void usercontrol(void) {
  while (1) {

    move();
    PCButton();
   // rollerButton();

    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
