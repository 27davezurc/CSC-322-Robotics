#include <Servo.h> // Include servo library

// -- global variables for servo motors
Servo leftServo;
Servo rightServo;

// Servo Pins
const int LEFTSERVOPIN = 12;
const int RIGHTSERVOPIN = 13;

// Touch Sensor Pins
int const LEFTWPIN = 5;
int const RIGHTWPIN = 7;

// Analog Pins
const int LEFTAPIN = A1;
const int RIGHTAPIN = A2;

// Variables for Ambient Light
double leftAmbient = 0;
double rightAmbient = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // Attach signals to designated pins
  leftServo.attach(LEFTSERVOPIN);
  rightServo.attach(RIGHTSERVOPIN);
  
  // General calibration:
  double right = 0;
  double left = 0;

  // Make a circle:
  //driveServos(35, 200);
  //delay(10500);
  //driveServos(0, 0);

  // Take measurements: 360 is an arbitrary number, N (any number) will do
  // I chose 105 bc that's how long it took for my robot to circle
    // Takes 105 * 100 = 10500 ms for one circle
  for(int i = 0; i < 105; i++) {
    left += analogRead(LEFTAPIN);
    right += analogRead(RIGHTAPIN);

    driveServos(35, 200);
    delay(100);

    Serial.print("left: "); Serial.print(left);
    Serial.print("  right: "); Serial.print(right);
    Serial.println();
  }

  driveServos(0, 0);
  
  // Divide left and right by N: 
  leftAmbient = (left / 105);
  rightAmbient = (right / 105);

  // Add 5% to calibration
//  leftAmbient = (leftAmbient * .05) + leftAmbient;
//  rightAmbient = (rightAmbient * .05) + rightAmbient;

  Serial.println(leftAmbient);
  Serial.println(rightAmbient);
}

void loop() {
  // put your main code here, to run repeatedly:

  // AnalogRead
  double leftAnalogRead = analogRead(LEFTAPIN);
  double rightAnalogRead = analogRead(RIGHTAPIN);

  Serial.print("leftAnalogRead: "); Serial.print(leftAnalogRead);
  Serial.print(" rightAnalogRead: "); Serial.print(rightAnalogRead);
  Serial.println();
  delay(2000);

  int leftSpeed = map(leftAnalogRead, leftAmbient, 1023, 0, 200);
  int rightSpeed = map(rightAnalogRead, rightAmbient, 1023, 0, 200);

  // Sensors
  int leftw = digitalRead(LEFTWPIN);
  int rightw = digitalRead(RIGHTWPIN);
  
  // Follow the light: 
  // Avoid objects:
    if(leftw == 0 && rightw == 0) { // Both touch
      // Turn left
        driveServos(-200, 0);
    } else if (leftw == 0 && rightw == 1) { // Left touch
      // Turn right
        driveServos(0, -200);
    } else if (leftw == 1 && rightw == 0) { // Right touch
      // Turn left
        driveServos(-200, 0);
    } else if (leftAnalogRead > leftAmbient) {
      // Turn right
      driveServos(rightSpeed, leftSpeed / 2); 
        // Robot kept going opposite way of light, so I 
        // swapped the parameters for driveServos
    } else if (rightAnalogRead > rightAmbient) {
      // Turn left
      driveServos(rightSpeed / 2, leftSpeed); 
    } else { // None touch
      // Go forward
      driveServos(200, 200);
    }

}

void driveServos(int leftpw, int rightpw) {

  leftServo.writeMicroseconds(1500 + leftpw);
  rightServo.writeMicroseconds(1500 - rightpw);
  
} // drive
