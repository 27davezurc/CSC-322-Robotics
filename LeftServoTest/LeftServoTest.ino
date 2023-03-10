/*
* Robotics with the BOE Shield - RightServoTest
* Right servo turns clockwise three seconds, stops 1 second, then
* counterclockwise three seconds.
*/
#include <Servo.h> // Include servo library

// -- global variables for servo motors
Servo left;
Servo right;

const int LEFTSERVOPIN = 13;
const int RIGHTSERVOPIN = 12;

void setup() // Built in initialization block
{ 
 left.attach(13); // Attach left signal to pin 13
 
 driveServos(200, 0); // Left wheel clockwise (works as intended)
 delay(3000); // ...for 3 seconds

 driveServos(0, 0); // Stays still (works as intended)
 delay(3000); // ...for 3 seconds
 
 driveServos(-200, 0); // Left wheel counterclockwise (works, but does not stop)
 delay(3000); // ...for 3 seconds

 driveServos(200, 0);
}

void driveServos(int leftpw, int rightpw) {

  left.writeMicroseconds(1500 + leftpw);
  right.writeMicroseconds(1500 - rightpw);
  
} // drive

void loop() // Main loop auto-repeats
{ // Empty, nothing needs repeating
} 
