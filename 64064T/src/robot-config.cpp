#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor frontRight = motor(PORT20, ratio18_1, true);
motor frontLeft = motor(PORT14, ratio18_1, true);
motor backRight = motor(PORT19, ratio18_1, true);
motor backLeft = motor(PORT17, ratio18_1, true);
motor loader = motor(PORT18, ratio18_1, false);
motor feed = motor(PORT15, ratio18_1, false);
motor launch = motor(PORT16, ratio6_1, false);
digital_out pneumatic1 = digital_out(Brain.ThreeWirePort.A);
motor roller = motor(PORT21, ratio18_1, false);
digital_out Pneumatic2 = digital_out(Brain.ThreeWirePort.B);

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