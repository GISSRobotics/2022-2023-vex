/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// expandmotor          motor         20              
// rollermotor          motor         21              
// MotorGroupR          motor_group   8, 9            
// MotorR               motor         10              
// MotorGroupL          motor_group   11, 12          
// MotorL               motor         13              
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

void leftmotors(int Lvelocity) { // group all motors that will power the left
                                 // side of the drivetrain
  if (Lvelocity != 0) {
    MotorGroupL.spin(forward);
    MotorL.spin(forward);
    MotorGroupL.setVelocity(Lvelocity, percent);
    MotorL.setVelocity(Lvelocity, percent);
  } else {
    MotorGroupL.stop();
    MotorL.stop();
  }
}

void rightmotors(int Rvelocity) { // group all motors that will power the right
                                  // side of the drivetrain
  MotorGroupR.spin(forward);
  MotorR.spin(forward);
  MotorGroupR.setVelocity(Rvelocity, percent);
  MotorR.setVelocity(Rvelocity, percent);
}



void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}
void autorollers(void) { // for automating the turning of colour-coded rollers
}

void autofire(void) { // for automating the fireing of the disks, woirth a
  /*                    // breakout clause if the spinmotor override is pressed.
  bool breakloop = false;
  bool abortfire = false;
  spinmotor.setVelocity(100, percent);
  spinmotor.spin(forward);
  while (breakloop ==
         false) { // wait until flywheel motor is up to speed by looping until
                  // it is up to speed or override is pressed
    if (Controller1.ButtonL1.pressing() == true or
        Controller1.ButtonL2.pressing() == true) {
      breakloop = true;
      abortfire = true;
    } else {
      if (spinmotor.velocity(percent) >= 98) {
        breakloop = true;
        abortfire = false;
      } else {
        wait(100, msec);
      }
    }
  }
  if (abortfire == false) {
    firemotor.spinFor(forward, 30, degrees);
    wait(500, msec);
    firemotor.spinFor(reverse, 30, degrees);
  }
  spinmotor.stop();*/
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

void autonomous(void) { // tested, works?
rightmotors(50);
leftmotors(50);
wait(100,msec);
rightmotors(0);
leftmotors(0);
rollermotor.spinFor(forward,90,degrees);
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
  //bool turned = false;
  int linintention=0;
  int turintention=0;
  while (1) { // loop forever

// start 6wd block - tested, works but could require improvement


linintention =  Controller1.Axis3.position(percent); // align varible with respective axis - aids with thought process
    turintention = Controller1.Axis4.position(percent);
    if (linintention != 0 and turintention != 0) { // if both axis don't equal zero, average their wishes
      rightmotors(((2*linintention) + (-2*turintention)) / 2);
      leftmotors(((2*linintention) + (2*turintention)) / 2);
    } else { // else, if only linear axis active, go forwards
      if (linintention != 0 and turintention == 0) {
        leftmotors(linintention);
        rightmotors(linintention);
      } else { // else, if only turning axis active, turn
        if (linintention == 0 and turintention != 0) {
          rightmotors(-1 * turintention);
          leftmotors(turintention);
        } else { // else, stop
          leftmotors(0);
          rightmotors(0);
        }
      }
    }

/*//start disc firing block - tested, works imperfectly

    if(Controller1.ButtonA.pressing() == true or Controller1.ButtonA.pressing() == true){ // if the left arrow button is pressed, make the disc fireing motor turn at full speed
      spinmotor.setVelocity(330,rpm);
      spinmotor.spin(forward);
      }
    else{ // otherwise, stop the motor
      spinmotor.stop();}

    if (Controller1.ButtonL1.pressing() == true) { // if told to go to fireing disc position, execute:
      if (spinmotor.velocity(rpm) >= 325){ // if the flywheel is up to speed, execute:
        if (turned == false) { // if the armn isn't already there, make it so and tell the computer that
          firemotor.spinFor(forward, 45, degrees);
          turned = true;
        }
      }
    }
    else {
      if (turned == true) { // if  it isn't told to yet is, then turn the arm back, while twelling the computer that this has happened.
      firemotor.spinFor(reverse, 45, degrees);
      turned = false;
      }
    }
    */
    // end disc fireing block; start roller control block - tested, works.
    if (Controller1.ButtonR1.pressing() == true) { // checks if the upwards roller override button pressed
      rollermotor.spin(forward);
      rollermotor.setVelocity(30,percent);
    }
    else{
      if (Controller1.ButtonR2.pressing() == true) { // checks if the upwards roller override button pressed
      rollermotor.spin(reverse);
      rollermotor.setVelocity(-30,percent);
      }
      else{
        rollermotor.stop();
      }
    }

    // end roller control block; start expansion control block - tested, works

    if(Controller1.ButtonLeft.pressing() == true){
      expandmotor.setVelocity(35,percent);
      expandmotor.spin(forward);
    }
    else{
      if(Controller1.ButtonRight.pressing() == true){
      expandmotor.setVelocity(35,percent);
      expandmotor.spin(reverse);
      }
      else{
        expandmotor.stop();
      }
    }

    wait(20, msec);
  } // Sleep the task for a short amount of time to prevent wasted resources.
}
// Main will set up the competition functions and callbacks.

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
