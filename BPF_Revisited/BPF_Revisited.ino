#include <Servo.h>
#include <EEPROM.h>
Servo leftServo;
Servo rightServo; 

// SERVO PINS
const int LEFTSERVOPIN = 12;
const int RIGHTSERVOPIN = 13;

// IR PINS
static int RIGHTLEDIR = 3;
static int RIGHTRECEIVER = 4;

// WHISKER PINS
const int LEFTWPIN = 5;
const int RIGHTWPIN = 7;

// SONAR PINS: Maybe change this
const int PINGEMITTER = 10; 
const int PINGRECEIVER = 10;

// Conversion Constant
const int usTocm = 29;

// EEPROM Variable
int address = 1;

void setup() {
  Serial.begin(9600);

  // Set up pins for IR LED and IR Sensor
  pinMode(RIGHTLEDIR, OUTPUT);
  pinMode(RIGHTRECEIVER, INPUT);

  // -- Set up whisker pins
  pinMode(LEFTWPIN, INPUT);
  pinMode(RIGHTWPIN, INPUT);

  // -- Attach servo motors to digital output pins
  leftServo.attach(LEFTSERVOPIN);
  rightServo.attach(RIGHTSERVOPIN);

  EEPROM.write(0, 57);
  
  // -- Get measurements of distance and write them to EEPROM
  for (long freq = 33000; freq <= 42000; freq = freq + 500) {
    for (int meas = 1; meas <= 3; meas = meas + 1) {
     
      // Step 2: Roll forward until whisker touches, then pause for 1/2 second
      driveServos(200,200);
      while (digitalRead(LEFTWPIN) == 1 || digitalRead(RIGHTWPIN) == 1);
      driveServos(0, 0);
      delay(500);
     
      // Step 3: Roll backwards until it no longer touches the wall, then pause for 1/2 second
      driveServos(-200,-200);
      while (digitalRead(LEFTWPIN) == 0 || digitalRead(RIGHTWPIN) == 0);
      driveServos(0, 0);
      delay(500);
      
      // Step 4: Read current time with millis() function. This is the start time
//      unsigned long startTime = millis();
      unsigned long startDist = cmDistance();

      // Step 5: Roll backward until it no longer sees the wall with the IR sensor. Pause for 1/2 second.
      driveServos(-200, -200);
      float avg =  0;
      do {
        float sum = 0;
        for (int i = 0; i < 30; i++){
          sum += irDetect(RIGHTLEDIR, RIGHTRECEIVER, freq);
        }
        avg = (sum / 10);
        Serial.println(avg);
      } while (avg < 0.5);
      driveServos(0, 0);

      // Step 6: Read the current time with the millis() function. This is the end time.
//      unsigned long endTime = millis();
      unsigned long endDist = cmDistance();

      // Step 7: Record time (end - start) in the EEPROM
//      unsigned long diff = (endTime - startTime); // Previous assignment
//      unsigned long diff = cmDistance();
      unsigned long diff = endDist - startDist;
      
      unsigned long high = (unsigned long)(diff / 256); // -- quotient of diff/256
      unsigned long low = (unsigned long)(diff % 256);  // -- remainder of diff/256
     
      // Write the values to EEPROM in high/low order.
      EEPROM.write(address, high);
      ++address;
      EEPROM.write(address, low);
      ++address;
    }
  }

}

void loop() {
  // Nothing here
}

// -- InfraRed functions
int irDetect(int irLedPin, int irSensorPin, long freq){
  tone(irLedPin, freq, 8);
  delay(1);
  int ir = digitalRead(irSensorPin);
  delay(1);
  return ir;
}

// -- Movement functions
void driveServos(int leftpw, int rightpw) {

  // Swap + and - if not working properly
  rightServo.writeMicroseconds(1500 + leftpw);
  leftServo.writeMicroseconds(1500 - rightpw);

}


/*
 * Get cm distance measurment from Ping Ultrasonic Distance Sensor
 * Returns: distance measurement in cm.   
 */ 
int cmDistance() {
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
int convert(int us, int scalar) {
    return us / scalar / 2;                        // Echo round trip time -> cm
}


long ping(int emmitterpin, int receiverpin) {
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
       
