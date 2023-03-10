void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  double mean = 0;
  for(int i = 0; i < 100; i++) {
    mean += analogRead(A2);
  }
  mean /= 100;

  Serial.println(mean);

}

void loop() {
  // put your main code here, to run repeatedly:

}
