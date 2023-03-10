using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor expandmotor;
extern motor rollermotor;
extern motor_group MotorGroupR;
extern motor MotorR;
extern motor_group MotorGroupL;
extern motor MotorL;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );