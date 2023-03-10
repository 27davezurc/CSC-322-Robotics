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
 right.attach(12); // Attach right signal to pin 12
 
 driveServos(0, 200); // Right wheel clockwise (works as intended)
 delay(3000); // ...for 3 seconds

 driveServos(0, 0); // Stays still (works as intended)
 delay(3000); // ...for 3 seconds
 
 driveServos(0, -200); // Right wheel counterclockwise (works, but does not stop)
 delay(3000); // ...for 3 seconds

 driveServos(0, 200);
 //servoRight.writeMicroseconds(1500); // Right wheel counterclockwise
}

void driveServos(int leftpw, int rightpw) {

  left.writeMicroseconds(1500 + leftpw);
  right.writeMicroseconds(1500 - rightpw);
  
} // drive

void loop() // Main loop auto-repeats
{ // Empty, nothing needs repeating
} 
