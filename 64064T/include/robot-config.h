using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor frontRight;
extern motor frontLeft;
extern motor backRight;
extern motor backLeft;
extern motor loader;
extern motor feed;
extern motor launch;
extern digital_out pneumatic1;
extern motor roller;
extern digital_out Pneumatic2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );