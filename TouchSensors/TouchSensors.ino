
// LED PINS
int const LEFTLED = 10;
int const RIGHTLED = 3;

// TOUCH SENSOR PINS
int const LEFTWPIN = 5;
int const RIGHTWPIN = 7;

// SOUND SENSOR PIN
int const SOUNDSENSOR = 2;

void setup() {

  // LED
  pinMode(LEFTLED, OUTPUT); // PIN 10 
  pinMode(RIGHTLED, OUTPUT); // PIN 3
  
  // Touch Sensors
  pinMode(LEFTWPIN, INPUT); // PIN 5
  pinMode(RIGHTWPIN, INPUT); // PIN 7

  // Sound
  pinMode(SOUNDSENSOR, OUTPUT); // PIN 2

  Serial.begin(9600);

  // tone(SERVOPIN, tone, duration in ms)
}

void loop() {
  
  // Sense the environment: 0 means touching; 1 is not touching
  int leftw = digitalRead(LEFTWPIN);
  int rightw = digitalRead(RIGHTWPIN);

  // Determine action:
  if (leftw == 0 && rightw == 0) { // Touch both
      // Turn on both
      digitalWrite(LEFTLED, HIGH);
      digitalWrite(RIGHTLED, HIGH);

      // Play a 3000Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 3000, 4000);
  } else if (leftw == 0 && rightw == 1) { // Only touch left
     // Turn on left; Turn off right
      digitalWrite(LEFTLED, HIGH);
      digitalWrite(RIGHTLED, LOW);

      // Play a 1000Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 1000, 4000);
      
  } else if (leftw == 1 && rightw == 0) { // Only touch right
      // Turn on right; Turn off left
      digitalWrite(RIGHTLED, HIGH); 
      digitalWrite(LEFTLED, LOW);

      // Play a 2000Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 2000, 4000);

  } else if (leftw == 1 && rightw == 1) { // Neither
      // Turn off both
      digitalWrite(LEFTLED, LOW); 
      digitalWrite(RIGHTLED, LOW);

      // Play a 0Hz tone on the piezo electric speaker
      tone(SOUNDSENSOR, 0, 2000);
  }
  
  // Achieve goal:
  Serial.print(leftw);
  Serial.print(rightw);
  Serial.println();
  delay(100);
  
}
