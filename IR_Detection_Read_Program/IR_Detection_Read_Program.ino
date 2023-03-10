#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:

  // Second Program: Read

  unsigned long sum = 0;
  unsigned long high = 0;
  unsigned long low = 0;

  int addressCount = 1;
  
  for(int measurement = 0; measurement < 5; measurement++) {
    
    high = EEPROM.read(addressCount);
    addressCount++;
    low = EEPROM.read(addressCount);
    addressCount++;

    sum = high * 256 + low;
    Serial.println("Measurement: "); Serial.print(sum);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
