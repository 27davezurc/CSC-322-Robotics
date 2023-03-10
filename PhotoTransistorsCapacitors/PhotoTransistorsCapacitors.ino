 /*
* Robotics with the BOE Shield - LeftLightSensor
* Measures and displays microsecond decay time for left light sensor.
*/

const int CAP104PIN = 4;
const int CAP103PIN = 3;

void setup() { // Built-in initialization block
 
 Serial.begin(9600); // Set data rate to 9600 bps
}

void loop()  { // Main loop auto-repeats

  long cap103 = rcTime(CAP103PIN); // Red Capacitor
  long cap104 = rcTime(CAP104PIN); // Yellow Capacitor
  
  Serial.print(cap104); Serial.print("us ");
  Serial.print(cap103); Serial.print("us ");
  Serial.println();
  delay(100);
}

 // rcTime function at pin
long rcTime(int pin) {    // ..returns decay time

 pinMode(pin, OUTPUT);    // Charge capacitor
 digitalWrite(pin, HIGH); // ..by setting pin ouput-high
 delay(1); // ..for 5 ms
 
 pinMode(pin, INPUT); // Set pin to input
 digitalWrite(pin, LOW); // ..with no pullup
 long time = micros(); // Mark the time
 
 while(digitalRead(pin)); // Wait for voltage < threshold
 time = micros() - time; // Calculate decay time
 return time; // Return decay time
} 
