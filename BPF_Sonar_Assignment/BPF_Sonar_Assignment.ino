#include <Servo.h>
#include <EEPROM.h>

// SERVO MOTORS
Servo leftServo;
Servo rightServo;
const int LEFTSERVOPIN = 12;
const int RIGHTSERVOPIN = 13;

// IR LED/SENSOR
const int ledPinRight = 3;
const int irSensorRight = 4;

// WHISKER
const int LEFTWHISKER = 5;
const int RIGHTWHISKER = 7;

// SONAR PINS
const int PINGEMITTER = 10;
const int PINGRECEIVER = 10;

// -- Global variables for EEPROM
int address = 1;
int count = 0;

const int usTocm = 29;

void setup() {
  Serial.begin(9600);

  pinMode(ledPinRight, OUTPUT);
  pinMode(irSensorRight, INPUT);

  pinMode(LEFTWHISKER, INPUT);
  pinMode(RIGHTWHISKER, INPUT);

  leftServo.attach(LEFTSERVOPIN);
  rightServo.attach(RIGHTSERVOPIN);

  // Get distance measurements and write to EEPROM
  for (long freq = 36500; freq <= 42000; freq = freq + 500) {
    for (int meas = 1; meas <= 3; meas = meas + 1) {
     
      // Step 2: Roll forward until whisker touches, then pause for 1/2 second
      driveServos(200, 200);;
      while (digitalRead(LEFTWHISKER) == 1 || digitalRead(RIGHTWHISKER) == 1);
      driveServos(0, 0);
      Serial.println("IT GOT HERE 1");
      delay(500);
     
      // Step 3: Roll backwards until it no longer touches the wall, then pause for 1/2 second
      Serial.println("IT GOT HERE 2");
      driveServos(-200,-200);
      while (digitalRead(LEFTWHISKER) == 0 || digitalRead(RIGHTWHISKER) == 0);
      driveServos(0, 0);
      Serial.println("IT GOT HERE 3");
      delay(500);
      
      // Step 4: Read current dist with cmDistance() function. This is the start time
//      unsigned long startTime = millis();
      unsigned long startDist = cmDistance();
      
      driveServos(-200,-200);
      float avg =  0;
      do{
        float sum = 0;
        for (int i = 0; i < 30; i++){
          sum += irDetect(ledPinRight, irSensorRight, freq);
        }
        avg = (sum / 10);
        Serial.println(avg);
      }while (avg < 0.5);
      driveServos(0, 0);
      
      // Step 6: Read the current dist with the cmDistance() function. This is the end time.
//      unsigned long endTime = millis();
      unsigned long endDist = cmDistance();

      // Step 7: Record time (end - start) in the EEPROM
//      unsigned long diff = (endTime - startTime);
      unsigned long diff = endDist - startDist;

      // split the elapsed time into two values to facilitate writing to EEPROM
      unsigned long high = (unsigned long)(diff / 256); // -- quotient of diff/256
      unsigned long low = (unsigned long)(diff % 256);  // -- remainder of diff/256
     
      EEPROM.write(address, high);
      ++address;
      EEPROM.write(address, low);
      ++address;
 
      ++count;
    }
  }
  EEPROM.write(0, count);

}

void loop() {

}

// -- InfraRed functions
int irDetect(int irLedPin, int irSensorPin, long freq){
  tone(irLedPin, freq, 8);
  delay(1);
  int ir = digitalRead(irSensorPin);
  delay(1);
  return ir;
}

int irDistance(int irLedPin, int irSensorPin){
  int distance = 0;
  // 33000
  for(long f = 38000; f <= 42000; f += 1000){
    distance += irDetect(irLedPin, irSensorPin, f);
  }
  return distance;
}

// -- Movement functions
void driveServos(int leftpw, int rightpw) {

  rightServo.writeMicroseconds(1500 - leftpw);
  leftServo.writeMicroseconds(1500 + rightpw);

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
