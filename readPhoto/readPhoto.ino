void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  double photo = readPhoto(100, A5);
  Serial.println(photo);
}

double readPhoto(int N, int pin) {
  
  double mean = 0;
  for(int i = 0; i < N; i++) {
    mean += analogRead(pin);
  }

  mean /= N;
  return mean;
}
