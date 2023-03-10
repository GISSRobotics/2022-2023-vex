/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\terri                                            */
/*    Created:      Tue Jan 31 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// frontLeft            motor         3               
// frontRight           motor         2               
// backLeft             motor         7               
// backRight            motor         6               
// Controller1          controller                    
// Spinner4Launcher     motor         8               
// MotorGroup9          motor_group   9, 10           
// SliderBelt           motor         11              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
//motor_group(Motor10,Motor9);
    
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  //motor_group: Motor10,Motor9;

  vexcodeInit();

    Spinner4Launcher.setVelocity(100, percent); 

    MotorGroup9.setVelocity(100,percent);

    SliderBelt.setVelocity(100,percent);

    //Motor9.setVelocity(100,percent),Motor10.setVelocity(-100,percent);

   while(1)
   {
     double rotate = Controller1.Axis1.position(percent);
     double forward = Controller1.Axis3.position(percent);
     double sideways = Controller1.Axis4.position(percent);


     frontRight.spin(vex::forward, rotate - sideways + forward, vex::percent);
     frontLeft.spin(vex::forward,  rotate - sideways - forward, vex::percent);
     backRight.spin(vex::forward,  rotate + sideways + forward, vex::percent);
     backLeft.spin(vex::forward,   rotate + sideways - forward, vex::percent);    
   }
}