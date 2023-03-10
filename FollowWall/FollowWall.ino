#include <Servo.h> // Include servo library

// -- global variables for servo motors
Servo left;
Servo right;

// LED PINS
int const LEFTLED = 10;
int const RIGHTLED = 3;

// TOUCH SENSOR PINS
int const LEFTWPIN = 5;
int const RIGHTWPIN = 7;

// SOUND SENSOR PIN
int const SOUNDSENSOR = 2;

// int
int wall = 0;

void setup() {

  // Attach signals to designated pins
  left.attach(13);
  right.attach(12);

  // LED
  pinMode(LEFTLED, OUTPUT); // PIN 10 
  pinMode(RIGHTLED, OUTPUT); // PIN 3
  
  // Touch Sensors
  pinMode(LEFTWPIN, INPUT); // PIN 5
  pinMode(RIGHTWPIN, INPUT); // PIN 7

  // Sound
  pinMode(SOUNDSENSOR, OUTPUT); // PIN 2

  // Read whiskers
  int leftw = digitalRead(LEFTWPIN);
  int rightw = digitalRead(RIGHTWPIN);

  // 1) Find Wall:
  while(leftw == 1 && rightw == 1) { // Not touching wall, go forward
    driveServos(-200, -200);
    leftw = digitalRead(LEFTWPIN);
    rightw = digitalRead(RIGHTWPIN);
  }

  if(leftw == 0 && rightw == 1) { // Only touching left whisker
    // Turn on left; Turn off right
    digitalWrite(LEFTLED, HIGH);
    digitalWrite(RIGHTLED, LOW);
    
    // Set wall = 0, backup, and turn left
    wall = 0;
    // driveServos(-200, 0);
    driveServos(0, 200);
    // delay()? To see how long to turn
    
  } else {
    // Turn on right; Turn off left
    digitalWrite(LEFTLED, LOW);
    digitalWrite(RIGHTLED, HIGH);
    
    // Set wall = 1 and turn right
    wall = 1;
    // driveServos(0, -200);
    driveServos(200, 0);
    // delay()? To see how long to turn
    
  }

  Serial.begin(9600);
  
}

void loop() {
  
  // Sense the environment: 0 means touching; 1 is not touching
  int leftw = digitalRead(LEFTWPIN);
  int rightw = digitalRead(RIGHTWPIN);

  // 2) Follow Wall:
  if(wall == 0) { // TURNING LEFT
    if(leftw == 0 && rightw == 0) { // Touching both whiskers
      // Turn on both
      digitalWrite(LEFTLED, HIGH);
      digitalWrite(RIGHTLED, HIGH);

      // Play a 3000Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 3000, 4000);
      
      // Turn left ***
      //driveServos(200, 200); // Backwards
      //delay(500);
      //driveServos(-200, 0);

      driveServos(0, 200);
      
    } else if (leftw == 0 && rightw == 1) { // Only touching left whisker
      // Turn on left; Turn off right
      digitalWrite(LEFTLED, HIGH);
      digitalWrite(RIGHTLED, LOW);

      // Play a 1000Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 1000, 4000);

      // Turn right ***
//      driveServos(200, 200); // Backwards
//      delay(500);
//      driveServos(0, -200);

      driveServos(200, 0);
      
    } else if (leftw == 1 && rightw == 0) { // Only touching right whisker
      // Turn on right; Turn off left
      digitalWrite(RIGHTLED, HIGH); 
      digitalWrite(LEFTLED, LOW);

      // Play a 2000Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 2000, 4000);
      
      // Turn left ***
//      driveServos(200, 200); // Backwards
//      delay(500);
//      driveServos(-200, 0);

      driveServos(0, 200);
      
    } else { // Not touching any whisker
      // Turn off both
      digitalWrite(LEFTLED, LOW); 
      digitalWrite(RIGHTLED, LOW);

      // Play a 0Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 0, 2000);
      
      // Go forward
      driveServos(-200, -200);
    }
  } else { // TURNING RIGHT
     if(leftw == 0 && rightw == 0) { // Touching both whiskers
      // Turn on both
      digitalWrite(LEFTLED, HIGH);
      digitalWrite(RIGHTLED, HIGH);

      // Play a 3000Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 3000, 4000);
      
      // Turn left ***
      //driveServos(200, 200); // Backwards
      //delay(500);
      //driveServos(-200, 0);

      driveServos(0, 200);
      
    } else if (leftw == 0 && rightw == 1) { // Only touching left whisker
      // Turn on left; Turn off right
      digitalWrite(LEFTLED, HIGH);
      digitalWrite(RIGHTLED, LOW);

      // Play a 1000Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 1000, 4000);

      // Turn right ***
//      driveServos(200, 200); // Backwards
//      delay(500);
//      driveServos(0, -200);

      driveServos(200, 0);
      
    } else if (leftw == 1 && rightw == 0) { // Only touching right whisker
      // Turn on right; Turn off left
      digitalWrite(RIGHTLED, HIGH); 
      digitalWrite(LEFTLED, LOW);

      // Play a 2000Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 2000, 4000);
      
      // Turn left ***
//      driveServos(200, 200); // Backwards
//      delay(500);
//      driveServos(-200, 0);

      driveServos(0, 200);
      
    } else { // Not touching any whisker
      // Turn off both
      digitalWrite(LEFTLED, LOW); 
      digitalWrite(RIGHTLED, LOW);

      // Play a 0Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 0, 2000);
      
      // Go forward
      driveServos(-200, -200);
    }
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
  
} // drive
