#include <Servo.h>
#include <EEPROM.h>

Servo leftServo;
Servo rightServo;

// Servo PINS
int const LEFTSERVOPIN = 12;
int const RIGHTSERVOPIN = 13;

// Whisker PINS
int const LEFTWPIN = 5;
int const RIGHTWPIN = 7;

// IR LED PINS
int const RIGHTLEDIR = 2; // 3 
int const RIGHTRECEIVER = 3; // 

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  // Attach Servo Pins
  leftServo.attach(LEFTSERVOPIN);
  rightServo.attach(RIGHTSERVOPIN);


  // Right IR LED & Receiver // swapped
  pinMode(2, OUTPUT);  
  pinMode(3, INPUT);

  // Testing
  while(true) {
    Serial.println(irDetect(2, 3, 38000));
  }
  
  // Stay still at first
  driveServos(0, 0); 

  int address = 0;
  EEPROM.write(address, 57); 
  ++address;

  // First Program: Write into EEPROM
  // Change freq to 36000 just to test. Anything below 36000 it hardly works. This is normal.
  for (long freq = 36000; freq <= 42000; freq = freq + 500) {
    for (int meas = 1; meas <= 3; meas = meas + 1) {
    // Code for steps 2 – 7 goes here
    
    // Step 2: Roll forward until whisker touches, then pause for 1/2 second
    driveServos(100, 100); // 200 instead of 100?
    while(digitalRead(LEFTWPIN) == 1 && digitalRead(RIGHTWPIN) == 1);
    driveServos(0, 0);
    delay(500);
    
    // Step 3: Roll backwards until it no longer touches the wall, then pause for 1/2 second
    driveServos(-200, -200);
    while(digitalRead(LEFTWPIN) == 0 && digitalRead(RIGHTWPIN) == 0);
    driveServos(0, 0);
    delay(500);

    // Step 4: Read current time with millis() function. This is the start time
    unsigned long start = millis();

    // Step 5: Roll backward until it no longer sees the wall with the IR sensor. Pause for 1/2 second.
    driveServos(-200, -200);
    while(irDetect(RIGHTLEDIR, RIGHTRECEIVER, freq) == 0) { // 0 is detecting, 1 is not detecting 
      Serial.print("IR: "); Serial.print(irDetect(RIGHTLEDIR, RIGHTRECEIVER, freq));
      Serial.println();
    }
    driveServos(0, 0);
    delay(500);

    // driveServos(0, 0); // maybe erase this?

    // Step 6: Read the current time with the millis() function. This is the end time.
    unsigned long end = millis();

    // Step 7: Record time (end - start) in the EEPROM
    unsigned long diff = end - start;

    unsigned long high = (unsigned long)(diff / 256); // -- quotient of diff/256
    unsigned long low = (unsigned long)(diff % 256);  // -- remainder of diff/256

    EEPROM.write(address, high);
    ++address;
    EEPROM.write(address, low);
    ++address;
    }
  }


  // Second Program: Read and compute mean
  long sum = 0; 
  long high = 0;
  long low = 0;
  long mean = 0;
  int addressCount = 1;
  
  for (long freq = 33000; freq <= 42000; freq = freq + 500) {
    sum = 0;
    for (int meas = 1; meas <= 3; meas = meas + 1) {
      high = EEPROM.read(addressCount);
      addressCount++;
      low = EEPROM.read(addressCount);
      addressCount++;

      sum += high * 256 + low;
    }
    mean = sum / 3;
    Serial.println("mean: ");   Serial.print(mean);
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}


int irDetect (int irLedPin, int irReceiverPin, long frequency) {
  tone(irLedPin, frequency, 8); // IRLED 38 kHz at least 1 ms
  delay(1); // Wait 1 ms
  int ir = digitalRead(irReceiverPin); // IR receiver -> ir variable
  delay(1); // Down time before recheck
  return ir; // Return 1 no detect, 0 detect
} 

void driveServos(int leftpw, int rightpw) {

  leftServo.writeMicroseconds(1500 + leftpw);
  rightServo.writeMicroseconds(1500 - rightpw);
  
} // drive
