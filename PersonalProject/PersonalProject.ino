#include <Servo.h>

// SERVO MOTORS
Servo leftServo;
Servo rightServo;
const int LEFTSERVOPIN = 12;
const int RIGHTSERVOPIN = 13;

// WHISKER
const int LEFTWHISKER = 5;
const int RIGHTWHISKER = 7;

// SONAR PINS
const int PINGEMITTER = 10;
const int PINGRECEIVER = 10;

const int usTocm = 29;           // -- conversion constant

void setup()                                      
{
  Serial.begin(9600);  

  // -- Set up whisker pins
  pinMode(LEFTWHISKER, INPUT);
  pinMode(RIGHTWHISKER, INPUT);

  // -- Attach servo motors to digital output pins
  leftServo.attach(LEFTSERVOPIN);
  rightServo.attach(RIGHTSERVOPIN);

  int targetOne = 30;
  // Continue backing up until it reaches a certain distance
  while(cmDistance() > targetOne) {
    driveServos(-200, -200);
  }
  stayStill(500);

  int targetTwo = 15;
  // Reverse into the spot until it reaches a certain distance
  while(cmDistance() > targetTwo) {
    driveServos(-40, -200);
  }
  stayStill(500);

  // Straigthen robot
  driveServos(-200, -20);
  delay(3000);
  stayStill(500);
  
  // Straighten the robot until whiskers touch object in front
  while (digitalRead(LEFTWHISKER) == 1 || digitalRead(RIGHTWHISKER) == 1) {
    driveServos(40, 70);
  }
  stayStill(500);
  
}  
 
void loop()                                       
{
  int cm = cmDistance();
  Serial.print(cm);
  Serial.println(" cm");
  delay(200);  
}

void driveServos(int leftpw, int rightpw) {

  rightServo.writeMicroseconds(1500 - leftpw);
  leftServo.writeMicroseconds(1500 + rightpw);

}

void stayStill(int ms) {
  driveServos(0, 0);
  delay(ms);
}

/*
 * Get cm distance measurment from Ping Ultrasonic Distance Sensor
 * Returns: distance measurement in cm.   
 */ 
int cmDistance()
{
  int distance = 0;                                // Initialize distance to zero    
  do                                               // Loop in case of zero measurement
  {
    int us = ping(PINGEMITTER, PINGRECEIVER);      // Get measurement in microseconds
    distance = convert(us, usTocm);                // Convert microseconds to cm 
    delay(3);                                      // Pause before retry (if needed)
  }
  while(distance == 0);                            
  return distance;                                 // Return distance measurement
}

/*
 * Converts measurement in microseconds round trip measurement to units of distance
 * depending on the constant used.
 * Parameters: us - microsecond value from Sonar echo time measurement.
 *             scalar - 29 for us to cm, or 74 for us to in.
 * Returns:    distance measurement dictated by the scalar.   
 */ 
int convert(int us, int scalar)
{
    return us / scalar / 2;                        // Echo round trip time -> cm
}


long ping(int emmitterpin, int receiverpin)
{
  long duration;                                   // Variables for calculating distance
  pinMode(emmitterpin, OUTPUT);                    // TRIG pin -> output
  digitalWrite(emmitterpin, LOW);                  // Generate a 5 microsecond pulse
  
  delayMicroseconds(2);                            
  digitalWrite(emmitterpin, HIGH);                 
  delayMicroseconds(5);                            
  digitalWrite(emmitterpin, LOW);                          
  
  pinMode(receiverpin, INPUT);                     // Set ECHO pin to input 
  duration = pulseIn(receiverpin, HIGH, 25000);    // Measure echo time pulse from sonar
  return duration;                                 // Return pulse duration in microseconds
}    
          
