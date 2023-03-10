#include <Servo.h> // Include servo library

// -- global variables for servo motors
Servo left;
Servo right;

const int LEFTSERVOPIN = 13;
const int RIGHTSERVOPIN = 12;

int const LEFTWPIN = 5;
int const RIGHTWPIN = 7;

void setup() {

  // Attach signals to designated pins
  left.attach(13);
  right.attach(12);
  
  pinMode(LEFTWPIN, INPUT);
  pinMode(RIGHTWPIN, INPUT);

  Serial.begin(9600);

  // tone is a long variable type
  // tone(SERVOPIN, tone, duration in ms)

  // Left whisker as seen, right whisker as seen
}

void loop() {

  // Sense the environment: 0 means touching; 1 is not touching
  int leftw = digitalRead(LEFTWPIN);
  int rightw = digitalRead(RIGHTWPIN);

  // Determine action:
  if (leftw == 0 && rightw == 0) {
    // Backup
    driveServos(-200, -200);
    delay(3000);
    
    // Turn 180 degrees
    driveServos(200, 0);
    delay(3000);

    driveServos(0, 0);
  } else if (leftw == 0 && rightw == 1) {
    // Backup
    driveServos(-200, -200);
    delay(3000);

    // Turn right 90 degrees
    driveServos(200, 0);
    delay(1500);

    driveServos(0, 0);
  } 
  else if (leftw == 1 && rightw == 0) {
    // Backup    
    driveServos(-200, -200);
    delay(3000);

    // Turn left 90 degrees
    driveServos(0, 200);
    delay(1500);    

    driveServos(0, 0);
  } 
  else if (leftw == 1 && rightw == 1) {
    // Forward
    driveServos(200, 200);
    delay(3000);

    driveServos(0, 0);
  }
  
  // Achieve goal:
  Serial.print(leftw);
  Serial.print(rightw);
  Serial.println();
  delay(100);
  
}

void driveServos(int leftpw, int rightpw) {

  left.writeMicroseconds(1500 + leftpw);
  right.writeMicroseconds(1500 - rightpw);

//      driveServos(-200, -200); // Forwards
//      driveServos(200, 200); // Backwards
//      driveServos(0, -200); // Turn right
//      driveServos(-200, 0); // Turn left
} // drive
