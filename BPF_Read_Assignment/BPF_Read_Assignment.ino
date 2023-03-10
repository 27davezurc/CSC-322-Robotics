#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:

  // Second Program: Read and compute mean
  unsigned long sum = 0; 
  unsigned long high = 0;
  unsigned long low = 0;
  unsigned long mean = 0;
  int addressCount = 1;
  
  for (long freq = 36500; freq <= 42000; freq = freq + 500) {
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
