
int a[100];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  // 1K: 98 / 99
  // 2K: 48
  // 10K: 657
//  int photo = analogRead(A1);
//  Serial.println(photo);
//  delay(100);

  double photo = readPhoto(100);
  Serial.println(photo);
}

double readPhoto(int N) {
  
  // Don't need array
  
  double mean = 0;
  for(int i = 0; i < 100; i++) {
    a[i] = analogRead(A1);  
    mean += a[i];
  }
  mean /= 100;

  double stdDev = 0;
  for(int i = 0; i < 100; i++) {
    stdDev += (a[i] - mean) * (a[i] - mean);
  }
  stdDev = sqrt(stdDev / 100);

  Serial.print(mean);
  Serial.print("\t");
  Serial.print(stdDev);
  Serial.print("\n");

  return mean;
}
