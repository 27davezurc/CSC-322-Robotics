void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int irLeft = irDirect(9, 8, 38000);
  Serial.println(irLeft);
  delay(100);
}

int irDirect(int irLedPin, int irReceiverPin, long frequency) {
  tone(irLedPin, frequency, 8);
  delay(1);
  int ir = digitalRead(irReceiverPin);
  delay(1);
  return ir;
}
