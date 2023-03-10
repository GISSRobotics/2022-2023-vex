#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor expandmotor = motor(PORT20, ratio18_1, false);
motor rollermotor = motor(PORT21, ratio18_1, false);
motor MotorGroupRMotorA = motor(PORT8, ratio18_1, true);
motor MotorGroupRMotorB = motor(PORT9, ratio18_1, true);
motor_group MotorGroupR = motor_group(MotorGroupRMotorA, MotorGroupRMotorB);
motor MotorR = motor(PORT10, ratio18_1, true);
motor MotorGroupLMotorA = motor(PORT11, ratio18_1, false);
motor MotorGroupLMotorB = motor(PORT12, ratio18_1, false);
motor_group MotorGroupL = motor_group(MotorGroupLMotorA, MotorGroupLMotorB);
motor MotorL = motor(PORT13, ratio18_1, false);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}