#include <Servo.h> // Include servo library

// -- global variables for servo motors
Servo left;
Servo right;

const int LEFTSERVOPIN = 13;
const int RIGHTSERVOPIN = 12;

void setup() {
  // put your setup code here, to run once:
  
  // Attach signals to designated pins
  left.attach(13);
  right.attach(12);
  
//   Traverse straight line
  driveServos(200, 200);
  delay(5000);
  
  // Turn right
  driveServos(200, 0);
  delay(1300); 
  
  // Traverse 360 degrees counter-clockwise
  driveServos(27,75);
  delay(12000);

  // Turn right
  driveServos(200, 0);
  delay(1300);
  driveServos(0,0);
  delay(500);

  //   Traverse straight line
  driveServos(200, 200);
  delay(5000);
  driveServos(0,0);
  delay(500);

  // Turn left
  driveServos(-80, 180);
  delay(1000);

  // Square:
    // short straight
    driveServos(200, 200);
    delay(1000);
    
    // Turn right: 1
    driveServos(200, 0);
    delay(1750);
    
    // medium straight
    driveServos(200, 200);
    delay(1700);
    
    // Turn right: 2
    driveServos(200, 0);
    delay(2200);
    
    // medium straight
    driveServos(200, 200);
    delay(2300); //1500
    
    // Turn right: 3
    driveServos(170, -30);
    delay(900); // 1700
   
    // medium straight
    driveServos(200, 200);
    delay(2200);
    
    // Turn right: 4
    driveServos(200, -15);
    delay(1400); // 2200
    
    // short straight
    driveServos(200, 200);
    delay(1500);
    driveServos(0,0);
    delay(500);
    
  // Turn left
  driveServos(0, 200);
  delay(1300);

  driveServos(0, 0);
  delay(100);
  
}

void driveServos(int leftpw, int rightpw) {

  left.writeMicroseconds(1500 + leftpw);
  right.writeMicroseconds(1500 - rightpw);
  
} // drive

void loop() {
  // put your main code here, to run repeatedly;
}
